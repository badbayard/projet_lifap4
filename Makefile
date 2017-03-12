CC= g++
FLAGS = -g -Wall -c
OBJ =obj/Combat.o obj/Joueur.o obj/Pays.o obj/Region.o obj/Terrain.o obj/main.o obj/Jeu.o
SRC =src/Combat.h src/Joueur.h src/Pays.h src/Region.h src/Terrain.h src/main.cpp src/Jeu.h
	

all : bin/test.out

bin/test.out : $(OBJ)
	$(CC) $(OBJ) -o  bin/test.out

obj/Combat.o : $(SRC)
	$(CC) $(FLAGS)   src/Combat.cpp -o obj/Combat.o

obj/Joueur.o : $(SRC)
	$(CC) $(FLAGS)  src/Joueur.cpp -o obj/Joueur.o

obj/Pays.o : $(SRC)
	$(CC) $(FLAGS)  src/Pays.cpp -o obj/Pays.o

obj/Region.o : $(SRC)
	$(CC) $(FLAGS)  src/Region.cpp -o obj/Region.o

obj/Terrain.o : $(SRC)
	$(CC) $(FLAGS)  src/Terrain.cpp -o obj/Terrain.o

obj/Jeu.o : $(SRC)
	$(CC) $(FLAGS) src/Jeu.cpp -o obj/Jeu.o

obj/main.o : $(SRC)
	$(CC) $(FLAGS) src/main.cpp -o obj/main.o


clean:
	rm obj/*.o
