# ASMGameOfLife
Conway's Game of Life implemented in NAMS x64

## Structure

Repository consists of:
* `game.asm` - file with defintion of two global functions (`start` and `run`) and two helper functions (`run_once` and `check_neighbours`)
* `main.c` - file consists of a program which tests `start` and `run`
 functions
* `Makefile`
* `tests` - directory with few tests in txt format

## Dependencies
* gcc
* nasm

## Usage
```bash
make
./game tests/glider_gun.txt
```
Run parameter should contain path to appropriate test file with initial description of board for the Game of Life.
Testing program loads file, initializes the game by calling `start` function 
and afterwards calls `run(1)` in the loop and prints the content of the board to stdout.