#!/bin/sh
# $1: vdbe.c path

echo '/* Automatically generated file.  Do not edit */' >opcodes.h
grep '^case OP_' $1 | \
  sed -e 's/://' -e 's/{//' -e 's/case //' | \
  awk '{printf "#define %-30s %3d\n", $$2, ++cnt}' >>opcodes.h