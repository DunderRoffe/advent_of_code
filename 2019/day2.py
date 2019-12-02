from typing import List

def run(memory: List[int]) -> List[int]:
    memory_ptr: int = 0
    opcode: int = memory[memory_ptr]

    while opcode != 99:
        result_ptr: int

        if opcode == 1:
            term1_ptr: int = memory[memory_ptr + 1]
            term2_ptr: int = memory[memory_ptr + 2]
            result_ptr = memory[memory_ptr + 3]

            memory[result_ptr] = memory[term1_ptr] + memory[term2_ptr]
            memory_ptr += 4
 
        if opcode == 2:
            factor1_ptr: int = memory[memory_ptr + 1]
            factor2_ptr: int = memory[memory_ptr + 2]
            result_ptr = memory[memory_ptr + 3]

            memory[result_ptr] = memory[factor1_ptr] * memory[factor2_ptr]
            memory_ptr += 4
 
        opcode = memory[memory_ptr]

    return memory

assert run([1, 0, 0, 0, 99])               == [2, 0, 0, 0, 99]
assert run([2, 3, 0, 3, 99 ])              == [2, 3, 0, 6, 99]
assert run([2, 4, 4, 5, 99, 0 ])           == [2, 4, 4, 5, 99, 9801]
assert run([1, 1, 1, 4, 99, 5, 6, 0, 99 ]) == [30, 1, 1, 4, 2, 5, 6, 0,99]


#
# Part 1
#

memory_initial: List[int]
with open("day2_input.txt", "r") as f:
    memory_initial = [ int(cell) for cell in f.readlines()[0].split(",") ]

memory = memory_initial.copy()
memory[1] = 12
memory[2] = 2
run(memory)
print(f"Part 1: {memory[0]}")


#
# Part 2
#

for noun in range(100):
    for verb in range(100):
        memory = memory_initial.copy()
        memory[1] = noun
        memory[2] = verb
        run(memory)

        if memory[0] == 19690720:
            print(f"Part 2: {(100 * noun) + verb}")
