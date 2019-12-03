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


def parse_wire_instructions(wire_instructions: List[str], cells: Dict[int, Node], is_wire_1: bool) -> List[Node]:
    collisions: List[Node] = list()
    next_position = Position()
    steps: int = 0

    for instr in wire_instructions:
        direction: str = instr[0]
        length: int = int(instr[1:])

        for i in range(length):
            steps += 1
            if direction == "R":
               next_position.x += 1
            elif direction == "L":
               next_position.x -= 1
            elif direction == "U":
               next_position.y += 1
            elif direction == "D":
               next_position.y -= 1
            else:
               raise Exception(f"Parse error: Illegal direction '{direction}'")

            temp_position = next_position.copy()
            temp_hash = hash(temp_position)
            if temp_hash not in cells:
                pointer = Node()
                cells[temp_hash] = pointer
                pointer.position = temp_position
            else:
                pointer = cells[temp_hash]

            if is_wire_1:
                pointer.steps = steps

            elif pointer.steps != -1:
                pointer.steps += steps
                collisions.append(pointer)

    return collisions

def parse_two_wires(list_of_instructions: List[List[str]]) -> List[Node]:
    cells: Dict[int, Node] = dict()

    cells[hash(Position())] = Node()

    parse_wire_instructions(list_of_instructions[0], cells, is_wire_1=True)
    return parse_wire_instructions(list_of_instructions[1], cells, is_wire_1=False)

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
