all: game

util.o: util.c util.h
	gcc  -c util.c

backup.o: backup.c backup.h
	gcc  -c backup.c

step.o: step.c step.h
	gcc  -c step.c

inventory.o: inventory.c inventory.h
	gcc  -c inventory.c

game : main.c util.o step.o backup.o inventory.o
	gcc  main.c util.o step.o backup.o -o game
	
clean :
	rm game *.o
