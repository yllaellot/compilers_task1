#include <stdio.h>
#include <stdlib.h>

static FILE *TraceFile = NULL;
static long long Events = 0;
static long long Limit = 0;

__attribute__((constructor))
static void traceInit(void) {
  const char *path = getenv("TRACE_FILE");
  if (!path) path = "trace/trace.log";

  const char *lim = getenv("TRACE_LIMIT");
  Limit = lim ? atoll(lim) : 2000000LL;

  TraceFile = fopen(path, "w");
  if (!TraceFile)
    fprintf(stderr, "[LOG] cannot open %s\n", path);
}

__attribute__((destructor))
static void traceFini(void) {
  if (TraceFile) {
    fflush(TraceFile);
    fclose(TraceFile);
    TraceFile = NULL;
  }
  fprintf(stderr, "[LOG] %lld events written\n", Events);
}

void traceEdgeLogger(char *userName, char *operandName) {
  if (!TraceFile) return;
  if (Limit > 0 && Events >= Limit) return;
  fprintf(TraceFile, "%s<-%s\n", userName, operandName);
  ++Events;
}
