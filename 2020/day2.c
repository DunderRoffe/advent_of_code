#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "day2_input.h"
#include "utils.h"

#define PASS_LEN 20

struct entry {
	int min;
	int max;
	char c;
	char pass[PASS_LEN];
};

void parse_entry(char *input, struct entry  *e)
{
	char *delim1;
	char *delim2;

	delim1 = strchr(input, '-');
	delim2 = strchr(input, ' ');
	e->c = *(delim2 + 1);

	e->min = strtol(input, NULL, 10);
	e->max = strtol((char *) (delim1 + 1), NULL, 10);

	strncpy(e->pass, (char*)(delim2 + 4), PASS_LEN);
}

uint8_t is_valid_sled_entry(const struct entry *e)
{
	uint8_t nr_matches = 0;
	uint8_t i;

	for (i = 0; i < strlen(e->pass); i++) {
		if (e->pass[i] == e->c) {
			nr_matches++;
		}
	}

	return e->min <= nr_matches && e->max >= nr_matches;
}

uint8_t is_valid_toboggan_entry(const struct entry *e)
{
	uint8_t nr_matches = 0;

	nr_matches += e->pass[e->min - 1] == e-> c;
	nr_matches += e->pass[e->max - 1] == e-> c;
	return nr_matches == 1;
}

int main()
{
	int i;
	struct entry e;
	uint16_t nr_valid_sled;
	uint16_t nr_valid_toboggan;

	nr_valid_sled = 0;
	nr_valid_toboggan = 0;

	for (i = 0; i < ARRAY_SIZE(real_input); i++) {
		parse_entry(real_input[i], &e);
		nr_valid_sled += is_valid_sled_entry(&e);
		nr_valid_toboggan += is_valid_toboggan_entry(&e);
	}

	printf("Sled:     %u\n", nr_valid_sled);
	printf("Toboggan: %u\n", nr_valid_toboggan);
}
