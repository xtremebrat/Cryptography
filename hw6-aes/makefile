all: ./hw6

./hw6: mainLink.o tabChk.o mprod.o keyexp.o encrypt.o decrypt.o inverse.o
	g++ mainLink.o tabChk.o mprod.o keyexp.o encrypt.o decrypt.o inverse.o -o ./hw6

mainLink.o: mainLink.cpp
	g++ -Wall -c mainLink.cpp

tabChk.o: tabChk.cpp
	g++ -Wall -c tabChk.cpp
	
mprod.o: mprod.cpp
	g++ -Wall -c mprod.cpp

keyexp.o: keyexp.cpp
	g++ -Wall -c keyexp.cpp

encrypt.o: encrypt.cpp
	g++ -Wall -c encrypt.cpp

decrypt.o: decrypt.cpp
	g++ -Wall -c decrypt.cpp

inverse.o: inverse.cpp
	g++ -Wall -c inverse.cpp

clean:
	rm -rf *o ./hw6
