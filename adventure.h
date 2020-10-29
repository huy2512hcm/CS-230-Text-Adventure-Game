#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rooms.h"
#include "items.h"

#ifndef CH_HEAD
#define CH_HEAD

int check_inventory(struct Item *item, char *name);
int main();
#endif