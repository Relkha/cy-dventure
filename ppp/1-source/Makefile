all: game

util.o: ../2-includes/util.c ../2-includes/util.h
	gcc  -c util.c

backup.o: ../2-includes/backup.c ../2-includes/backup.h
	gcc  -c backup.c

step.o: ../2-includes/step.c ../2-includes/step.h
	gcc  -c step.c

inventory.o: ../2-includes/inventory.c ../2-includes/inventory.h
	gcc  -c inventory.c

game : main.c util.o step.o backup.o inventory.o
	gcc  main.c util.o step.o backup.o -o game
	
clean :
	rm game *.o
