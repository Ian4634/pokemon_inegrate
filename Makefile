image: main.o variables.o events.o login.o player_source.o inventory.o game.o
	gcc main.o ./lib/my_lib/events.o ./lib/my_lib/variables.o ./lib/my_lib/login.o ./lib/my_lib/player_source.o ./lib/my_lib/inventory.o ./lib/my_lib/game.o -L ./lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o image.exe
main.o: main.c
	gcc -I ./include main.c -c
variables.o: ./lib/my_lib/variables.c
	gcc -I ./include ./lib/my_lib/variables.c -c -o ./lib/my_lib/variables.o
events.o: ./lib/my_lib/events.c
	gcc -I ./include ./lib/my_lib/events.c -c -o ./lib/my_lib/events.o
login.o: ./lib/my_lib/login.c
	gcc -I ./include ./lib/my_lib/login.c -c -o ./lib/my_lib/login.o
player_source.o: ./lib/my_lib/player_source.c
	gcc -I ./include ./lib/my_lib/player_source.c -c -o ./lib/my_lib/player_source.o
inventory.o: ./lib/my_lib/inventory.c
	gcc -I ./include ./lib/my_lib/inventory.c -c -o ./lib/my_lib/inventory.o
game.o: ./lib/my_lib/game.c
	gcc -I ./include ./lib/my_lib/game.c -c -o ./lib/my_lib/game.o