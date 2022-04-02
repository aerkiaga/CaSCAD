#!/bin/sh

src/cascad "$1.scad" 2>&1 >/dev/null | grep -F -f"$1" -
