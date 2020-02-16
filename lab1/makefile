all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Converter/Converter.cpp Converter/ConverterException.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) 16 10 2147483647
