#!/bin/sh
rm -rf ../lxt2_write.o
gcc -c -I. lxt2_write.c && mv lxt2_write.o ..
