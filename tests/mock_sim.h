#ifndef MOCK_SIM_H
#define MOCK_SIM_H
#define MOCK_MAX_FRAMES 8

void mockRun(int (*script)(int), int limit);

void mockClick(int frame, int x, int y);

int mockPixel(int frame, int x, int y);
#endif
