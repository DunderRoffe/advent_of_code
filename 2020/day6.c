#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "utils.h"
#include "day6_input.h"

uint32_t parse_person(char p_input[LINE_MAX], size_t p_input_len)
{
	int i;
	uint32_t ret;

	ret = 0;
	for (i = 0; i < p_input_len; i++) {
		ret |= 1 << (p_input[i] - 'a');
	}

	return ret;
}

uint32_t reset_ret(uint8_t any) {
	if (any) {
		return 0;
	} else {
		return -1;
	}
}

uint8_t count_bits(uint32_t sum)
{
	uint8_t temp = 0;

	while (sum > 0)
	{
		if (sum & 1 == 1) {
			temp++;
		}
		sum = sum >> 1;
	}

	return temp;
}

uint16_t parse_groups(char g_input[][LINE_MAX], size_t g_input_len, uint8_t any)
{
	int i;
	uint32_t ret;
	uint16_t total;
	size_t p_input_len;

	total = 0;
	ret = reset_ret(any);

	for (i = 0; i < g_input_len; i++) {
		p_input_len = strlen(g_input[i]);

		if (p_input_len < 1) {
			total += count_bits(ret);
			ret = reset_ret(any);
		}
		else if (any) {
			ret |= parse_person(g_input[i], p_input_len);
		}
		else {
			ret &= parse_person(g_input[i], p_input_len);
		}
	}

	return total;
}

int main()
{
	uint16_t total;

	total = parse_groups(test_input, ARRAY_SIZE(test_input), 1);
	assert(total == 11);

	total = parse_groups(test_input, ARRAY_SIZE(test_input), 0);
	assert(total == 6);

	total = parse_groups(real_input, ARRAY_SIZE(real_input), 1);
	printf("%u\n", total);

	total = parse_groups(real_input, ARRAY_SIZE(real_input), 0);
	printf("%u\n", total);
	return 0;
}
