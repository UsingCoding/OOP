all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Parser/Parser.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
