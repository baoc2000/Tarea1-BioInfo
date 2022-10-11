all: Sequence.o main clean run

Sequence.o: Sequence.cpp
	g++ -W -c Sequence.cpp -o Sequence.o

main: main.o
	g++ main.o Sequence.o -o a.out

main.o: main.cpp
	g++ -W -c main.cpp -o main.o

clean:
	rm *.o

run: a.out
	./a.out