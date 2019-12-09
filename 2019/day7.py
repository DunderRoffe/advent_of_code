from typing import List, Iterable, Tuple, Optional
from intcode import run, test, Program
from itertools import permutations


def calc_phase_setting(initial_memory: List[int], sequence: Iterable[int]) -> int:
    phase_setting = 0
    programs: List[Program] = []
    halted = False

    while not halted:
        for i, program_input in enumerate(sequence):
            if len(programs) <= i:
               programs.append(Program(initial_memory))

               # Run with program_input only first time
               _, outputs = run(programs[i], inputs=[program_input, phase_setting])
            else:
               # Already added -> has run at least once already
               _, outputs = run(programs[i], inputs=[phase_setting])
               
            assert len(outputs) > 0
            phase_setting = outputs[-1]
        
            halted = programs[i].memory[programs[i].memory_ptr] == 99
            if halted:
                programs[i].memory_ptr = 0

    return phase_setting


assert test(calc_phase_setting([3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0], [4,3,2,1,0]), 43210)
assert test(calc_phase_setting([3,23,3,24,1002,24,10,24,1002,23,-1,23,
101,5,23,23,1,24,23,23,4,23,99,0,0], [0,1,2,3,4]), 54321)
assert test(calc_phase_setting([3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,
1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0], [1,0,4,3,2]), 65210)

# feedback
assert test(calc_phase_setting([3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,
27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5], [9, 8, 7, 6,5]), 139629729)

assert test(calc_phase_setting([3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
-5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10], [9, 7, 8, 5, 6]), 18216)


def calc_best_phase_setting(initial_memory: List[int], phase_range: List[int]) -> int:
    best_phase_setting = 0

    for order in permutations(phase_range):
        phase_setting = calc_phase_setting(initial_memory, order)
        best_phase_setting = max(best_phase_setting, phase_setting)

    return best_phase_setting


#
# Solve
#

memory_initial: List[int]
with open("day7_input.txt", "r") as f:
    memory_initial = [ int(cell) for cell in f.readlines()[0].split(",") ]

print(f"Part 1: {calc_best_phase_setting(memory_initial, [0, 1, 2, 3, 4])}")
print(f"Part 2: {calc_best_phase_setting(memory_initial, [5, 6, 7, 8, 9])}")
