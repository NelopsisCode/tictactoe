all: bin/tictactoe

bin/tictactoe: obj/main.o obj/morpion.o
	g++ -g obj/main.o obj/morpion.o -o bin/tictactoe

obj/main.o: src/main.cpp 
	g++ -g -Wall -c src/main.cpp -o obj/main.o

obj/morpion.o: src/morpion.h src/morpion.cpp 
	g++ -g -Wall -c src/morpion.cpp -o obj/morpion.o


clean:
	rm obj/*.o

veryclean: clean
	rm bin/*


