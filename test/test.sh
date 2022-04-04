#!/bin/sh

src/cascad --print-bytecode "$1.scad" 2>&1 >/dev/null | grep -F -f"$1" - | cmp "$1"
