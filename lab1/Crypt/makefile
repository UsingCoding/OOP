all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) crypt Tests/Inputs/input1.txt Tests/Outputs/output1.txt 5

	# ./$(mainFile) decrypt Tests/Outputs/output1.txt Tests/Inputs/input1.txt 5

.PHONY: test-only
test-only:
	dart ./Tests/main.dart
