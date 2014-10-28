all: ./hw7

./hw7: mainLink.o primes.o trialdiv.o mrabin.o rndsrc.o 
	g++ mainLink.o primes.o trialdiv.o mrabin.o rndsrc.o -L/home/scf-22/csci551b/openssl/lib -lcrypto -o ./hw7

mainLink.o: mainLink.cpp
	g++ -Wall -c mainLink.cpp

primes.o: primes.cpp
	g++ -Wall -c primes.cpp

trialdiv.o: trialdiv.cpp
	g++ -Wall -c trialdiv.cpp

mrabin.o: mrabin.cpp
	g++ -Wall -c mrabin.cpp

rndsrc.o: rndsrc.cpp 
	g++ -Wall -c -I/home/scf-22/csci551b/openssl/include rndsrc.cpp

clean:
	rm -rf *o ./hw7
