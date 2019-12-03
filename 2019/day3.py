from typing import List, Tuple, Optional, Any, Dict

class Position():

     x: int = 0
     y: int = 0

     def copy(self):
         p = Position()
         p.x = self.x
         p.y = self.y

         return p

     def __hash__(self) -> int:
         return hash((self.x, self.y))


class Node():

    position = Position()
    steps: int = -1

class Line():

    p1: Position
    p2: Position

    def __init__(self, p1: Position, p2: Position):
        self.p1 = p1.copy()
        self.p2 = p2.copy()

    def is_horizontal(self) -> bool:
        return self.p1.x == self.p2.x

    def __len__(self) -> int:
        return abs(self.p1.x - self.p2.x) + abs(self.p1.y - self.p2.y)


def parse_wire_instructions(wire_instructions: List[str]) -> List[Line]:
    next_position = Position()
    lines: List[Line] = list()

    for instr in wire_instructions:
        direction: str = instr[0]
        length: int = int(instr[1:])

        before_position = next_position.copy()
        if direction == "R":
           next_position.x += length
        elif direction == "L":
           next_position.x -= length
        elif direction == "U":
           next_position.y += length
        elif direction == "D":
           next_position.y -= length
        else:
           raise Exception(f"Parse error: Illegal direction '{direction}'")

        temp_position = next_position.copy()
        line = Line(before_position, temp_position)
        lines.append(line)

    return lines

def parse_two_wires(list_of_instructions: List[List[str]]) -> List[Node]:
    lines_in_wire1 = parse_wire_instructions(list_of_instructions[0])
    lines_in_wire2 = parse_wire_instructions(list_of_instructions[1])

    def does_intersect(hline: Line, vline: Line) -> bool:
        horizontal_match = max(hline.p1.x, hline.p2.x) >= vline.p1.x and min(hline.p1.x, hline.p2.x) <= vline.p1.x
        vertical_match = max(vline.p1.y, vline.p2.y) >= hline.p1.y and min(vline.p1.y, vline.p2.y) <= hline.p1.y

        return horizontal_match and vertical_match

    collisions: List[Node] = []
    steps1: int = 0
    steps2: int = 0
    for l1 in lines_in_wire1:
        for l2 in lines_in_wire2:

            if l1.is_horizontal():
                if not l2.is_horizontal():
                    match = does_intersect(l1, l2)
                else:
                    match = True
            else:
                if not l1.is_horizontal():
                    match = does_intersect(l2, l1)
                else:
                    match = True

            if match:
                n = Node()
                n.steps = steps1 + steps2 + l2.p1.x + l1.p1.y
                n.position.x = l2.p1.x
                n.position.y = l1.p1.y
                collisions.append(n)

            steps2 += len(l2)
        steps1 += len(l1)

    return collisions
#
# Part 1
#

def part1(collisions: List[Node]) -> int:
    closest_node: Optional[Node] = None

    def distance_from_center(position: Position) -> int:
        return abs(position.x) + abs(position.y)

    for node in collisions:
        if closest_node is None or distance_from_center(node.position) < distance_from_center(closest_node.position):
           closest_node = node

    assert closest_node is not None
    return distance_from_center(closest_node.position)

assert part1(parse_two_wires([["U3", "R3", "D2", "L2", "U3", "R10"], ["R10", "U10",]])) == 14
assert part1(parse_two_wires([["R8","U5","L5","D3"], ["U7","R6","D4","L4"]])) == 6

assert part1(parse_two_wires([["R75","D30","R83","U83","L12","D49","R71","U7","L72"],
              ["U62","R66","U55","R34","D71","R55","D58","R83"]])) == 159

assert part1(parse_two_wires([["R98","U47","R26","D63","R33","U87","L62","D20","R33","U53","R51"],
              ["U98","R91","D20","R16","D67","R40","U7","R15","U6","R7"]])) == 135

#
# Part 2
#

def part2(collisions: List[Node]) -> int:
    closest_node: Optional[Node] = None

    for node in collisions:
        if closest_node is None or node.steps < closest_node.steps:
            closest_node = node

    assert closest_node is not None
    return closest_node.steps


assert part2(parse_two_wires([["R8","U5","L5","D3"], ["U7","R6","D4","L4"]])) == 30

assert part2(parse_two_wires([["R75","D30","R83","U83","L12","D49","R71","U7","L72"],
              ["U62","R66","U55","R34","D71","R55","D58","R83"]])) == 610

assert part2(parse_two_wires([["R98","U47","R26","D63","R33","U87","L62","D20","R33","U53","R51"],
              ["U98","R91","D20","R16","D67","R40","U7","R15","U6","R7"]])) == 410

#
# Solve
#

with open("day3_input.txt", "r") as f:
    collisions = parse_two_wires([line.split(",") for line in f.readlines() ])

print(f"part1: {part1(collisions)}")
print(f"part2: {part2(collisions)}")
