all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Convert/Convert.cpp Convert/ConvertException.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) 36 10 36


.PHONY: test-only
test-only:
	dart ./Tests/test.dart
