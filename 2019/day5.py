from typing import List, Optional, Any, Iterable, Tuple

def test(given: Any, expected: Any) -> bool:
    ret = given == expected
    if not ret:
        print(f"{given} != {expected}")

    return ret

def using_mode(mode: int, memory: List[int], address: int) -> int:

    if mode == 0:
        return memory[address]
    elif mode == 1:
        return address
    else:
        raise Exception(f"Unkown mode: {mode}")

def get_param(memory: List[int], op_ptr: int, param_nr: int = 0) -> int:
    mode = (memory[op_ptr] // (10 ** (2 + param_nr))) % 10
    return using_mode(mode, memory, op_ptr + param_nr + 1)


def get_params(nr_of_params: int, memory: List[int], op_ptr: int) -> Iterable[int]:
    for i in range(nr_of_params):
        yield get_param(memory, op_ptr, param_nr=i)

def run(memory: List[int], inputs: List[int] = [], debug=False) -> Tuple[List[int], List[int]]:
    memory_ptr: int = 0
    input_ptr: int = 0
    outputs: List[int] = list()

    while True:

        opcode = memory[memory_ptr] % 100
        if debug: print(f"opcode: {opcode} {memory_ptr}")

        if opcode == 1:
            # Addition
            nr_of_params = 3
            term1_ptr, term2_ptr, result_ptr = get_params(nr_of_params, memory, memory_ptr)

            memory[result_ptr] = memory[term1_ptr] + memory[term2_ptr]
            memory_ptr += nr_of_params + 1
 
        elif opcode == 2:
            # Multiplication
            nr_of_params = 3
            factor1_ptr, factor2_ptr, result_ptr = get_params(nr_of_params, memory, memory_ptr)

            memory[result_ptr] = memory[factor1_ptr] * memory[factor2_ptr]
            memory_ptr += nr_of_params + 1

        elif opcode == 3:
            # Read input
            nr_of_params = 1
            result_ptr = get_param(memory, memory_ptr)

            assert len(inputs) > input_ptr
            memory[result_ptr] = inputs[input_ptr]
            input_ptr += 1
            memory_ptr += nr_of_params + 1

        elif opcode == 4:
            # Output memory
            nr_of_params = 1
            output_ptr = get_param(memory, memory_ptr)

            outputs.append(memory[output_ptr])
            memory_ptr += nr_of_params + 1

        elif opcode == 99:
            # Halt
            return (memory, outputs)

        else:
            raise Exception(f"Unknown opcode {opcode}")


assert test(run([1, 0, 0, 0, 99])               , ([2, 0, 0, 0, 99],[]))
assert test(run([2, 3, 0, 3, 99 ])              , ([2, 3, 0, 6, 99],[]))
assert test(run([2, 4, 4, 5, 99, 0 ])           , ([2, 4, 4, 5, 99, 9801],[]))
assert test(run([1, 1, 1, 4, 99, 5, 6, 0, 99 ]) , ([30, 1, 1, 4, 2, 5, 6, 0,99],[]))

assert test(run([1002,4,3,4,33]), ([1002, 4, 3, 4, 99], []))
assert test(run([3, 0, 4, 0, 99], inputs=[1]), ([1, 0, 4, 0, 99], [1]))


#
# Part 1
#

memory_initial: List[int]
with open("day5_input.txt", "r") as f:
    memory_initial = [ int(cell) for cell in f.readlines()[0].split(",") ]

memory = memory_initial.copy()
memory, outputs = run(memory, inputs=[1], debug=True)
print(f"Part 1: Diagnostics code {outputs[-1]}")

