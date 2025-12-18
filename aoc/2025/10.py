# Problem: Advent of Code 2025 - Day 10: Factory
# Author: babhishek21
# Lang: Python 3
#
# Adapted from
#   - https://www.reddit.com/r/adventofcode/comments/1pity70/comment/nta30mi/
#   - https://www.reddit.com/r/adventofcode/comments/1pity70/comment/ntb36sb/
#
# TODO
#   - Elegant bifurcation solution: https://www.reddit.com/r/adventofcode/comments/1pk87hl/2025_day_10_part_2_bifurcate_your_way_to_victory/
#   - Gaussian elimination + multithreading: https://github.com/maneatingape/advent-of-code-rust/blob/main/src/year2025/day10.rs

from collections import Counter
from multiprocessing import Pool
import sys
from typing import final

INF = int(0x3F3F3F3F)


"""
Part 1
------

Each combo press essentially flips a machine light (bit).
    - We can search for shortest path from all zero bits to bit config of the machine state.
    - Max search space is 2**(number of combos), which is not so bad on this puzzle input.
"""


def solve1(machine: str, combos: list[tuple[int, ...]]) -> int:
    ans = 0

    dest = 0
    for i, ch in enumerate(machine):
        if ch == "#":
            dest |= 1 << i

    opts: list[int] = []
    for combo in combos:
        opt = 0
        for button in combo:
            opt |= 1 << button
        opts.append(opt)

    # print(bin(dest), [bin(opt) for opt in opts])

    # run bfs on all options available to go from src to dest
    src = 0
    que = [src]

    dist = [INF] * (1 << len(machine))
    dist[src] = 0

    for curr in que:
        if curr == dest:
            ans = dist[curr]
            break

        for opt in opts:
            next = curr ^ opt

            if dist[curr] + 1 < dist[next]:
                dist[next] = dist[curr] + 1
                que.append(next)

    # print(ans)

    return ans


"""
Part 2
------

Each combo press increments joltage of some lights.
  - We could a simple shortest path search from all zero to joltage requirement state, but that is too slow.
  - The search space for that is about (number of combos)**(number of presses), which is hopelessly slow.

Another way to think about this is that is it an Integer Linear Programming (ILP) problem of the form:

  find x ∈ ℤ >= 0, such that:
      1. Cx = R where C[i] is the [i]th combo of wirings, x[i] is the number of presses for that combo, to reach required state R[i]
      2. sum(x) needs to be minimized

This is:
  - A linear Diophantine system
  - With non-negative integer variables
  - And a linear minimization objective
which is formally an ILP problem.

In matrix form:

  minimize    1ᵀ x
  subject to  A x = b
              x ≥ 0 integer

  where n = number of joltage counters (i.e. the number of lights in the machine)
  and m = number of wiring combo buttons that are available to press, then:

  A is an (n x m) matrix where A[i][j] = 1 if [j]th combo button lights up [i]th light
  x is a (m x 1) vector where x[j] is the number of times [j]th combo button is pressed
  b is a (n x 1) vector where b[i] is the jotage requirement of the [i]th light

Options to solve:
    - Some sort of Simplex solver with branch-and-bound: https://github.com/Fadi88/AoC/blob/master/2025/days/day10/test.py
    - Some external LP solver like Z3:
    - Matrix solution using row-reduction (probably using Gaussian elimination): https://git.tronto.net/aoc/file/2025/10/b.py.html

Those are hard to do and probably overkill for this input, so instead we'll do simple backtracking + branch-and-bound + some optimizations
(which is equivalent to an ILP solver).

Adapted from:
    - https://github.com/mkern75/AdventOfCodePython/blob/main/year2025/Day10.py
    - https://github.com/michel-kraemer/adventofcode-rust/blob/main/2025/day10/src/main.rs
"""


@final
class BrandAndBoundILPSolverSansSimplex:
    def __init__(
        self, joltage_requirements: list[int], wiring_combos: list[tuple[int, ...]]
    ):
        self.requirements: list[int] = joltage_requirements
        self.combos: list[tuple[int, ...]] = wiring_combos

        self.num_lights: int = len(joltage_requirements)
        self.num_combos: int = len(wiring_combos)

        self.best: int = INF

        # cache to store count_remaining_combos_for_each_light at each combo_idx
        # self.cache: dict[int, Counter[int]] = {}

        # indices of the lights for which the current combo is the last resort
        self.last_resort_lights_at_combo: list[list[int]] = []

    def solve(self) -> int:
        # using static reordering of combos (simpler, but faster. ~275secs on puzzle input)
        self.reorder_combos()
        self.precompute_remaining_combos_for_each_light()
        self.dfs(self.requirements)

        # using dynamic reordering of combos  (better solver, but slower. ~30mins on puzzle input)
        # self.try_next_combo(self.requirements, self.combos)

        print(self.best)  # debug
        return self.best

    def reorder_combos(self):
        """
        Reorder combos with these heuristics:
        1. Prefer combos that are last remaining option for many lights
        2. Prefer combos touching fragile lights (i.e. light which have few remaining combos)
        3. (Tie-breaker) Prefer larger combos
        """
        remaining = self.combos[:]
        ordered: list[tuple[int, ...]] = []

        # Initial counts
        num_combos_per_light = [0] * self.num_lights
        for combo in remaining:
            for light_idx in combo:
                num_combos_per_light[light_idx] += 1

        while remaining:

            def score(combo: tuple[int, ...]) -> tuple[int, float, int]:
                forced = sum(num_combos_per_light[l] == 1 for l in combo)
                fragility = sum(
                    1 / num_combos_per_light[l]
                    for l in combo
                    if num_combos_per_light[l] > 0
                )
                return (forced, fragility, len(combo))

            best_combo = max(remaining, key=score)
            remaining.remove(best_combo)
            ordered.append(best_combo)

            # Decrement counts for affected lights
            for light_idx in best_combo:
                num_combos_per_light[light_idx] -= 1

        self.combos = ordered

    def precompute_remaining_combos_for_each_light(self):
        remaining_combos_per_light = [0] * self.num_lights
        for combo in self.combos:
            for light_idx in combo:
                remaining_combos_per_light[light_idx] += 1

        for combo in self.combos:
            last_resort_indices = [
                light_idx
                for light_idx in combo
                if remaining_combos_per_light[light_idx] == 1
            ]
            self.last_resort_lights_at_combo.append(last_resort_indices)

            for light_idx in combo:
                remaining_combos_per_light[light_idx] -= 1

    def dfs(
        self,
        remaining_requirements: list[int],
        curr_combo_idx: int = 0,
        presses_so_far: int = 0,
    ):
        """
        Go through all the combos one by one and branch with different amount of presses for each.
        """
        best = self.best
        combos = self.combos

        if presses_so_far >= best:  # this branch is already worse; PRUNE!
            return

        if (
            presses_so_far + max(remaining_requirements) >= best
        ):  # this branch is running worse; PRUNE!
            return

        if curr_combo_idx == self.num_combos:  # branch end; all combos have been tried
            if sum(remaining_requirements) == 0:
                self.best = min(best, presses_so_far)
            return

        # explore deeper

        """
        with the remaining combos (i.e. combos[curr_idx...]), if this combo is the last resort for any light,
        we must meet the remaining joltage requirements for such lights with this combo itself
        """
        # if curr_combo_idx not in self.cache:
        #     self.cache[curr_combo_idx] = Counter(
        #         light_idx for combo in combos[curr_combo_idx:] for light_idx in combo
        #     )
        # count_remaining_combos_for_each_light = self.cache[curr_combo_idx]

        # min_presses_needed = max(
        #     (
        #         remaining_requirements[light_idx]
        #         for light_idx in combos[curr_combo_idx]
        #         if count_remaining_combos_for_each_light[light_idx] == 1
        #     ),
        #     default=0,
        # )

        min_presses_needed = max(
            (
                remaining_requirements[light_idx]
                for light_idx in self.last_resort_lights_at_combo[curr_combo_idx]
            ),
            default=0,
        )

        max_presses_allowed = min(
            remaining_requirements[light_idx] for light_idx in combos[curr_combo_idx]
        )  # any more presses and we'll overshoot the requirements

        # print("[{}]".format(curr_combo_idx), min_presses_needed, "->", max_presses_allowed) # debug
        # print("     counter:  ", [x[1] for x in sorted(count_remaining_combos_for_each_light.most_common())])   # debug
        # print("     remaining:", remaining_requirements)    # debug

        if min_presses_needed > max_presses_allowed:  # impossible branch; PRUNE!
            return

        # try pressing all feasible combos
        for presses in range(min_presses_needed, max_presses_allowed + 1):
            # next_remaining_requirements = remaining_requirements[:]

            for light_idx in combos[curr_combo_idx]:
                # next_remaining_requirements[light_idx] -= presses
                remaining_requirements[light_idx] -= presses

            self.dfs(
                # next_remaining_requirements,
                remaining_requirements,
                curr_combo_idx + 1,
                presses_so_far + presses,
            )

            for light_idx in combos[curr_combo_idx]:
                remaining_requirements[light_idx] += presses

    def try_next_combo(
        self,
        remaining_requirements: list[int],
        remaining_combos: list[tuple[int, ...]],
        presses_so_far: int = 0,
    ):
        """
        Go through all the combos one by one and branch with different amount of presses for each (DFS).
        Uses dynamic reordering of combos within a DFS branch.
        """
        if presses_so_far >= self.best:  # this branch is already worse; PRUNE!
            return

        if (
            presses_so_far + max(remaining_requirements) >= self.best
        ):  # this branch is running worse; PRUNE!
            return

        if len(remaining_combos) == 0:  # branch end; all combos have been tried
            if all(x == 0 for x in remaining_requirements):
                self.best = min(self.best, presses_so_far)
            return

        # explore deeper (pick a combo to try next)

        count_remaining_combos_for_each_light = Counter(
            light_idx
            for combo in remaining_combos
            for light_idx in combo  # flat map
        )

        def combo_score(combo: tuple[int, ...]):
            forcedness = sum(
                count_remaining_combos_for_each_light[light_idx] == 1
                for light_idx in combo
            )  # is this combo the last resort for any lights?
            fragility = sum(
                1 / count_remaining_combos_for_each_light[light_idx]
                for light_idx in combo
            )  # how many fragile lights does this combo affect? The lesser the number of combos a light is affected by, the more fragile it is (lesser options left).
            versatility = len(combo)  # how many lights can this combo affect?

            return (forcedness, fragility, versatility)

        # dynamically choose next combo to try (this is computationally expensive)
        chosen_combo = max(remaining_combos, key=combo_score)

        max_presses_allowed = min(
            remaining_requirements[light_idx] for light_idx in chosen_combo
        )  # any more presses and we'll overshoot the requirements

        min_presses_needed = max(
            (
                remaining_requirements[light_idx]
                for light_idx in chosen_combo
                if count_remaining_combos_for_each_light[light_idx] == 1
            ),
            default=0,
        )  # if this combo is the last resort for any lights, we must meet their requirements with this combo itself

        # print("[{}]".format(chosen_combo), min_presses_needed, "->", max_presses_allowed) # debug
        # print("     counter:  ", [x[1] for x in sorted(count_remaining_combos_for_each_light.most_common())])   # debug
        # print("     remaining:", remaining_requirements)    # debug

        if min_presses_needed > max_presses_allowed:  # impossible branch; PRUNE!
            return

        # try pressing all feasible combos
        next_remaining_combos = [
            combo for combo in remaining_combos if combo != chosen_combo
        ]

        for presses in range(min_presses_needed, max_presses_allowed + 1):
            next_remaining_requirements = remaining_requirements[:]
            for light_idx in chosen_combo:
                next_remaining_requirements[light_idx] -= presses

            self.try_next_combo(
                next_remaining_requirements,
                next_remaining_combos,
                presses_so_far + presses,
            )


def solve2(requirements: list[int], combos: list[tuple[int, ...]]) -> int:
    solver = BrandAndBoundILPSolverSansSimplex(requirements, combos)
    return solver.solve()


def solve2_task(machine: tuple[str, list[tuple[int, ...]], list[int]]):
    _, wiring_combos, joltage_requirements = machine
    return solve2(joltage_requirements, wiring_combos)


def main():
    machines: list[tuple[str, list[tuple[int, ...]], list[int]]] = []

    for line in sys.stdin:
        line = line.rstrip("\n")
        inp = line.split()

        machine_lights = inp[0][1:-1]
        wiring_combos = [tuple(map(int, c[1:-1].split(","))) for c in inp[1:-1]]
        joltage_requirements = list(map(int, inp[-1][1:-1].split(",")))

        # print(machine_lights, wiring_combos)

        machines.append((machine_lights, wiring_combos, joltage_requirements))

        # ans1 += solve1(machine_lights, wiring_combos)
        # ans2 += solve2(joltage_requirements, wiring_combos)

    with Pool() as pool:
        ans2 = sum(
            pool.imap_unordered(solve2_task, machines, chunksize=1)
        )  # solves puzzle input in about ~145secs

    ans1 = sum(
        solve1(machine_lights, wiring_combos)
        for machine_lights, wiring_combos, _ in machines
    )  # very fast

    print("answers:", ans1, ans2)


if __name__ == "__main__":
    main()
