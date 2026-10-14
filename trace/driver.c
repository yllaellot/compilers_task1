#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

static int FrameLimit = 2;
static int Frames = 0;
static unsigned Seed = 0x12345u;
static jmp_buf Done;

static unsigned next_rand(void) {
  Seed = Seed * 1664525u + 1013904223u;
  return Seed & 0x7fffffff;
}

void simInit(void) {
  const char *fl = getenv("TRACE_FRAMES");
  if (fl) FrameLimit = atoi(fl);
  if (FrameLimit < 1) FrameLimit = 1;
}
void simExit(void) {}
void simPutPixel(int x, int y, int argb) { (void)x; (void)y; (void)argb; }
void simFlush(void) {
  if (++Frames >= FrameLimit) longjmp(Done, 1);
}
int simRand(void) { return (int)next_rand(); }
int simHasClick(void) { return 0; }
int simGetClick(void) { return 0; }

int main(void) {
  simInit();
  if (setjmp(Done) == 0) app();
  simExit();
  fprintf(stderr, "[driver] stopped after %d frame(s)\n", Frames);
  return 0;
}
