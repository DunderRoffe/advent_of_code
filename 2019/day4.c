#include <stdint.h>
#include <stdio.h>

#define FALSE 0u
#define STREAK_MIN2 1u
#define STREAK_EXACT2 2u

#define TEN 10
#define MIN_SIZE 100000u

#define INPUT_MIN 137683u
#define INPUT_MAX 596253u

int match(uint32_t nr)
{
    if (nr < MIN_SIZE) {
       return FALSE;
    }

    int streak = 1;
    int last_digit = -1;

    uint8_t return_value = 0;
    int digit;
    
    do {
        digit = nr % TEN;
        nr /= TEN;
       
        if (last_digit > -1) {
              if (digit == last_digit) {
                 streak += 1;
              } else {
                 if (streak >= 2) {
                    return_value |= STREAK_MIN2;
                 }
                 if (streak == 2) {
                    return_value |= STREAK_EXACT2;
                 }
                 streak = 1;
              }
              if (digit > last_digit) {
                 return FALSE;
              }
        } 
        last_digit = digit;
    } while(nr > 0);


    if (streak >= 2) {
       return_value |= STREAK_MIN2;
    }
    if (streak == 2) {
       return_value |= STREAK_EXACT2;
    }

    return return_value;
}

int main()
{
    uint16_t amnt_part1 = 0;
    uint16_t amnt_part2 = 0;
    uint8_t ret;

    for (uint32_t nr = INPUT_MIN; nr <= INPUT_MAX; nr++) {
        ret = match(nr);

        if (ret & STREAK_MIN2) {
            amnt_part1 += 1;
        }
        if (ret & STREAK_EXACT2) {
            amnt_part2 += 1;
        }
    }

    printf("Part 1: %u\n", amnt_part1);
    printf("Part 2: %u\n", amnt_part2);
}
