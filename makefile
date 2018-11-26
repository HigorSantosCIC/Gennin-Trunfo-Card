all: funct.o list.o ninja.o log.o prog.exe clean
prog.exe: main.c funct.o list.o ninja.o log.o
	gcc -o prog main.c funct.o list.o ninja.o log.o -g -lm
funct.o: funct.c
	gcc -c funct.c -g
list.o: list.c
	gcc -c list.c -g
ninja.o: ninja.c
	gcc -c ninja.c -g
log.o:
	gcc -c log.c -g
clean:
	-rm *.o
