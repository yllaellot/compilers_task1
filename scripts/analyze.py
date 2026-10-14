#!/usr/bin/env python3
import argparse
import sys
from collections import Counter


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("trace")
    ap.add_argument("--top", type=int, default=25)
    ap.add_argument("--max-window", type=int, default=5)
    ap.add_argument("-o", "--output")
    args = ap.parse_args()

    out = open(args.output, "w") if args.output else sys.stdout

    with open(args.trace) as f:
        events = [l.strip() for l in f if l.strip()]
    total = len(events)
    print(f"# trace: {args.trace}", file=out)
    print(f"# events: {total}", file=out)
    print(f"# unique edges: {len(set(events))}\n", file=out)

    for n in range(1, args.max_window + 1):
        c = Counter(tuple(events[i:i + n]) for i in range(total - n + 1))
        print(f"## window = {n} (unique: {len(c)})", file=out)
        for pat, cnt in c.most_common(args.top):
            share = cnt / max(total - n + 1, 1) * 100
            print(f"  {cnt:>10}  {share:5.2f}%  " + "  ".join(pat), file=out)
        print(file=out)

    if args.output:
        out.close()


if __name__ == "__main__":
    main()
