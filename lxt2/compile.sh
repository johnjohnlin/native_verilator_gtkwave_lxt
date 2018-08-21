#!/bin/sh
rm -rf ../lxt2_write.o
g++ -c -I. lxt2_write.cpp && mv lxt2_write.o ..
