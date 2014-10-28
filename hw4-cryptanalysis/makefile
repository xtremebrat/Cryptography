all: hw4

hw4: linkProg.o keygen.o invkey.o solve.o encode2.o histo.o
	g++ linkProg.o keygen.o invkey.o solve.o encode2.o histo.o -o hw4

linkProg.o: linkProg.cpp
	g++ -c -Wall linkProg.cpp

keygen.o: keygen.cpp
	g++ -c -Wall keygen.cpp

invkey.o: invkey.cpp
	g++ -c -Wall invkey.cpp

solve.o: solve.cpp
	g++ -c -Wall solve.cpp

encode2.o: encode2.cpp
	g++ -c -Wall encode2.cpp

histo.o: histo.cpp
	g++ -c -Wall histo.cpp
clean:
	rm -rf *o hw4
