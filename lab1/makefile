all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Converter/Converter.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile) 16 10 14
