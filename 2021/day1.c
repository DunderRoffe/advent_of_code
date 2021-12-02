#include <stdint.h>
#include <stdio.h>

#include "utils.h"
#include "day1_input.h"

size_t calc(const uint16_t *puzzle_input,
	    const size_t puzzle_input_len,
	    const uint8_t window_size)
{
	uint16_t prev;
	uint16_t current;
	uint16_t tot = 0;

	prev = 0;
	for (uint8_t j = 0; j < window_size; j++) {
		prev += puzzle_input[j];
	}

	for (size_t i = window_size; i < puzzle_input_len; i++)
	{
		current = 0;
		for (uint8_t j = 0; j < window_size; j++) {
			current += puzzle_input[i + j];
		}

		if (current > prev) {
			tot++;
		}

		prev = current;
	}

	return tot;
}

int main()
{
	printf("day1 a: %u\n", calc(puzzle_input, ARRAY_SIZE(puzzle_input), 1));
	printf("day1 b: %u\n", calc(puzzle_input, ARRAY_SIZE(puzzle_input), 3));
}
