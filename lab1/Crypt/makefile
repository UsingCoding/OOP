all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp -o $(mainFile)

.PHONY: run
run:
	# ./$(mainFile) crypt Tests/Input/input1.txt Tests/Output/output1.txt 5
	# ./$(mainFile) crypt input.txt output.txt 5
	./$(mainFile) decrypt output.txt input.txt 5

.PHONY: test-only
test-only:
	dart ./Tests/main.dart
