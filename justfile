default: run

build:
    mkdir build -p
    gcc src/main.c src/board.c src/game.c src/rank.c -o ./build/sumplete -Wall

run: build
    ./build/sumplete
