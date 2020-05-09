all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Car/Car.cpp CommandLineController/CommandLineController.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
