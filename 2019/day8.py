from typing import List
from math import inf


def calc_least_zero_layer(width: int, height: int, source: List[int]):
    layer_nr = 0
    least_zeroes = inf
    least_layer = -1

    source_ptr = 0
    
    while source_ptr < len(source):
            
        zeroes = 0
        for _ in range(width * height):
            i = source[source_ptr]
            if i == 0:
                zeroes += 1
            
            source_ptr += 1
        
        if zeroes < least_zeroes:
           least_zeroes = zeroes
           least_layer = layer_nr
        
        layer_nr += 1

    return least_layer


assert calc_least_zero_layer(2, 2, [0, 0, 0, 0, 1, 1, 1, 1, 0, 2, 2, 2]) == 1


#
# Input
#

HEIGHT = 6
WIDTH = 25
with open("day8_input.txt", "r") as f:
    source = [int(i) for i in f.readline()[:-1]]


#
# Part 1
#

layer_nr: int = calc_least_zero_layer(WIDTH, HEIGHT, source)

nr_layers = len(source) // (WIDTH * HEIGHT)
layer = source[layer_nr * (WIDTH * HEIGHT): (layer_nr + 1) * (WIDTH * HEIGHT)]

nr_ones = len(list(filter(lambda x: x == 1, layer)))
nr_twos = len(list(filter(lambda x: x == 2, layer)))
print(nr_ones * nr_twos)


#
# Part 2
#

def decode_image(width: int, height: int, source: List[int]):
    layer = []
    for x in range(width * height):
        for i in range(nr_layers):
           c = source[i * (width * height) + x]
           if c != 2:
              layer.append(c)
              break

    return layer


def draw(width: int, height: int, layer: List[int]):
    for h in range(height):
        line = ""
        for x in layer[h * width: (h+1) * width]:
            if x == 1: line += "#"
            elif x == 0: line += " "
            else: line += "E"
            
        print(line)


assert decode_image(2, 2, [0,2,2,2,1,1,2,2,2,2,1,2,0,0,0,0]) == [0, 1, 1, 0]

draw(WIDTH, HEIGHT, decode_image(WIDTH, HEIGHT, source))
