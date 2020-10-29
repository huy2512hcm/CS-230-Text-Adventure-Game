#include "rooms.h"

struct Room *room(char *description, struct Item *items, struct Room *current, struct Room *north, struct Room *south,
                  struct Room *east, struct Room *west,
                  struct Room *up, struct Room *down)
{
        struct Room *newRoom = (struct Room *)malloc(sizeof(struct Room));
        newRoom->description = description;
        newRoom->items = items;
        newRoom->current = current;
        newRoom->north = north;
        newRoom->south = south;
        newRoom->east = east;
        newRoom->west = west;
        newRoom->up = up;
        newRoom->down = down;
}

void room_exit_north(struct Room *current, struct Room *other)
{
        current->north = other;
        other->south = current;
}

void room_exit_south(struct Room *current, struct Room *other)
{
        current->south = other;
        other->north = current;
}
void room_exit_east(struct Room *current, struct Room *other)
{
        current->east = other;
        other->west = current;
}
void room_exit_west(struct Room *current, struct Room *other)
{
        current->west = other;
        other->east = current;
}
void room_exit_up(struct Room *current, struct Room *other)
{
        current->up = other;
        other->down = current;
}
void room_exit_down(struct Room *current, struct Room *other)
{
        current->down = other;
        other->up = current;
}
