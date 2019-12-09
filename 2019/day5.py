from typing import List, Optional, Any, Iterable, Tuple

from intcode import run, test

#
# Solutions
#

memory_initial: List[int]
with open("day5_input.txt", "r") as f:
    memory_initial = [ int(cell) for cell in f.readlines()[0].split(",") ]

memory = memory_initial.copy()
_, outputs = run(memory, inputs=[1])
print(f"Part 1: Diagnostics code {outputs[-1]}")


memory = memory_initial.copy()
_, outputs = run(memory, inputs=[5])
print(f"Part 2: Diagnostics code {outputs[-1]}")
