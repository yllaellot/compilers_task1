# Game of Life
This is an example of a graphical application with a simple interface based on the SDL 2.0.

## Usage:
Simple run:
```
sudo apt install libsdl2-dev
cmake -S . -B build
cmake --build build
./build/life
```
Run tests:
```
ctest --test-dir build --output-on-failure
```
Generate optimized LLVM IR (`-O2`) of the app module:
```
cmake --build build --target ir
```
or manually:
```
cd src && clang -O2 -S -emit-llvm app.c -o ../ir/app.ll
```
If SDL2 is not installed, CMake downloads and builds it automatically (internet and git are required). Tests do not need SDL.

## Controls:
Mouse click spawns an R-pentomino under the cursor.

## Graphical Interface:
```
#define SIM_X_SIZE 1536
#define SIM_Y_SIZE 768

void simFlush();
void simPutPixel(int x, int y, int argb);
int simRand();
int simHasClick();
int simGetClick();
```

## Files:
```
src/app.c        - logic of the game (only void app())
src/sim.c/.h     - SDL 2.0 interface
src/start.c      - main
ir/app.ll        - optimized LLVM IR of app.c
tests/           - tests with a mock of sim.h
```
