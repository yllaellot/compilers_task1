#include "sim.h"

#define CELL 6
#define X_SIZE (SIM_X_SIZE / CELL)
#define Y_SIZE (SIM_Y_SIZE / CELL)
#define ALIVE 0xFF00FF00
#define DEAD 0xFF000000

static void randField(int *field) {
  for (int i = 0; i < Y_SIZE * X_SIZE; i++)
    field[i] = (simRand() % 4 == 0);
}

static void drawCell(int x, int y, int argb) {
  for (int dy = 0; dy < CELL; dy++)
    for (int dx = 0; dx < CELL; dx++)
      simPutPixel(x * CELL + dx, y * CELL + dy, argb);
}

static void drawField(int *field) {
  for (int y = 0; y < Y_SIZE; y++)
    for (int x = 0; x < X_SIZE; x++)
      drawCell(x, y, field[y * X_SIZE + x] ? ALIVE : DEAD);
}

static int countNeighbours(int *field, int x, int y) {
  int l = (x == 0) ? X_SIZE - 1 : x - 1;
  int r = (x == X_SIZE - 1) ? 0 : x + 1;
  int u = (y == 0) ? Y_SIZE - 1 : y - 1;
  int d = (y == Y_SIZE - 1) ? 0 : y + 1;
  return field[u * X_SIZE + l] + field[u * X_SIZE + x] + field[u * X_SIZE + r] +
         field[y * X_SIZE + l] + field[y * X_SIZE + r] +
         field[d * X_SIZE + l] + field[d * X_SIZE + x] + field[d * X_SIZE + r];
}

static void calcField(int *prev, int *next) {
  for (int y = 0; y < Y_SIZE; y++)
    for (int x = 0; x < X_SIZE; x++) {
      int n = countNeighbours(prev, x, y);
      int alive = prev[y * X_SIZE + x];
      next[y * X_SIZE + x] = (n == 3) || (alive && n == 2);
    }
}

static void setCell(int *field, int x, int y) {
  x = (x + X_SIZE) % X_SIZE;
  y = (y + Y_SIZE) % Y_SIZE;
  field[y * X_SIZE + x] = 1;
}

static void spawnFigure(int *field, int xy) {
  int x = (xy >> 16) / CELL;
  int y = (xy & 0xFFFF) / CELL;
  setCell(field, x, y - 1);
  setCell(field, x + 1, y - 1);
  setCell(field, x - 1, y);
  setCell(field, x, y);
  setCell(field, x, y + 1);
}

void app(void) {
  int field1[Y_SIZE * X_SIZE];
  int field2[Y_SIZE * X_SIZE];
  int *prev = field1;
  int *next = field2;
  randField(prev);
  while (1) {
    drawField(prev);
    simFlush();
    calcField(prev, next);
    int *tmp = prev;
    prev = next;
    next = tmp;
    while (simHasClick())
      spawnFigure(prev, simGetClick());
  }
}
