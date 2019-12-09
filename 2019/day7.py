from typing import List, Iterable, Tuple, Optional
from intcode import run, test, Program

from itertools import permutations

def calc_phase_setting(program: Program, sequence: Iterable[int]) -> int:
    phase_setting = 0

    for i, program_input in enumerate(sequence):
        program.memory_ptr = 0
        _, outputs = run(program, inputs=[program_input, phase_setting])
        assert len(outputs) > 0
        phase_setting = outputs[-1]

    return phase_setting

assert test(calc_phase_setting(Program([3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0]), [4,3,2,1,0]), 43210)
assert test(calc_phase_setting(Program([3,23,3,24,1002,24,10,24,1002,23,-1,23,
101,5,23,23,1,24,23,23,4,23,99,0,0]), [0,1,2,3,4]), 54321)
assert test(calc_phase_setting(Program([3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,
1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0]), [1,0,4,3,2]), 65210)


#
# Part 1
#

def calc_best_phase_setting(initial_memory: List[int]) -> int:
    best_phase_setting = 0

    for order in permutations([0, 1, 2, 3, 4]):
        program = Program(initial_memory)
        phase_setting, _ = calc_phase_setting(program, order)
        best_phase_setting = max(best_phase_setting, phase_setting)

    return best_phase_setting



memory_initial: List[int]
with open("day7_input.txt", "r") as f:
    memory_initial = [ int(cell) for cell in f.readlines()[0].split(",") ]

print(f"Part 1, best phase setting: {calc_best_phase_setting(memory_initial)}")