#!/bin/bash -x

/lib/x86_64-linux-gnu/libc.so.6
make clean all
readelf -a libwrite_rev.so.1.0 > 1-before-strip
strip --strip-unneeded libwrite_rev.so.1.0
readelf -a libwrite_rev.so.1.0 > 2-after-strip
diff -Naur *strip > 3-strip.diff
