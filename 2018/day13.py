
from typing import Dict

NORTH: int = 0
EAST: int = 1
SOUTH: int = 2
WEST: int = 3
NR_OF_DIRECTIONS: int = 4

LEFT: int = 3
STRAIGHT: int = 0
RIGHT: int = 1

def calc_move(heading: int, next_move: int):
    return (heading + next_move) % NR_OF_DIRECTIONS


assert calc_move(NORTH, LEFT) == WEST
print(calc_move(SOUTH, LEFT))
assert calc_move(SOUTH, LEFT) == EAST

class Cart:

    def __init__(self, heading: int):
        self.next_move : int = LEFT
        pass

class Node:

    def __init__(self, ):
        self.directions : Dict[int, Node] = None

    def set_directions(self, directions : Dict[int, Node] = {}):
        self.directions = directions

    def get_directions(self):
        if self.directions is None:
           raise Exception("Directions not set before using Node")

        return self.directions
        

