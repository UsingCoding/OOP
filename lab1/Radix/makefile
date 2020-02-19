all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Converter/Converter.cpp Converter/ConverterException.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) 16 2 1F

.PHONY: test-only
test-only:
	dart ./Tests/test.dart
