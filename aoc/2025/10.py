# Problem: Advent of Code 2025 - Day 10: Factory
# Author: babhishek21
#   Originally from https://www.reddit.com/r/adventofcode/comments/1pity70/comment/nta30mi/
# Lang: Python 3

import sys

INF = 0x3f3f3f3f

def solve1(machine: str, combos: list[tuple[int, ...]]) -> int:
    ans = 0

    dest = 0
    for i, ch in enumerate(machine):
        if ch == '#':
            dest |= 1 << i

    opts: list[int] = []
    for combo in combos:
        opt = 0
        for button in combo:
            opt |= 1 << button
        opts.append(opt)

    print(bin(dest), [bin(opt) for opt in opts])

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

    print(ans)

    return ans


def main():
    ans1 = 0

    for line in sys.stdin:
        line = line.rstrip("\n")
        inp = line.split()

        machine = inp[0][1:-1]
        combos = [tuple(map(int, c[1:-1].split(","))) for c in inp[1:-1]]

        # print(machine, combos)

        ans1 += solve1(machine, combos)

    print("answers:", ans1)


if __name__ == "__main__":
    main()
