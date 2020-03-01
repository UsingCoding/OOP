all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Command/impl.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) Tests/Inputs/input1.txt output.txt

.PHONY: test-only
test-only:
	# dart ./Tests/test.dart
