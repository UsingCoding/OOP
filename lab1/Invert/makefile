all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Matrix3x3/Matrix3x3.cpp ReadException/ReadException.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) Tests/Inputs/input1.txt

.PHONY: test-only
test-only:
	dart ./Tests/test.dart
