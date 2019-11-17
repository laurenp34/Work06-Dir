all: main.o
	gcc -o dirtest main.o

main.o: main.c
	gcc -c main.c

run:
	./dirtest

clean:
	rm *.o
	rm *~
