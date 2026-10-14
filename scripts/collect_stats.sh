#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT"

mkdir -p build trace stats

clang++ pass/TracePass.cpp -fPIC -shared \
    -I"$(llvm-config --includedir)" \
    -o build/libTracePass.so

clang -O2 -fpass-plugin=./build/libTracePass.so \
    src/app.c trace/driver.c pass/log.c \
    -Isrc \
    -o build/life_trace

TRACE_FILE="trace/trace.log" TRACE_FRAMES="${TRACE_FRAMES:-2}" \
    ./build/life_trace

python3 scripts/analyze.py trace/trace.log \
    --top 25 --max-window 5 \
    -o stats/patterns.txt

echo "stats/patterns.txt written"
