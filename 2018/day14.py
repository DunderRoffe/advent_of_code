from typing import List, Tuple

def list_to_string(ls):
    return "".join(str(e) for e in ls)

def print_score_board(score_board: List[int], elf_1: int, elf_2: int):
    score_board_str = list_to_string(score_board)
    if elf_1 < elf_2:
        print("{}({}){}[{}]{}".format(
            " ".join(score_board_str[:elf_1]), \
            score_board_str[elf_1], \
            " ".join(score_board_str[elf_1 + 1: elf_2]), \
            score_board_str[elf_2], \
            " ".join(score_board_str[elf_2 + 1:]) \
        ))
    elif elf_1 > elf_2:
        print("{}({}){}[{}]{}".format(
            " ".join(score_board_str[:elf_2]), \
            score_board_str[elf_2], \
            " ".join(score_board_str[elf_2 + 1: elf_1]), \
            score_board_str[elf_1], \
            " ".join(score_board_str[elf_1 + 1:]) \
        ))

def create_new_recipes(score_board: List[int], elf_1: int, elf_2: int) -> Tuple[List[int], int, int] :
    sum_elf_recipes: int = score_board[elf_1] + score_board[elf_2]
    if sum_elf_recipes >= 10:
       score_board.append(int(sum_elf_recipes / 10))
       score_board.append(int(sum_elf_recipes % 10))
    else:
       score_board.append(sum_elf_recipes)

    len_score_board = len(score_board)
    elf_1 = (elf_1 + score_board[elf_1] + 1) % len_score_board
    elf_2 = (elf_2 + score_board[elf_2] + 1) % len_score_board

    return (score_board, elf_1, elf_2)

recipes = create_new_recipes([3, 7], 0, 1) 
assert recipes == ([3, 7, 1, 0], 0, 1)
assert create_new_recipes(*recipes) == ([3, 7, 1, 0, 1, 0], 4, 3)



def part1(nr_learning_recipes: int):
    score_board: List[int] = [3, 7]

    elf_1: int = 0
    elf_2: int = 1

    print_score_board(score_board, elf_1, elf_2)
    create_more_recipes = True
    while create_more_recipes:
        score_board, elf_1, elf_2 = create_new_recipes(score_board, elf_1, elf_2)
        #print_score_board(score_board, elf_1, elf_2)

        if len(score_board) > nr_learning_recipes + 10:
           create_more_recipes = False
           result_list = score_board[nr_learning_recipes: nr_learning_recipes + 10]
           print(list_to_string(result_list))

        elif len(score_board) < nr_learning_recipes:
           print("{} recipes left of learning process...".format(\
                     nr_learning_recipes - len(score_board)))
    

def part2(match_list: List[int]):
    score_board: List[int] = [3, 7]

    elf_1: int = 0
    elf_2: int = 1

    match_len = len(match_list)
    score_len: int = len(score_board)
    match: bool = False

    while not match:

        sum_elf_recipes: int = score_board[elf_1] + score_board[elf_2]
        if sum_elf_recipes >= 10:
           score_board.append( int(sum_elf_recipes / 10) )
           score_board.append( int(sum_elf_recipes % 10) )
           score_len_diff = 2
        else:
           score_board.append(sum_elf_recipes)
           score_len_diff = 1
 
        score_len += score_len_diff

        elf_1 = (elf_1 + score_board[elf_1] + 1) % score_len
        elf_2 = (elf_2 + score_board[elf_2] + 1) % score_len

        match = score_board[-match_len - score_len_diff + 1: - score_len_diff + 1] == match_list

    print(score_len - match_len - score_len_diff + 1)

part2([4, 0, 9, 5, 5, 1])
