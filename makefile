all: Sequence.o pbPlots.o supportLib.o main run

Sequence.o: Sequence.cpp
	g++ -W -c Sequence.cpp -o Sequence.o

pbPlots.o: pbPlots.cpp
	g++ -W -c pbPlots.cpp -o pbPlots.o

supportLib.o: supportLib.cpp
	g++ -W -c supportLib.cpp -o supportLib.o

main: main.o
	g++ main.o Sequence.o pbPlots.o supportLib.o -o a.out -lm

main.o: main.cpp
	g++ -W -c main.cpp -o main.o

clean:
	rm *.o

run: a.out
	./a.out