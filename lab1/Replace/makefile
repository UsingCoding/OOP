all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) Tests/Inputs/input1.txt Tests/output.txt replace ""

.PHONY: test-only
test-only:
	dart ./Tests/main.dart
