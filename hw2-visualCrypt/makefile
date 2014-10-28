all: hw2

hw2: mainp.o keydump.o merge.o
	g++ -lcrypto mainp.o keydump.o merge.o -o hw2

mainp.o: mainp.cpp
	g++ -g -Wall mainp.cpp -I/home/scf-22/csci551b/openssl/include -L/home/scf-22/csci551b/openssl/lib -lcrypto -o mainp.o

keydump.o: keydump.cpp
	g++ -c keydump.cpp

merge.o: merge.cpp
	g++ -c merge.cpp

clean:
	rm -rf *o hw2
