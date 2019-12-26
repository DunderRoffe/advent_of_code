#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define TEN_MILLION 10000000u


uint8_t match(const uint8_t *score_board, const uint64_t score_board_used_size, const uint8_t *match_list, const uint8_t match_list_size, const uint8_t score_len_diff)
{
	uint8_t i;
	uint8_t score_at_i;

	if (score_len_diff > 1 && match(score_board, score_board_used_size,
	                          match_list, match_list_size, score_len_diff - 1)) {
		return 1;
	}

	for (i = 0; i < match_list_size; i++) {
		score_at_i = score_board[score_board_used_size - match_list_size - score_len_diff + 1 + i];
//		printf("%u == %u ?\n", score_at_i, match_list[i]);
		if (score_at_i != match_list[i]) {
			return 0;
		}
	}
	return 1;
}

void print_score_board(const uint8_t *score_board, const uint64_t used_size, uint64_t elf_1, uint64_t elf_2)
{
	uint64_t i;
	for (i = 0; i < used_size; i++) {
		if (i == elf_1) {
			printf("(%u)", score_board[i]);
		}
		else if (i == elf_2) {
			printf("[%u]", score_board[i]);
		} else {
			printf(" %u ", score_board[i]);
		}
	}
	printf("\n");
}

uint8_t* allocate_more_space(uint8_t* score_board, const uint64_t used_size, const uint64_t allocated_size)
{
	uint64_t i;
	uint8_t *new_board;

	new_board = malloc(sizeof(uint8_t) * (allocated_size + TEN_MILLION));

	for (i = 0; i < used_size; i ++) {
		new_board[i] = score_board[i];
	}

	free(score_board);

	return new_board;
}

uint64_t solve(const uint8_t *match_list, const uint8_t match_list_size)
{
	uint8_t *score_board;
        uint64_t used_size = 0;
        uint64_t allocated_size = TEN_MILLION;

        score_board = malloc(sizeof(uint8_t) * TEN_MILLION);

        score_board[used_size++] = 3;
        score_board[used_size++] = 7;

        uint64_t elf_1 = 0;
        uint64_t elf_2 = 1;

        uint8_t found_match = 0;

        uint8_t sum_elf_recipes;

        while (!found_match) {
		if (used_size + 2 >= allocated_size) {
			score_board = allocate_more_space(score_board, used_size, allocated_size);
			allocated_size += TEN_MILLION;
			assert(allocated_size > used_size);
		}

		sum_elf_recipes = score_board[elf_1] + score_board[elf_2];

#ifdef DEBUG
		print_score_board(score_board, used_size, elf_1, elf_2);
#endif

		if (sum_elf_recipes >= 10) {
			score_board[used_size++] = (uint8_t)((float)sum_elf_recipes / 10.0F);
			score_board[used_size++] = sum_elf_recipes % 10;
			found_match = match(score_board, used_size,
		        	            match_list, match_list_size, 2);
		} else {
			score_board[used_size++] = sum_elf_recipes;
			found_match = match(score_board, used_size,
		        	            match_list, match_list_size, 1);
		}
      		
		elf_1 = (elf_1 + score_board[elf_1] + 1) % used_size; 
		elf_2 = (elf_2 + score_board[elf_2] + 1) % used_size; 

		assert(elf_1 < used_size);
		assert(elf_2 < used_size);

#ifdef DEBUG
		getchar();
#endif
        }

	free(score_board);
	printf("Solution: %lu\n", used_size - match_list_size);
	return used_size - match_list_size;
}

int  main() {

#ifdef TEST
	printf("match test1\n");
	uint8_t match_test_1_score[] = {0, 0, 1, 2, 3};
	uint8_t match_test_1_match[] = {1, 2, 3};
	assert(match(match_test_1_score, 5u, match_test_1_match, 3u, 1));

	printf("match test2\n");
	uint8_t match_test_2_score[] = {0, 0, 1, 2, 3, 0};
	uint8_t match_test_2_match[] = {1, 2, 3};
	assert(match(match_test_2_score, 6u, match_test_2_match, 3u, 2));

	printf("match test3\n");
	uint8_t match_test_3_score[] = {0, 0, 0, 1, 2, 3};
	uint8_t match_test_3_match[] = {1, 2, 3};
	assert(match(match_test_3_score, 6u, match_test_3_match, 3u, 2));
    
    
	printf("solve test1\n");
	uint8_t test1[] = {5, 1, 5, 8, 9};
        assert(solve(test1, 5u) == 9);

	printf("solve test2\n");
	uint8_t test2[] = {0, 1, 2, 4, 5}; assert(solve(test2, 5u) == 5);

	printf("solve test3\n");
	uint8_t test3[] = {9, 2, 5, 1, 0}; assert(solve(test3, 5u) == 18);

	printf("solve test4\n");
	uint8_t test4[] = {5, 9, 4, 1, 4}; assert(solve(test4, 5u) == 2018);
#endif

	uint8_t input[] = {4, 0, 9, 5, 5, 1};
	solve(input, 6u);
}
