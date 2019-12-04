

def match(nr: int) -> bool:
    if nr < 10e4:
       #print("No match: Too small")
       return False

    has_double = False

    last_digit = None
    for digit in str(nr):
        if last_digit is not None:
            if not has_double and digit == last_digit:
               has_double = True

            if int(digit) < int(last_digit):
               #print("No match: Decreasing order")
               return False

        last_digit = digit

    return has_double


assert match(111111)
assert not match(223450)
assert not match(123789)

amnt: int = 0
for nr in range(137683, 596253):
    if match(nr):
        amnt += 1

print(amnt)
