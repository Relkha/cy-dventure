all: game

util.o: util.c ../2-includes/util.h
	gcc  -c util.c

backup.o: backup.c ../2-includes/backup.h
	gcc  -c backup.c

step.o: step.c ../2-includes/step.h
	gcc  -c step.c

inventory.o: inventory.c ../2-includes/inventory.h
	gcc  -c inventory.c

game : main.c util.o step.o backup.o inventory.o
	gcc  main.c util.o step.o backup.o inventory.o -o game
	
clean :
	rm game *.o
