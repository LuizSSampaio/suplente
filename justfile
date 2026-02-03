default: run

build:
    mkdir build -p
    gcc main.c board.c -o ./build/sumplete -Wall

run: build
    ./build/sumplete
