Project 2: Text Adventure Game - Introduction and Explanation

Link to video demonstration: https://www.youtube.com/watch?v=tWeI_X0KGkU&t=1s

## In this project, I implement the Text Adventure Game for 1 player - the avatar - who will play the role of finding the necessery objects in rooms and using them to win the game.

## My notes for the overall operation of the game:
    In this game the player control an avatar to go around the rooms and search for objects, using 5 basic commands (look, go, take, drop, inventory).
    Each time the player enter the room, he will get information about room's description, items in it, and the direction to his previous room.
    The player will continue to play until he find the key to go to the last room and find the correct weapon to kill the Boss.
    So every time the player do the 'go' command, I will check if the location at the direction is existed and then print out the next's room description, as well as the current items in that room.
    Note that player can only take items in his current room, yet can choose to drop it at any room he wants, since my implementation allow new items to be added
    Also, my implementation requires the player to find and use the key to enter the last room, and allows just one of the weapons in those rooms to be able to kill the Boss. It will not result in a losing state, the player can play for as long as he wants until he finds the correct weapon that can kill the Boss. 

## Here is the explanation of my code and the requirements it satisfies:
-   First, I created 8 rooms in my game, and allow each rooms to contain items. (adventure.c) 
-   All of the rooms and items are created using C structs (struct Item, struct Room) and are dynamically allocated using malloc() (rooms.h, rooms.c, items.h, and items.c)
-   I also deallocated memory in my code using the free() function for items and rooms that are dynamically allocated. (adventure.c)
-   I implenmented an avatar and its inventory using pointers (code requirements). (in main() - adventure.c)
-   My game allows an avatar to perform action with the 5 basic commands (all in main() function of adventure.c):
    +   "look" (see the current room) 
    +   "go direction" (north south east west up down)
    +   "take Item", item is the name of an item in the room 
    +   "drop Item", item is the name of an item in the avatars inventory
    +   "inventory", to check the current items in the inventory
-   I also have 2 instances that change the state of the room:
    +   The first one is to use the key to move from room7 to the last room
    +   The second one is to use the "dagger", one of the weapon to kill the boss, and lead to the winning state
-   The winning state is when the person use the correct weapon to kill the boss

##Below are some functions for my implementations:
struct Item *item_take(struct Item *head, char *name): function to take the item with the given name from the room and remove it in the room (items.c)
struct Item *item_drop(struct Item *head, char *name): function to drop the item from inventory to the room (rooms.c)
void room_exit_north(struct Room* current, struct Room* other): function to link this current room's north to the other and link backward (from other's south to current), same for the other directions (rooms.c)
int check_inventory(struct Item *item, char *name): function to check if the given item is in the inventory by comparing its name (adventure.c)
void print_rooms(struct Room *active): function to print out the current room's description and the current items that are placed in the rooms. Note that my implementation allows up to 2 items in each room. (adventure.c)
