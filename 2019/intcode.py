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


class Program():
    memory: List[int]
    memory_ptr: int = 0

    def __init__(self, initial_memory: List[int]):
        self.memory = initial_memory.copy()


def get_param(program: Program, param_nr: int = 0) -> int:
    mode = (program.memory[program.memory_ptr] // (10 ** (2 + param_nr))) % 10
    return using_mode(mode, program.memory, program.memory_ptr + param_nr + 1)


def get_params(nr_of_params: int, program: Program) -> Iterable[int]:
    for i in range(nr_of_params):
        yield get_param(program, param_nr=i)


def run(program: Program, inputs: List[int] = [], debug=False) -> Tuple[Program, List[int]]:
    input_ptr: int = 0
    outputs: List[int] = list()

    while True:

        opcode = program.memory[program.memory_ptr] % 100
        if debug: print(f"opcode: {opcode} {program.memory_ptr}")

        if opcode == 1:
            # Addition
            nr_of_params = 3
            term1_ptr, term2_ptr, result_ptr = get_params(nr_of_params, program)

            program.memory[result_ptr] = program.memory[term1_ptr] + program.memory[term2_ptr]
            program.memory_ptr += nr_of_params + 1
 
        elif opcode == 2:
            # Multiplication
            nr_of_params = 3
            factor1_ptr, factor2_ptr, result_ptr = get_params(nr_of_params, program)

            program.memory[result_ptr] = program.memory[factor1_ptr] * program.memory[factor2_ptr]
            program.memory_ptr += nr_of_params + 1

        elif opcode == 3:
            # Read input
            nr_of_params = 1
            result_ptr = get_param(program)

            # If no more input is available stop executing
            # and wait for more input
            if len(inputs) <= input_ptr:
               if debug: print("Out of inputs, waiting for more...")
               return program, outputs

            program.memory[result_ptr] = inputs[input_ptr]
            input_ptr += 1
            program.memory_ptr += nr_of_params + 1

        elif opcode == 4:
            # Output memory
            nr_of_params = 1
            output_ptr = get_param(program)

            outputs.append(program.memory[output_ptr])
            program.memory_ptr += nr_of_params + 1

        elif opcode == 5:
            # Jump if true
            nr_of_params = 2
            condition_ptr, jump_ptr_ptr = get_params(nr_of_params, program)

            if program.memory[condition_ptr] != 0:
                program.memory_ptr = program.memory[jump_ptr_ptr]

            else:
                program.memory_ptr += nr_of_params + 1

        elif opcode == 6:
            # Jump if false
            nr_of_params = 2
            condition_ptr, jump_ptr_ptr = get_params(nr_of_params, program)

            if program.memory[condition_ptr] == 0:
                program.memory_ptr = program.memory[jump_ptr_ptr]

            else:
                program.memory_ptr += nr_of_params + 1

        elif opcode == 7:
            # less than
            nr_of_params = 3
            param1_ptr, param2_ptr, store_ptr = get_params(nr_of_params, program)

            if program.memory[param1_ptr] < program.memory[param2_ptr]:
                program.memory[store_ptr] = 1
            else:
                program.memory[store_ptr] = 0

            program.memory_ptr += nr_of_params + 1

        elif opcode == 8:
            # equals
            nr_of_params = 3
            param1_ptr, param2_ptr, store_ptr = get_params(nr_of_params, program)

            if program.memory[param1_ptr] == program.memory[param2_ptr]:
                program.memory[store_ptr] = 1
            else:
                program.memory[store_ptr] = 0

            program.memory_ptr += nr_of_params + 1

        elif opcode == 99:
            # Halt
            return program, outputs

        else:
            raise Exception(f"Unknown opcode {opcode}")


def program_test(given_memory, given_inputs=[],
                 expected_mem = None, expected_outputs = None,
                 expected_mem_ptr = None):

    program = Program(given_memory)
    _ , outputs = run(program, given_inputs)

    if expected_mem is not None:
       assert test(program.memory, expected_mem)

    if expected_mem_ptr is not None:
       assert test(program.memory_ptr, expected_mem_ptr)

    if expected_outputs is not None:
       assert test(outputs, expected_outputs)

program_test([1, 0, 0, 0, 99], expected_mem = [2, 0, 0, 0, 99])
program_test([2, 3, 0, 3, 99 ], expected_mem = [2, 3, 0, 6, 99])
program_test([2, 4, 4, 5, 99, 0 ], expected_mem = [2, 4, 4, 5, 99, 9801])
program_test([1, 1, 1, 4, 99, 5, 6, 0, 99 ], expected_mem = [30, 1, 1, 4, 2, 5, 6, 0,99])

program_test([1002,4,3,4,33], expected_mem = [1002, 4, 3, 4, 99])
program_test([3, 0, 4, 0, 99], [1],
             expected_mem = [1, 0, 4, 0, 99], expected_outputs = [1])

# Test equal
program_test([3,9,8,9,10,9,4,9,99,-1,8], [8],
             expected_outputs = [1])
program_test([3,9,8,9,10,9,4,9,99,-1,8], [7],
             expected_outputs = [0])

program_test([3,3,1108,-1,8,3,4,3,99], [8], expected_outputs = [1])
program_test([3,3,1108,-1,8,3,4,3,99], [7], expected_outputs = [0])

# Test less than
program_test([3,9,7,9,10,9,4,9,99,-1,8], [7], expected_outputs = [1])
program_test([3,9,7,9,10,9,4,9,99,-1,8], [8], expected_outputs = [0])

program_test([3,3,1107,-1,8,3,4,3,99], [7], expected_outputs = [1])
program_test([3,3,1107,-1,8,3,4,3,99], [8], expected_outputs = [0])
