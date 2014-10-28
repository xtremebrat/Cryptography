all: ./hw5

./hw5: mainLink.o tabChk.o desenc.o desdec.o
	g++ mainLink.o tabChk.o desenc.o desdec.o -o ./hw5

mainLink.o: mainLink.cpp
	g++ -c mainLink.cpp

tabChk.o: tabChk.cpp
	g++ -c tabChk.cpp

desenc.o: desenc.cpp
	g++ -c desenc.cpp

desdec.o: desdec.cpp
	g++ -c desdec.cpp

clean:
	rm -rf *o ./hw5
