from typing import Tuple

def match(nr: int) -> Tuple[bool, bool]:
    if nr < 10e4:
       return (False, False)

    streak: int = 1
    last_digit = None

    has_double_streak = False
    has_min2_streak = False

    for digit in str(nr):
        if last_digit is not None:
            if digit == last_digit:
               streak += 1
            else:
               if streak >= 2:
                  has_min2_streak = True
               if streak == 2:
                  has_double_streak = True
               streak = 1

            if int(digit) < int(last_digit):
               return (False, False)

        last_digit = digit

    if streak >= 2:
       has_min2_streak = True
    if streak == 2:
       has_double_streak = True

    return (has_min2_streak, has_double_streak)

# Part 1 tests
assert match(111111)[0]
assert not match(223450)[0]
assert not match(123789)[0]

# Part 2 tests
assert match(112233)[1]
assert not match(123444)[1]
assert match(111122)[1]

#
# Solve
#

amnt_part1: int = 0
amnt_part2: int = 0
for nr in range(137683, 596253):
    part1_match, part2_match = match(nr)
    if part1_match:
        amnt_part1 += 1
    if part2_match:
        amnt_part2 += 1

print(f"Part 1: {amnt_part1}")
print(f"Part 2: {amnt_part2}")
