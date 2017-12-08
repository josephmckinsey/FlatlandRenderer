CC = g++ -Wall -g -std=c++11
flags = -I/usr/include -fPIC -c
OBJ = main.o Flatland.o FlatShape.o Polygon.o WavefrontShape.o
LINK = -L/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -lGL

a.out : $(OBJ)
	$(CC) -o a.out $(OBJ) $(LINK)

main.o : main.cpp Flatland.h Polygon.h
	$(CC) $(flags) -o main.o main.cpp

Flatland.o : Flatland.cpp Flatland.h Polygon.h
	$(CC) $(flags) -o Flatland.o Flatland.cpp

FlatShape.o : FlatShape.cpp FlatShape.h
	$(CC) $(flags) -o FlatShape.o FlatShape.cpp

Polygon.o : Polygon.cpp Polygon.h FlatShape.h
	$(CC) $(flags) -o Polygon.o Polygon.cpp

WavefrontShape.o : WavefrontShape.cpp WavefrontShape.h FlatShape.h
	$(CC) $(flags) -o WavefrontShape.o WavefrontShape.cpp

.PHONY : clean
clean :
	-rm *.o a.out
