#include <errno.h>

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define NORTH 0u
#define EAST 1u
#define SOUTH 2u
#define WEST 3u
#define NR_OF_DIRECTIONS 4u

#define LEFT 3u
#define STRAIGHT 0u
#define RIGHT 1u

struct Vector2 {
    uint32_t x;
    uint32_t y;
};

struct Cart {
    struct Vector2 pos;
    uint8_t next_move;
    uint8_t heading;
};

struct Cart *alloc_cart(struct Vector2 pos, uint8_t heading)
{
    struct Cart *new_cart;
    new_cart = malloc(sizeof(struct Cart));

    new_cart->pos = pos;
    new_cart->next_move = LEFT;
    new_cart->heading = heading;

    return new_cart;
}

struct Node {
    char symbol;
    struct Vector2 pos;
    struct Node* directions[NR_OF_DIRECTIONS];
};

struct Node *alloc_node(struct Vector2 pos)
{
    struct Node *new_node;
    int i;

    new_node = malloc(sizeof(struct Node));
    new_node->pos = pos;

    for (i = 0; i < NR_OF_DIRECTIONS; i++) {
        new_node->directions[i] = NULL;
    }

    return new_node;
}

struct World {
    struct Vector2 size;    

    char **cells;
    struct Node ***nodes;
    struct Cart **carts;
    uint32_t carts_len;
};

struct Vector2 move(const struct Vector2 *vec,
                    const uint8_t heading)
{
    struct Vector2 res_vec;

    res_vec.x = vec->x;
    res_vec.y = vec->y;

    if (heading == NORTH)
         res_vec.y -= 1;

    else if (heading == EAST)
         res_vec.x += 1;

    else if (heading == SOUTH)
         res_vec.y += 1;

    else if (heading == WEST)
         res_vec.x -= 1;

    return res_vec;
}

uint8_t is_intersection(const struct Node *node)
{
    return node->directions[0] &&
           node->directions[1] && 
           node->directions[2] && 
           node->directions[3];
}

uint8_t move_cart(struct Cart *cart, struct World *world)
{
    struct Node *current_node;
    struct Vector2 next_pos;
    uint8_t new_heading;
    uint32_t i;

    current_node = world->nodes[cart->pos.y][cart->pos.x];
    if (is_intersection(current_node)){
        cart->heading = (cart->heading + cart->next_move) % NR_OF_DIRECTIONS;
    }
    else if (!current_node->directions[cart->heading])
    {
        // Our current heading is not available, need to figure out where to go...
        new_heading = (cart->heading + 1) % NR_OF_DIRECTIONS;
        if (current_node->directions[new_heading]) {
            cart->heading = new_heading;
        } else {
            // This is the only other option since we dont wanna go backwards
            cart->heading = (cart->heading - 1) % NR_OF_DIRECTIONS;
        }
    }
    // If none of the above matched we are free to continue in the same heading

    next_pos = move(&cart->pos, cart->heading);

    for (i = 0; i < world->carts_len; i++) {
        if (world->carts[i]->pos.x == next_pos.x &&
            world->carts[i]->pos.y == next_pos.y) {
            return 0; // another cart is already at our next position -> crash
        }
    }

    cart->pos = next_pos;

    return 1;
}

int inside_bounds(const struct Vector2 *pos, const struct World *world)
{
    return pos->x >= 0 && pos->x < world->size.x
           && pos->y >=0 && pos->y < world->size.y;
}

char interpret_symbol(const struct Vector2 *pos,
                      struct World *world)
{
    uint8_t connected[NR_OF_DIRECTIONS] = {0};
    char temp_symbol;
    struct Vector2 temp_vec;
    int heading;

    for (heading = 0; heading < NR_OF_DIRECTIONS; heading++) {
        temp_vec = move(pos, heading);

        if (!inside_bounds(&temp_vec, world)) {
            connected[heading] = 0;
            continue;
        }

        temp_symbol = world->cells[temp_vec.y][temp_vec.x];

        if (heading == NORTH || heading == SOUTH)
           connected[heading] = temp_symbol == '|';
        else
           connected[heading] = temp_symbol == '-';

        connected[heading] = connected[heading]
                           || temp_symbol == '+'
                           || temp_symbol == '\\'
                           || temp_symbol == '/';
    }

    if (connected[NORTH] && connected[EAST] &&
        connected[SOUTH] && connected[WEST])
        return '+';
    else if ((connected[NORTH] && connected[EAST]) ||
        (connected[SOUTH] && connected[WEST]))
        return '\\';
    else if ((connected[NORTH] && connected[WEST]) ||
             (connected[SOUTH] && connected[EAST]))
        return '/';
    else if (connected[NORTH] && connected[SOUTH])
        return '|';
    else if (connected[EAST] && connected[WEST])
        return '-';

}

struct Node *parse_cell(const struct Vector2 pos,
                        struct World *world)
{
    struct Node *new_node;
    new_node = world->nodes[pos.y][pos.x];
    if (new_node) {
        //printf("\nPos (%u, %u) already visited\n", pos.x, pos.y);
        return new_node;
    }

    //printf("\nVisiting pos (%u, %u) for first time\n", pos.x, pos.y);
    char cell_symbol;
    char east_cell;
    char south_cell;
    char north_cell;
    struct Cart *new_cart = NULL;
    struct Vector2 temp_pos;
    int headings_to_link[NR_OF_DIRECTIONS] = {-1, -1, -1, -1};

    new_node = alloc_node(pos);
    world->nodes[pos.y][pos.x] = new_node;

    cell_symbol = world->cells[pos.y][pos.x];
    if (cell_symbol == ' ') {
        printf("Encountered weird state...\n");
        exit(1);
    }
    //printf("Parsing cell %c\n", cell_symbol);

    switch(cell_symbol) {
    case '^': new_cart = alloc_cart(pos, NORTH);
              break;
    case '>': new_cart = alloc_cart(pos, EAST);
              break;
    case 'v': new_cart = alloc_cart(pos, SOUTH);
              break;
    case '<': new_cart = alloc_cart(pos, WEST);
              break;
    default: break;
    }

    if (new_cart) {
        world->carts[world->carts_len++] = new_cart;
        cell_symbol = interpret_symbol(&pos, world);
        //printf("Interpreted underlying cell as %c\n", cell_symbol);
    }

    new_node->symbol = cell_symbol;
    switch(cell_symbol) {
    case '/': temp_pos = move(&pos, EAST); 
              if (inside_bounds(&temp_pos, world))
                  east_cell = world->cells[temp_pos.y][temp_pos.x];
              else
                  east_cell = ' ';
              temp_pos = move(&pos, SOUTH);
              if (inside_bounds(&temp_pos, world))
                  south_cell = world->cells[temp_pos.y][temp_pos.x];
              else
                  south_cell = ' ';
              if (east_cell != ' ' && east_cell != '|' &&
                  south_cell != '-' && south_cell != ' ')
              {
                  headings_to_link[0] = EAST;
                  headings_to_link[1] = SOUTH;
              } else {
                  headings_to_link[0] = NORTH;
                  headings_to_link[1] = WEST;
              }
              break;

    case '\\':temp_pos = move(&pos, NORTH);
              if (inside_bounds(&temp_pos, world))
                  north_cell = world->cells[temp_pos.y][temp_pos.x];
              else
                  north_cell = ' ';
              temp_pos = move(&pos, EAST); 
              if (inside_bounds(&temp_pos, world))
                  east_cell = world->cells[temp_pos.y][temp_pos.x];
              else
                  east_cell = ' ';
              if (east_cell != ' ' && east_cell != '|' &&
                  north_cell != '-' && north_cell != ' ')
              {
                  headings_to_link[0] = NORTH;
                  headings_to_link[1] = EAST;
              } else {
                  headings_to_link[0] = SOUTH;
                  headings_to_link[1] = WEST;
              }
              break;

    case '|': headings_to_link[0] = NORTH;
              headings_to_link[1] = SOUTH;
              break;

    case '-': headings_to_link[0] = EAST;
              headings_to_link[1] = WEST;
              break;

    case '+': headings_to_link[0] = NORTH;
              headings_to_link[1] = EAST;
              headings_to_link[2] = SOUTH;
              headings_to_link[3] = WEST;
              break;

    default: break;
    }

    //printf("Start link for pos (%u, %u)\n", pos.x, pos.y);
    for (int i = 0; i < NR_OF_DIRECTIONS; i++) {
       if (headings_to_link[i] == -1) {
           break;
       }

       //printf("Linking to %u\n", headings_to_link[i]);
       temp_pos = move(&pos, headings_to_link[i]);
       new_node->directions[headings_to_link[i]] =
           parse_cell(temp_pos, world);
    }
    //printf("Done linking!\n");

    return new_node;
}

void free_cells(struct World *world)
{
   uint32_t y;

   for (y = 0; y < world->size.y; y++) {
       free(world->cells[y]);
   }
}

struct Vector2 run_simulation(struct World *world)
{
    uint32_t cart_index;
    struct Cart *cart;

    while (1) {
        for (cart_index = 0; cart_index < world->carts_len; cart_index++) {
            cart = world->carts[cart_index];

            if (!move_cart(cart, world)) {
                return cart->pos;
            }
        }
    }
}

void read_world_file(struct World *world, const char *filename)
{
    FILE *fd = NULL;
    char *line = NULL;
    size_t len;
    int read;
    int i;

    printf("Read size of input...\n");
    fd = fopen(filename, "r");
    do {
        read = getline(&line, &len, fd);
        if (read > 0) {
            if (world->size.x == 0)
                world->size.x = len;

            world->size.y += 1;
        } else {
            printf("%s\n", strerror(errno));
        }
    }
    while (read > 1);

    fclose(fd);

    printf("Alloc world y's...\n");
    world->cells = malloc(sizeof(char*) * world->size.y);
    world->nodes = malloc(sizeof(struct Node*) * world->size.y);
    world->carts = malloc(sizeof(struct Cart*) * world->size.y);
    world->carts_len = 0;

    printf("Alloc world x's...\n");
    fd = fopen(filename, "r");
    for (i = 0; i < world->size.y; i++) {
        read = getline(&line, &len, fd);
        if (read) {
            world->cells[i] = malloc(sizeof(char) * world->size.x);
            strncpy(world->cells[i], line, len);

            world->nodes[i] = calloc(world->size.x, sizeof(struct Node*));
            
        } else {
            printf("%s\n", strerror(errno));
        }
    }

    fclose(fd);
    free(line);
}

int main() {
    uint32_t i = 0;
    struct World world;

    struct Vector2 crash_pos;

    world.size.x = 0;
    world.size.y = 0;

    printf("World size: (%u, %u)\n", world.size.x, world.size.y);


    read_world_file(&world, "test_input");

    printf("Parsing cells...\n");
    for (i = 0 ; i < world.size.x; i++) {
         if (world.cells[0][i] != ' ') {
             struct Vector2 pos = {.x = i, .y = 0};
             printf("Start parse pos: (%u, %u)\n", pos.x, pos.y);
             parse_cell(pos, &world);
             break;
         }
    }

    free_cells(&world);

    printf("Pos of first cart: (%u, %u)\n", world.carts[0]->pos.x, world.carts[0]->pos.y);

    crash_pos = run_simulation(&world);
    printf("Pos of crash: (%u, %u)\n", crash_pos.x, crash_pos.y);

    return 0;
}
