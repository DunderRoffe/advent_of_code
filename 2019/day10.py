from typing import List
from math import gcd

SPACE = 0
ASTEROID = 1

def int_format(source: str) -> List[int]:
    ret: List[int] = []
    for s in source:
        if s == "#":
            ret.append(ASTEROID)
        elif s == ".":
            ret.append(SPACE)

    return ret

assert int_format(".##..#") == [SPACE, ASTEROID, ASTEROID, SPACE, SPACE, ASTEROID]


def check_pos(target_x: int, target_y: int, width: int, height: int, source: List[int]) -> int:
    seen_asteroids = 0
    debug_txt = f"{target_x}, {target_y} can see: "

    for x in range(width):
        for y in range(height):
            if x == target_x and y == target_y:
                continue

            #print(f"Looking at {x},{y}")
            lookat = source[x + (y * width)]

            if lookat == ASTEROID:
                diff_x = x - target_x
                diff_y = y - target_y

                d = gcd(diff_x, diff_y)

                step_x = diff_x // d
                step_y = diff_y // d

                #print(f"diff: {diff_x}, {diff_y}")
                #print(f"step: {step_x}, {step_y}")

                can_be_seen = check_line_of_sight(target_x, target_y, width, height, step_x, step_y, x, y, source)
                if can_be_seen:
                    seen_asteroids += 1
                    debug_txt += f" {x}, {y} "

    #print(debug_txt)
    return seen_asteroids



def check_line_of_sight(target_x: int, target_y: int, width: int, height: int, step_x: int, step_y: int, end_x: int, end_y: int, source: List[int]) -> bool:
    x = target_x + step_x
    y = target_y + step_y

    #print(f"target: {target_x},{target_y}")
    #print(f"end: {end_x},{end_y}")
    #print(f"step: {step_x}, {step_y}")

    while ((x - end_x) != 0) or ((y - end_y) != 0):
        #print(f"Looking at {x},{y}")

        lookat = source[x + (y * width)]
        if lookat == ASTEROID:
            #print(f"Found asteroid!")
            return False

        x += step_x
        y += step_y

    return True

assert check_line_of_sight(0, 0, 3, 3, 1, 1, 2, 2, [ASTEROID, SPACE, SPACE, SPACE, ASTEROID, SPACE, SPACE, SPACE, ASTEROID]) == False
assert check_line_of_sight(0, 0, 3, 3, 1, 1, 1, 1, [ASTEROID, SPACE, SPACE, SPACE, ASTEROID, SPACE, SPACE, SPACE, ASTEROID]) == True
assert check_line_of_sight(0, 0, 3, 3, 1, 1, 2, 2, [ASTEROID, SPACE, SPACE, SPACE, SPACE, SPACE, SPACE, SPACE, ASTEROID]) == True

#
#
#

def draw_sight(width: int, height:int , source: List[int], draw: bool = False) -> int:
    if draw: print()
    best = 0
    for y in range(height):
        if draw: line = ""
        for x in range(width):
            lookat = source[x + (y * width)]
            if lookat == ASTEROID:
                see = check_pos(x, y, width, height, source)
                best = max(see, best)
                if draw: line += "#" #str(see)
            else:
                if draw: line += "."
        if draw: print(line)
    if draw:
        print()
        print(f"View from best spot: {best}")
    return best

test_input1 = int_format(".#..#.....#####....#...##")
test_input2 = int_format(".#..##.###...#######\
##.############..##.\
.#.######.########.#\
.###.#######.####.#.\
#####.##.#.##.###.##\
..#####..#.#########\
####################\
#.####....###.#.#.##\
##.#################\
#####.##.###..####..\
..######..##.#######\
####.##.####...##..#\
.#####..#.######.###\
##...#.##########...\
#.##########.#######\
.####.#.###.###.#.##\
....##.##.###..#####\
.#.#.###########.###\
#.#.#.#####.####.###\
###.##.####.##.#..##")

test_input3 = int_format("\
.#..#..###\
####.###.#\
....###.#.\
..###.##.#\
##.##.#.#.\
....###..#\
..#.#..#.#\
#..#.#.###\
.##...##.#\
.....#.#..\
")

test_input4 = int_format("\
#.#...#.#.\
.###....#.\
.#....#...\
##.#.#.#.#\
....#.#.#.\
.##..###.#\
..#...##..\
..##....##\
......#...\
.####.###.\
")

test_input5 = int_format("\
......#.#.\
#..#.#....\
..#######.\
.#.#.###..\
.#..#.....\
..#....#.#\
#..#....#.\
.##.#..###\
##...#..#.\
.#....####\
")

test_input6 = int_format("\
......#.#.\
#..#.#....\
..#######.\
.#.#.###..\
.#..#.....\
..#....#.#\
#..#....#.\
.##.#..###\
##...#..#.\
.#....####\
")


assert draw_sight(5, 5, test_input1) == 8
assert draw_sight(20, 20, test_input2) == 210
assert draw_sight(10, 10, test_input3) == 41
assert draw_sight(10, 10, test_input4) == 35
assert draw_sight(10, 10, test_input5) == 33
assert draw_sight(10, 10, test_input6) == 33

assert check_line_of_sight(0,2, 5, 5, 1, 0, 1, 2, test_input1) == True
assert check_line_of_sight(0,2, 5, 5, 1, 0, 2, 2, test_input1) == False
assert check_line_of_sight(0,2, 5, 5, 1, 0, 3, 2, test_input1) == False
assert check_line_of_sight(0,2, 5, 5, 1, 0, 4, 2, test_input1) == False

assert check_pos(1, 0, 5, 5, test_input1) == 7

puzzle_width = 0
puzzle_height = 0
with open("day10_input.txt", "r") as f:
    puzzle_input: List[int] = []
    for line in f.readlines():
        puzzle_input += int_format(line)
        puzzle_height += 1

    puzzle_width = len(line) - 1
    puzzle_height = (len(puzzle_input) // puzzle_width)

assert puzzle_input[:5] == [0,1,0,0,0]

print(puzzle_width)
print(puzzle_height)
draw_sight(puzzle_width, puzzle_height, puzzle_input, draw=True)
