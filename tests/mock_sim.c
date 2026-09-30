#include "sim.h"
#include "mock_sim.h"
#include <setjmp.h>
#include <string.h>

static int fb[SIM_Y_SIZE][SIM_X_SIZE];
static int frames[MOCK_MAX_FRAMES][SIM_Y_SIZE][SIM_X_SIZE];
static int frameCount = 0, frameLimit = 0, randCalls = 0;
static int (*randScript)(int);
static jmp_buf done;
static int clickFrame = -1, clickXY = 0, clickPending = 0;

void mockRun(int (*script)(int), int limit) {
  frameCount = 0; frameLimit = limit; randCalls = 0; randScript = script;
  memset(fb, 0, sizeof fb);
  if (setjmp(done) == 0) app();
  clickPending = 0;
}
int mockPixel(int frame, int x, int y) { return frames[frame][y][x]; }
void simPutPixel(int x, int y, int argb) { fb[y][x] = argb; }
void simFlush(void) {
  memcpy(frames[frameCount++], fb, sizeof fb);
  if (frameCount == frameLimit) longjmp(done, 1);
}
int simRand(void) { return randScript(randCalls++); }
void simInit(void) {}
void simExit(void) {}
void mockClick(int frame, int x, int y) {
  clickFrame = frame; clickXY = (x << 16) + (y & 0xFFFF); clickPending = 1;
}
int simHasClick(void) { return clickPending && frameCount == clickFrame; }
int simGetClick(void) { clickPending = 0; return clickXY; }
