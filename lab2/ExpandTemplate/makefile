all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp ExpandTemplate.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
