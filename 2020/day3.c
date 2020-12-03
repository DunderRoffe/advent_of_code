#include <assert.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "day3_input.h"
#include "utils.h"

#define TREE '#'

struct vec2 {
	int16_t x;
	int16_t y;
};

uint16_t check_path(char map[][MAP_MAX_WIDTH], size_t map_height, struct vec2 *dir)
{
	struct vec2 pos;
	uint8_t map_width;
	uint16_t nr_trees;

	pos.x = 0;
	pos.y = 0;

	nr_trees = 0;
	map_width = strlen(map[0]);

	while ((pos.y + dir->y) < map_height)
	{
		pos.x = (pos.x + dir->x) % map_width;
		pos.y = pos.y + dir->y;

		if (map[pos.y][pos.x] == TREE) {
			nr_trees++;
		}
	}

	return nr_trees;
}

uint32_t check_multi_path(char map[][MAP_MAX_WIDTH], size_t map_height)
{
	struct vec2 dirs[] = {
		{ .x = 1, .y = 1},
		{ .x = 3, .y = 1},
		{ .x = 5, .y = 1},
		{ .x = 7, .y = 1},
		{ .x = 1, .y = 2}
	};

	uint32_t res = 1;
	uint16_t hits;
	size_t i;

	for (i = 0; i < ARRAY_SIZE(dirs); i++) {
		res *= check_path(map, map_height, &dirs[i]);
	}

	return res;
}

int main()
{
	struct vec2 dir = { .x = 3, .y = 1};
	uint32_t res;

	res = check_path(test_input, ARRAY_SIZE(test_input), &dir);
	assert(res = 7);
	res = check_multi_path(test_input, ARRAY_SIZE(test_input));
	assert(res = 336);

	res = check_path(real_input, ARRAY_SIZE(real_input), &dir);
	printf("A: %u\n", res);
	res = check_multi_path(real_input, ARRAY_SIZE(real_input));
	printf("B: %u\n", res);

	return 0;
}
