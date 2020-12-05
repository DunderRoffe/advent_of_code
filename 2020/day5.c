#define ROWS 128
#define COLS 8

#define ROW_ENTRIES 7

#include <assert.h>
#include <stdio.h>
#include <stdint.h>

#include "utils.h"
#include "day5_input.h"

struct seat {
	uint16_t id;
	uint8_t row;
	uint8_t col;
};

uint8_t inner_parse(char line[SEATLINE], uint8_t i, uint8_t end, char min_char, uint8_t max)
{
	uint8_t min = 0;
	for (; i < end; i++)
	{
		if (max - min == 1) {
			if (line[i] == min_char) {
				return min;
			} else {
				return max;
			}
		}
		else if (line[i] == min_char) {
			max = min + ((max - min) / 2);
		} else {
			min = max - ((max - min) / 2);
		}

	}

}

void parse_seat(char line[SEATLINE], struct seat *s)
{
	s->row = inner_parse(line, 0, ROW_ENTRIES, 'F', ROWS - 1);
	s->col = inner_parse(line, ROW_ENTRIES, SEATLINE - 1, 'L', COLS - 1);
	s->id = s->row * 8 + s->col;
}

uint16_t highest_seat_id(char lines[][SEATLINE], size_t lines_len)
{
	struct seat s;
	size_t i;
	uint16_t max;

	max = 0;

	for (i = 0; i < lines_len; i++)
	{
		parse_seat(lines[i], &s);
		if (s.id > max) {
			max = s.id;
		}
	}

	return max;
}

#define MAX_SEATS 1000
static struct seat seats[MAX_SEATS];
uint16_t find_seat(char lines[][SEATLINE], size_t lines_len)
{
	struct seat s;
	uint16_t max;
	size_t i;

	max = highest_seat_id(lines, lines_len);

	for (i = 0; i < MAX_SEATS; i++)
	{
		seats[i].id = 0;
		seats[i].row = 0;
		seats[i].col = 0;
	}

	for (i = 0; i < lines_len; i++)
	{
		parse_seat(lines[i], &s);
		seats[s.id] = s;
	}

	for (i = 1; i < max - 1; i++)
	{
		if (seats[i].id == 0) {
			if (seats[i - 1].id > 0) {
				if (seats[i + 1].id > 0) {
					return i;
					printf("%u\n", i);
				}
			}
		}
	}

	return 0;
}

int main() {
	struct seat s;
	char l[SEATLINE] = "FBFBBFFRLR";
	uint16_t max;
	parse_seat(l, &s);
	assert(s.row == 44 && s.col == 5 && s.id == 357);

	max = highest_seat_id(test_input, ARRAY_SIZE(test_input));
	assert(max == 820);

	max = highest_seat_id(real_input, ARRAY_SIZE(real_input));
	printf("A: %u\n", max);

	max = find_seat(real_input, ARRAY_SIZE(real_input));
	printf("B: %u\n", max);
}
