all: hw1

hw1: mainp.o hex.o enc.o dec.o
	g++ mainp.o hex.o enc.o dec.o -o hw1

mainp.o: mainp.cpp
	g++ -c mainp.cpp

hex.o: hex.cpp
	g++ -c hex.cpp

enc.o: enc.cpp
	g++ -c enc.cpp

dec.o: dec.cpp
	g++ -c dec.cpp

clean:
	rm -rf *o hw1
