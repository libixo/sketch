#!/bin/sh -ex

time ${CC:-tcc} -g -Wall -Wpedantic src/main.c -o sketch
