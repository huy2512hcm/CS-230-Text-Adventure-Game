SRC =  rooms.c items.c adventure.c
OBJ =  rooms.o items.o adventure.o
PROG = adventure_game

$(PROG): $(OBJ)
	gcc $(OBJ) -o $(PROG)
$(OBJ): $(SRC)