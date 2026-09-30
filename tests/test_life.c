#include "mock_sim.h"
#include "sim.h"
#include <stdio.h>

#define CELL 6
#define X_SIZE (SIM_X_SIZE / CELL)
#define Y_SIZE_T (SIM_Y_SIZE / CELL)
#define ALIVE 0xFF00FF00
#define DEAD 0xFF000000

static int failed = 0;
#define CHECK(cond, msg) do { if (!(cond)) { printf("FAIL: %s\n", msg); failed++; } } while (0)

static int cell(int f, int x, int y) {
  int c = mockPixel(f, x * CELL, y * CELL);
  for (int dy = 0; dy < CELL; dy++)
    for (int dx = 0; dx < CELL; dx++)
      if (mockPixel(f, x * CELL + dx, y * CELL + dy) != c) return -1;
  return c == ALIVE ? 1 : (c == DEAD ? 0 : -1);
}

static const int *pat; static int patN;
static int script(int i) {
  int x = i % X_SIZE, y = i / X_SIZE;
  for (int k = 0; k < patN; k++)
    if (pat[2 * k] == x && pat[2 * k + 1] == y) return 0;
  return 1;
}
static void run(const int *p, int n, int frames) { pat = p; patN = n; mockRun(script, frames); }

static void testBlinker(void) {
  static const int p[] = {10, 10, 11, 10, 12, 10};
  run(p, 3, 3);
  CHECK(cell(0, 11, 10) == 1 && cell(0, 10, 11) == 0, "blinker: frame 0 horizontal");
  CHECK(cell(1, 11, 9) == 1 && cell(1, 11, 11) == 1 && cell(1, 10, 10) == 0, "blinker: frame 1 vertical");
  int same = 1;
  for (int y = 8; y < 13; y++) for (int x = 8; x < 14; x++) same &= cell(0, x, y) == cell(2, x, y);
  CHECK(same, "blinker: period 2");
}

static void testBlock(void) {
  static const int p[] = {5, 5, 6, 5, 5, 6, 6, 6};
  run(p, 4, 4);
  int ok = 1;
  for (int f = 0; f < 4; f++)
    ok &= cell(f, 5, 5) == 1 && cell(f, 6, 5) == 1 && cell(f, 5, 6) == 1 && cell(f, 6, 6) == 1 && cell(f, 7, 7) == 0;
  CHECK(ok, "block: stays still");
}

static void testGlider(void) {
  static const int p[] = {1, 0, 2, 1, 0, 2, 1, 2, 2, 2};
  run(p, 5, 5);

  int ok = 1;
  for (int k = 0; k < 5; k++) ok &= cell(4, p[2 * k] + 1, p[2 * k + 1] + 1) == 1;
  CHECK(ok, "glider: shifted by (1,1) after 4 generations");
}

static void testTorus(void) {

  static const int p[] = {0, 10, 0, 11, 0, 12};
  run(p, 3, 2);
  CHECK(cell(1, 0, 11) == 1 && cell(1, X_SIZE - 1, 11) == 1 && cell(1, 1, 11) == 1, "torus: wraps over left edge");
}

static void testEmpty(void) {
  run(0, 0, 2);
  int ok = 1;
  for (int y = 0; y < 20; y++) for (int x = 0; x < 20; x++) ok &= cell(1, x, y) == 0;
  CHECK(ok, "empty field stays empty");
}

static void testClick(void) {
  pat = 0; patN = 0;
  mockClick(1, 7 * CELL + 2, 9 * CELL + 3);
  mockRun(script, 3);
  CHECK(cell(0, 7, 9) == 0 && cell(0, 8, 8) == 0, "click: dead before click");
  CHECK(cell(1, 7, 8) == 1 && cell(1, 8, 8) == 1 && cell(1, 6, 9) == 1 &&
        cell(1, 7, 9) == 1 && cell(1, 7, 10) == 1, "click: figure spawned");
  CHECK(cell(1, 9, 9) == 0 && cell(1, 6, 8) == 0, "click: nothing around the figure");
  CHECK(cell(2, 6, 8) == 1 && cell(2, 6, 10) == 1 && cell(2, 7, 9) == 0 && cell(2, 8, 9) == 0, "click: figure evolves");
}

static void testClickEdge(void) {
  pat = 0; patN = 0;
  mockClick(1, 0, 0);
  mockRun(script, 2);
  CHECK(cell(1, 0, 0) == 1 && cell(1, X_SIZE - 1, 0) == 1 && cell(1, 0, Y_SIZE_T - 1) == 1,
        "click: figure wraps over the edge");
}

int main(void) {
  testBlinker(); testBlock(); testGlider(); testTorus(); testEmpty(); testClick(); testClickEdge();
  if (failed) { printf("%d test(s) failed\n", failed); return 1; }
  printf("All tests passed\n");
  return 0;
}
