kate.o: kate.h kate.c
	gcc -c kate.c

max.o: max.h max.c
	gcc -c max.c

main.o: main.c
	gcc -c main.c

sayHi: kate.o max.o main.o
	gcc kate.o max.o main.o	 -o sayHi
