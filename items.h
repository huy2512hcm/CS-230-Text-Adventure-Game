#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef ITEM_HEAD
#define ITEM_HEAD

struct Item
{
    char *name;
    char *description;
    struct Item *next;
};
struct Item *item (char *name, char *description, struct Item* next);
char* item_name(struct Item* item);
char* item_description(struct Item* item);
struct Item* item_next(struct Item* item);
struct Item* item_take(struct Item* head, char* name);
struct Item* item_drop(struct Item* head, char* name);

#endif