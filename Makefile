CC = gcc
CFLAGS = -Wall -Werror -ansi -pedantic
MAIN = guess
OBJS = main.o tnode.o a2funcs.o game.o
all: $(MAIN)

$(MAIN): $(OBJS) tnode.h a2defs.h game.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

main.o: main.c a2defs.h
	$(CC) -g -c main.c 

tnode.o: tnode.c tnode.h a2defs.h 
	$(CC) -g -c tnode.c

game.o: game.c game.h
	$(CC) -g -c game.c

a2funcs.o: a2funcs.c a2defs.h
	$(CC) -g -c a2funcs.c

clean:
	rm * .o $(MAIN) core