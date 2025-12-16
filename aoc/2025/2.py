# Problem: Advent of Code 2025 - Day 2: Gift Shop
# Author: babhishek21
# Lang: Python 3

ranges = [rr.split("-") for rr in input().split(",")]
ranges = [tuple(map(int, rr)) for rr in ranges]

ans1, ans2 = 0, 0


def check_repeated(string: str, chunk_size: int) -> bool:
    if len(string) % chunk_size != 0:
        return False

    chunks = [string[i : i + chunk_size] for i in range(0, len(string), chunk_size)]
    return len(set(chunks)) == 1


for st, ed in ranges:
    for i in range(st, ed + 1):
        ss = str(i)

        if len(ss) % 2 == 0:
            ans1 += i if check_repeated(ss, len(ss) // 2) else 0

        chunk_size = len(ss) // 2
        while chunk_size:
            if check_repeated(ss, chunk_size):
                ans2 += i
                break

            chunk_size -= 1

print("answers:", ans1, ans2)
