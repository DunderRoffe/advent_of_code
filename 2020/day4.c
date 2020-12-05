#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "day4_input.h"
#include "utils.h"

#define KEY_LEN 4
#define VALUE_LEN 20

struct passport {
	int32_t byr;
	int32_t cid;
	int32_t eyr;
	char ecl[VALUE_LEN];
	int32_t iyr;
	char hgt[VALUE_LEN];
	char hcl[VALUE_LEN];
	char pid[VALUE_LEN];

};

struct pair {
	char key[KEY_LEN];
	char value[VALUE_LEN];
};

char *nxt(char *data, struct pair *kv)
{
	char *nxt;
	char *div;
	char *val_str;
	size_t value_len;

	nxt = strchr(data, ' ');
	div = strchr(data, ':');
	val_str = (char *) (div + 1);
	if (nxt) {
		*nxt = '\0';
	}

	value_len = strlen(val_str);
	assert(value_len < VALUE_LEN);

	if (nxt) {
		*nxt = ' ';
		nxt++;
	}

	memcpy(kv->key, data, KEY_LEN - 1);
	memcpy(kv->value, val_str, value_len);

	assert(strchr(kv->value, ':') == NULL);
	assert(strchr(kv->value, ' ') == NULL);
	assert(strlen(kv->key) == KEY_LEN - 1);

	return nxt;
}

void add_to_passport(struct passport *pass, struct pair *p)
{
	if (strcmp(p->key, "byr") == 0) {
		pass->byr = strtol(p->value, NULL, 10);
	}

	else if (strcmp(p->key, "cid") == 0) {
		pass->cid = strtol(p->value, NULL, 10);	  
	}

	else if (strcmp(p->key, "eyr") == 0) {
		pass->eyr = strtol(p->value, NULL, 10);
	}

	else if (strcmp(p->key, "ecl") == 0) {
		strcpy(pass->ecl, p->value);
	}

	else if (strcmp(p->key, "iyr") == 0) {
		pass->iyr = strtol(p->value, NULL, 10);
	}

	else if (strcmp(p->key, "hgt") == 0) {
		strncpy(pass->hgt, p->value, strlen(p->value));
	}

	else if (strcmp(p->key, "hcl") == 0) {
		strcpy(pass->hcl, p->value);
	}

	else if (strcmp(p->key, "pid") == 0) {
		strcpy(pass->pid, p->value);
	}
	
	else {
		printf("Unparsable key: %s\n", p->key);
	}
}

uint8_t naive_is_valid(struct passport *pass)
{
	if (pass->byr == -1) {
		return 0;
	}

	if (pass->eyr == -1) {
		return 0;
	}

	if (pass->iyr == -1) {
		return 0;
	}

	if (strlen(pass->ecl) == 0) {
		return 0;
	}

	if (strlen(pass->hgt) == 0) {
		return 0;
	}

	if (strlen(pass->hcl) == 0) {
		return 0;
	}

	if (strlen(pass->pid) == 0) {
		return 0;
	}

	return 1;
	
}

static char valid_colors[][4] = {
	"amb", "blu", "brn", "gry",
       	"grn", "hzl", "oth"
};

uint8_t better_is_valid(struct passport *pass)
{
	int i;
	uint8_t valid;
	size_t len;

	if (pass->byr < 1920 || pass->byr > 2002) {
		return 0;
	}

	if (pass->eyr < 2020 || pass->eyr > 2030) {
		return 0;
	}

	if (pass->iyr < 2010 || pass->iyr > 2020) {
		return 0;
	}

	if (strlen(pass->ecl) == 0) {
		return 0;
	}
	else {

		valid = 0;

		for (i = 0; i < ARRAY_SIZE(valid_colors); i++) {
			if (strcmp(pass->ecl, valid_colors[i]) == 0) {
				valid = 1;
			}
		}

		if (!valid) {
			return 0;
		}
	}

	len = strlen(pass->hgt);
	if (len < 3) {
		return 0;
	} else {
		i = strtol(pass->hgt, NULL, 10);
		if (pass->hgt[len - 1] == 'n' && (i < 59 || i > 76)) {
			return 0;
		}
		if (pass->hgt[len - 1] == 'm' && (i < 150 || i > 193)) {
			return 0;
		}
	}

	len = strlen(pass->hcl);
	if (len != 7) {
		return 0;
	} else {
		if (pass->hcl[0] != '#') {
			return 0;
		}
		for (i = 1; i < 7; i++) {
			if ((pass->hcl[i] < 'a' || pass->hcl[i] > 'f')
			    && (pass->hcl[i] < 'A' || pass->hcl[i] > 'F')
			    && (pass->hcl[i] < '0' || pass->hcl[i] > '9'))
		       	{
				return 0;
			}
		}
	}

	if (strlen(pass->pid) != 9) {
		return 0;
	} else {
		for (i = 0; i < 9; i++) {
			if (pass->pid[i] < '0' || pass->pid[i] > '9')
		       	{
				return 0;
			}
		}
	}

	return 1;
	
}

void reset_passport(struct passport *pass)
{
	memset(pass, 0, sizeof(*pass));
	pass->byr = -1;
	pass->eyr = -1;
	pass->iyr = -1;
}

uint16_t check_passports(char lst[][MAX_LINE], size_t lst_len,
                         uint8_t (*is_valid)(struct passport *pass))
{
	struct pair p;
	size_t i;

	char *ptr;

	uint16_t nr_valid;
	struct passport pass;
	nr_valid = 0;
	reset_passport(&pass);
	
	for (i = 0; i < lst_len; i++) {
		if (strlen(lst[i]) > 0) {

			ptr = lst[i];

			while (ptr) {
				memset(&p, 0, sizeof(p));
				ptr = nxt(ptr, &p);
				add_to_passport(&pass, &p);
			}

		} else {
			// Start new passport parse
			nr_valid += is_valid(&pass);
			reset_passport(&pass);
		}
	}

	return nr_valid;
}

int main()
{
	uint16_t nr_valid;

	// TEST A
	nr_valid = check_passports(test_input, ARRAY_SIZE(test_input),
	                           naive_is_valid);
	assert(nr_valid == 2);

	// TEST B all valid
	nr_valid = check_passports(test_input3, ARRAY_SIZE(test_input3),
	                           better_is_valid);
	assert(nr_valid == 4);

	// TEST B all invalid
	nr_valid = check_passports(test_input2, ARRAY_SIZE(test_input2),
	                           better_is_valid);
	assert(nr_valid == 0);


	// REAL input
	nr_valid = check_passports(real_input, ARRAY_SIZE(real_input),
	                           naive_is_valid);
	printf("A: %u\n", nr_valid);

	nr_valid = check_passports(real_input, ARRAY_SIZE(real_input),
	                           better_is_valid);
	printf("B: %u\n", nr_valid);

}
