CC = gcc
CFLAGS = -Wall -O2 -Igenerated
PYTHON = python

all: generate build_test run_test

generate:
	$(PYTHON) generator/dbc_to_autosar.py input/powertrain.dbc generated/

build_test:
	$(CC) $(CFLAGS) test/main_test.c generated/Can_Com_Generated.c -o test_runner.exe

run_test:
	./test_runner.exe

clean:
	rm -rf generated/*.h generated/*.c test_runner.exe

.PHONY: all generate build_test run_test clean
