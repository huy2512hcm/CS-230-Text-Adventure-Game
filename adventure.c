#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "rooms.h"
#include "items.h"

//Check if a specific item is in the inventory
int check_inventory(struct Item *item, char *name)
{
    struct Item *node = item; //temporary Item node to traverse the list

    while (node != NULL)
    {
        if (node->next == NULL) //edge case
        {
            return 0;
        }
        //check if the name of item is found and return 1, otherwise return 0
        if (strcmp(node->next->name, name) == 0)
        {
            return 1;
        }
        node = node->next;
    }
    return 0;
}
//Print out the current room's description and the current items that are placed in the rooms
void print_rooms(struct Room *active)
{
    //check for the number of items in the room and print the existed items
    if (active->items == NULL || active->items->next == NULL || active->items->next->next == NULL)
    {
        
        if (active->items->next == NULL)
            printf("You are in %s", active->description);

        else if (active->items->next != NULL)
        {
            printf("You are in %s", active->description);
            printf(", with a %s", active->items->next->description);
            if (active->items->next->next != NULL)
                printf(", and a %s", active->items->next->next->description);
        }
    }
    else
        printf("You are in %s, and there are a %s and a %s on the floor", active->description, active->items->next->description, active->items->next->next->description);
}

int main()
{
    int win_game = 0; // variable to check for the win case, set to 1 if the player win

    //Items list, create 7 Item struct variables for 7 rooms. Note: the first item in each items will always be HEAD (inventory)
    struct Item *item1 = item("Inventory: ", "head of inventory", item("gun", "large rainbow gun", item("rope", "leather-bound rope", NULL)));
    struct Item *item2 = item("Inventory: ", "head of inventory", item("spear", "dragon glass spear", item("shield", "Lannister's shield", NULL)));
    struct Item *item3 = item("Inventory: ", "head of inventory", item("bow", "old dust bow", item("arrow", "golden arrow", NULL)));
    struct Item *item4 = item("Inventory: ", "head of inventory", item("cannon", "fire cannon", item("coin", "gold coin", NULL)));
    struct Item *item5 = item("Inventory: ", "head of inventory", item("comb", "comb", item("dagger", "valyrian dagger", NULL)));
    struct Item *item6 = item("Inventory: ", "head of inventory", item("sword", "king's slayer sword", item("knife", "bloody jungle knife", NULL)));
    struct Item *item7 = item("Inventory: ", "head of inventory", item("axe", "wildings' axe", item("key", "key in the bush", NULL)));

    //Item struct variable to represent inventory, used as the head of a linked list
    struct Item *inventory = item("Inventory: ", "head of inventory", NULL);

    //Rooms list, create 8 Room struct variable to store Items and room description
    struct Room *room1 = room("The North", item1, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *room2 = room("The Isles & River", item2, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *room3 = room("The Mountain & Vale", item3, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *room4 = room("The Rock", item4, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *room5 = room("The Reach", item5, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *room6 = room("The Stormland", item6, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    struct Room *room7 = room("The Dorne", item7, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
    //The last room contains no items
    struct Room *room8 = room("Winterfell - the final battle with Night King. To kill him and win game, attack him with your weapons in inventory.\nRemember, just one of the weapons can kill him.", inventory, NULL, NULL, NULL, NULL, NULL, NULL, NULL);

    //Set connections between rooms, in order to it I drew a map and imagine what the overall structure looks like
    room_exit_south(room1, room2);
    room_exit_up(room2, room3);
    room_exit_west(room2, room4);
    room_exit_south(room2, room5);
    room_exit_down(room4, room5);
    room_exit_east(room5, room6);
    room_exit_south(room5, room7);
    room_exit_down(room6, room7);
    room_exit_south(room7, room8);

    struct Room *active = room1; //Room struct variable to keep track of the current room
    room1->current = active; //set the current room to room1
    char input[10000];       //char variable to store user's input
    //Print out the initial state of the game
    printf("\nWelcome to the text-adventure game! In this game you will be a character in the world of Game of Thrones - the seven kingdoms. \nIn order to win, you have to go through each kingdom and find the key to the battle as well as \nchoosing the correct weapon to kill the Night King.\nTo play, type (case sensitive):\n'look' to look around\n'go + direction (north west south east up down)' to move\n'take + object' to take objects in the room\n'drop + object' to drop objects to the room\n'use + object' to use objects to the room\n'inventory' to see your inventory");
    printf("\n\nYou are in %s, and there are a %s and a %s on the floor", active->description, active->items->next->description, active->items->next->next->description);
    //Loop for game operation
    while (win_game != 1)
    {
        //take user's input and process
        printf("\n\nenter your command: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            return 0;
        }
        else
        {   //5 basic commands operations
            char *action = strtok(input, " \n"); //char pointer variable to get the first word using strtok() to apply delimiters
            char *object = strtok(NULL, "\n");   //char pointer variable to get the second word
            if (action != NULL)
            { //execute look command
                if (strcmp(action, "look") == 0)
                { //Room 8 has no items, so I make its own case
                    if (active == room8)
                    {
                        printf("You are in %s", active->description);
                    }
                    else
                    {
                        print_rooms(active);
                    }
                }
                //execute go command
                if (strcmp(action, "go") == 0)
                {
                    if (!object)
                        printf("go where?");
                    else
                    { 
                        //check if the location at the direction is valid, and perform the move if it is
                        if (strcmp(object, "east") == 0)
                        {
                            if (active->east == NULL) 
                                printf("There is no way there.");
                            else
                            {
                                active = active->east;
                                print_rooms(active);
                            }
                        }
                        else if (strcmp(object, "south") == 0)
                        {
                            //if room8 is the next location, require the key to unlock
                            if (active->south == room8)
                            {
                                printf("you have to use the key to unlock this room");
                            }
                            else if (active->south == NULL)
                                printf("There is no way there.");
                            else
                            {
                                active = active->south;
                                print_rooms(active);
                            }
                        }
                        else if (strcmp(object, "north") == 0)
                        {
                            if (active->north == NULL)
                                printf("There is no way there.");
                            else
                            {
                                active = active->north;
                                print_rooms(active);
                            }
                        }
                        else if (strcmp(object, "west") == 0)
                        {
                            if (active->west == NULL)
                                printf("There is no way there.");
                            else
                            {
                                active = active->west;
                                print_rooms(active);
                            }
                        }
                        else if (strcmp(object, "up") == 0)
                        {
                            if (active->up == NULL)
                                printf("There is no way there.");
                            else
                            {
                                active = active->up;
                                print_rooms(active);
                            }
                        }
                        else if (strcmp(object, "down") == 0)
                        {
                            if (active->down == NULL)
                                printf("There is no way there.");
                            else
                            {
                                active = active->down;
                                print_rooms(active);
                            }
                        }
                        else
                        {
                            printf("I don't know where you want to go."); //check if player input invalid direction
                        }
                    }
                }
                //execute take command
                if (strcmp(action, "take") == 0)
                {  
                    if (!object)
                        printf("take what?");
                    else
                    {   
                        //do the item_take function and then append the item to the inventory list
                        struct Item *item = item_take(active->items, object);
                        if (item != NULL)
                        {

                            printf("%s taken", item->name);
                            struct Item *temp = inventory; //temporary struct pointer variable to do the traversal
                            while (temp->next != NULL)
                            {
                                temp = temp->next;
                            }
                            temp->next = item;
                            item->next = NULL;
                        }
                        else
                        {
                            printf("can't find item"); //check if player input invalid object
                        }
                    }
                }
                //execute drop command
                if (strcmp(action, "drop") == 0)
                {
                    if (!object)
                        printf("drop what?");
                    else
                    {   
                        //check if the item exist in the inventory
                        if (check_inventory(inventory, object) == 1)
                        {
                            struct Item *item = item_drop(active->items, object); //drop the item to the room if found
                            printf("%s dropped", item->name);
                            struct Item *temp = inventory; //temporary struct pointer variable to do the traversal
                            while (temp->next != NULL)
                            {
                                if (strcmp(temp->next->name, object) == 0)
                                {
                                    if (temp->next->next == NULL)
                                    {
                                        temp->next = NULL;
                                        break;
                                    }
                                    else
                                    {
                                        temp->next = temp->next->next;
                                        break;
                                    }
                                }
                                temp = temp->next;
                            }
                        }
                        else
                        {
                            printf("the item is not in inventory"); //check if player input invalid object
                        }
                    }
                }
                //execute inventory command
                if (strcmp(action, "inventory") == 0)
                {
                    printf("%s", inventory->name); //always print the inventory node
                    struct Item *temp = inventory->next; //temporary struct pointer variable to do the traversal
                    int i = 0;
                    while (temp != NULL) //loop to traverse the inventory list and print out the items
                    {
                        if (i == 0)
                            printf("%s", temp->name);
                        else
                        {
                            printf(", %s", temp->name);
                        }
                        temp = temp->next;
                        i++;
                    }
                }
                //execute use command
                if (strcmp(action, "use") == 0)
                {
                    if (!object)
                    {
                        printf("use what?");
                    }
                    else
                    {
                        if (check_inventory(inventory, object) == 1) //check if the object to be used is in inventory
                        {
                            if (strcmp(object, "key") == 0 && active == room7) //if object is key, move to the last room
                            {
                                printf("unlocked the room, you are moved to Winterfell.");
                                active = active->south;
                            }
                            else if (active == room8) //if the current room is room8, ask the player to attack the Boss using weapons
                            {
                                if (strcmp(object, "dagger") == 0) //if dagger is used to attack, the player win - return the winning state
                                {
                                    printf("Night King is dead - you win!\n\n");
                                    win_game = 1;
                                }
                                else
                                {
                                    printf("this can't kill Night King."); //other weapons are not effective
                                }
                            }
                            else
                            {
                                printf("you can't use it here."); //if player try to use items in other rooms apart from room7 and room8
                            }
                        }
                        else
                        {
                            printf("the item is not in inventory"); //check if player input invalid object
                        }
                    }
                }
            }
        }
    }
    //free all items and rooms that I had dynamically allocated with malloc()
    free(item1);
    free(item2);
    free(item3);
    free(item4);
    free(item5);
    free(item6);
    free(item7);
    free(room1);
    free(room2);
    free(room3);
    free(room4);
    free(room5);
    free(room6);
    free(room7);
    free(room8);

    return 1;
}
