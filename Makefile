CC=gcc
FLAGS=-c -Wall
LIBS=-lm

test_minsom: minsom.o test_minsom.o
	$(CC) minsom.o test_minsom.o -lm -o test_minsom

minsom.o: minsom.c minsom.h
	$(CC) $(FLAGS) $(LIBS) minsom.c

test_minsom.o: test_minsom.c
	$(CC) $(FLAGS) $(LIBS) test_minsom.c

clean:
	rm *.o test_minsom
