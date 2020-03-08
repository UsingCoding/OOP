all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Matrix/Matrix.cpp Command/ReadMatrixCommand/ReadMatrixCommand.cpp Command/WriteMatrixCommand/WriteMatrixCommand.cpp Command/CommandException.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) Tests/Inputs/input1.txt

.PHONY: test-only
test-only:
	dart ./Tests/test.dart
