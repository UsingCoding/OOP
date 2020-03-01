all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Replacer/Replacer.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) Tests/Inputs/input2.txt Tests/Outputs/output2.txt search research

.PHONY: test-only
test-only:
	# dart ./Tests/test.dart
