from typing import Optional, Dict, Tuple, List, Iterable

class Node:
    orbits: Optional["Node"] = None
    total_orbits: int = 0


def cascade_orbit_count_increase(node: Node, amount: int):
    node.total_orbits += amount
    if node.orbits != None:
        cascade_orbit_count_increase(node.orbits, amount)


def get_node(node_map: Dict[str, Node], node_name: str) -> Node:

    node_name = node_name.strip("\n")
    if node_name not in node_map:
       n = Node()
       node_map[node_name] = n

    return node_map[node_name]


def parse(node_map: Dict[str, Node], lines) -> None:
    for line in lines:
        orbited_node_name, orbiting_node_name = line.split(")")
            
        orbiting_node = get_node(node_map, orbiting_node_name)
        orbited_node = get_node(node_map, orbited_node_name)

        assert orbiting_node.orbits == None
        orbiting_node.orbits = orbited_node
        cascade_orbit_count_increase(orbited_node, orbiting_node.total_orbits + 1)


def calc_orbits(all_nodes: Iterable[Node]) -> int:
    total_nr_orbits: int = 0

    for node in all_nodes:
        total_nr_orbits += node.total_orbits

    return total_nr_orbits


test_input = [
    "D)I",
    "B)C",
    "E)J",
    "J)K",
    "C)D",
    "B)G",
    "D)E",
    "K)L",
    "E)F",
    "G)H",
    "COM)B",
]


test_map: Dict[str, Node] = dict()
parse(test_map, test_input)

assert calc_orbits(test_map.values()) == 42

#
# Part 1
#

real_map = dict()
with open("day6_input.txt", "r") as f:
    parse(real_map, f.readlines())

print(calc_orbits(real_map.values()))
