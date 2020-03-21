all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Converter/Converter.cpp Converter/ConverterException.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) 10 2 -2147483647


.PHONY: test-only
test-only:
	dart ./Tests/test.dart
