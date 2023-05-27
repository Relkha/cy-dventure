all: game

util.o: ppp/2-includes/util.c ppp/2-includes/util.h
	gcc  -c util.c

backup.o: ppp/2-includes/backup.c ppp/2-includes/backup.h
	gcc  -c backup.c

step.o: ppp/2-includes/step.c ppp/2-includes/step.h
	gcc  -c step.c

inventory.o: ppp/2-includes/inventory.c ppp/2-includes/inventory.h
	gcc  -c inventory.c

game : main.c util.o step.o backup.o inventory.o
	gcc  main.c util.o step.o backup.o -o game
	
clean :
	rm game *.o
