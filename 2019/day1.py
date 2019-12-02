from math import floor
from typing import Dict

def module_req(mass: int) -> int:
    return floor(mass / 3.0) - 2

assert module_req(12) == 2
assert module_req(14) == 2
assert module_req(1969) == 654
assert module_req(100756) == 33583

total_fuel_req: int = 0
with open("day1_input.txt", "r") as f:
    for line in f.readlines():
        total_fuel_req += module_req(int(line))

print(f"Part 1: {total_fuel_req}")

#
# Part 2
#

memo: Dict[int, int] = dict()

def module_req_memo(mass: int) -> int:
    if mass <= 0:
        return 0

    if not mass in memo:

        calc_mass: int = max(0, floor(mass / 3.0) - 2)
        memo[mass] = calc_mass + module_req_memo(calc_mass)

    return  memo[mass]

assert module_req_memo(14) == 2
assert module_req_memo(1969) == 966
assert module_req_memo(100756) == 50346

total_fuel_req = 0
with open("day1_input.txt", "r") as f:
    for line in f.readlines():
        total_fuel_req += module_req_memo(int(line))

print(f"Part 2: {total_fuel_req}")
