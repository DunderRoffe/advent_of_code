#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "day2_input.h"

struct state_t {
	int32_t x;
	int32_t y;
	int32_t aim;
};

void parse_a(char puzzle_input[][LEN],
             size_t puzzle_input_len,
	     struct state_t *state)
{
	char *command;
	uint16_t value;

	state->x = 0;
	state->y = 0;

	for (size_t i = 0; i < puzzle_input_len; i++) {
		command = puzzle_input[i];
		value = strtoul(strchr(command, ' ') + 1, NULL, 10);

		switch (command[0]) {
		case 'f' : state->x += value; break;
		case 'd': state->y += value; break;
		case 'u': state->y -= value; break;
		}
	}
}

void parse_b(char puzzle_input[][LEN],
             size_t puzzle_input_len,
	     struct state_t *state)
{
	char *command;
	uint16_t value;

	state->x = 0;
	state->y = 0;
	state->aim = 0;

	for (size_t i = 0; i < puzzle_input_len; i++) {
		command = puzzle_input[i];
		value = strtoul(strchr(command, ' ') + 1, NULL, 10);

		switch (command[0]) {
		case 'f' : state->x += value;
			   state->y += state->aim * value;
			   break;
		case 'd': state->aim += value; break;
		case 'u': state->aim -= value; break;
		}
	}
}

int main()
{
	struct state_t state;

	parse_a(puzzle_input, ARRAY_SIZE(puzzle_input), &state);
	printf("day2 a: %i\n", state.x * state.y);

	parse_b(puzzle_input, ARRAY_SIZE(puzzle_input), &state);
	printf("day2 b: %i\n", state.x * state.y);
}
