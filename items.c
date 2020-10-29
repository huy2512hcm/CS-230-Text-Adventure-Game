#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "items.h"

//struct function to dynamically allocate items
struct Item *item(char *name, char *description, struct Item *next)
{
    struct Item *newItem = (struct Item *)malloc(sizeof(struct Item));
    newItem->name = name;
    newItem->description = description;
    newItem->next = next;
    return newItem;
}

//return item's name
char *item_name(struct Item *item)
{
    return item->name;
}

//return item's description
char *item_description(struct Item *item)
{
    return item->description;
}

//return item's next
struct Item *item_next(struct Item *item)
{
    return item->next;
}

//
struct Item *item_take(struct Item *head, char *name)
{
    if (head == NULL)
    {
        return NULL;
    }

    struct Item *node = head;

    while (node != NULL)
    {
        if (node->next == NULL)
        {
            return NULL;
        }
        if (strcmp(node->next->name, name) == 0)
        {
            struct Item *temp = node->next;
            node->next = node->next->next;
            return temp;
        }
        node = node->next;
    }
}

struct Item *item_drop(struct Item *head, char *name)
{
    if (head == NULL)
    {
        return NULL;
    }

    struct Item *node = head;
    struct Item *newItem = item(name, NULL, NULL);
    if (strcmp(name, "gun") == 0)
    {
        newItem->name = name;
        newItem->description = "large rainbow gun";
    }
    if (strcmp(name, "rope") == 0)
    {
        newItem->name = name;
        newItem->description = "leather-bound rope";
    }
    if (strcmp(name, "spear") == 0)
    {
        newItem->name = name;
        newItem->description = "dragon glass spear";
    }
    if (strcmp(name, "shield") == 0)
    {
        newItem->name = "shield";
        newItem->description = "Lannister's shield";
    }
    if (strcmp(name, "bow") == 0)
    {
        newItem->name = "bow";
        newItem->description = "old dust bow";
    }
    if (strcmp(name, "arrow") == 0)
    {
        newItem->name = "arrow";
        newItem->description = "golden arrow";
    }
    if (strcmp(name, "cannon") == 0)
    {
        newItem->name = "cannon";
        newItem->description = "fire cannon";
    }
    if (strcmp(name, "coin") == 0)
    {
        newItem->name = "coin";
        newItem->description = "gold coin";
    }
    if (strcmp(name, "comb") == 0)
    {
        newItem->name = "comb";
        newItem->description = "comb";
    }
    if (strcmp(name, "dagger") == 0)
    {
        newItem->name = "dagger";
        newItem->description = "valyrian dagger";
    }
    if (strcmp(name, "sword") == 0)
    {
        newItem->name = "sword";
        newItem->description = "king's slayer sword";
    }
    if (strcmp(name, "knife") == 0)
    {
        newItem->name = "knife";
        newItem->description = "bloody jungle knife";
    }
    if (strcmp(name, "axe") == 0)
    {
        newItem->name = "axe";
        newItem->description = "wildings' axe";
    }
    if (strcmp(name, "key") == 0)
    {
        newItem->name = "key";
        newItem->description = "key in the bush";
    }

    while (node != NULL)
    {
        if (node->next == NULL)
        {
            node->next = newItem;
            break;
        }
        node = node->next;
    }
    return newItem;
}
