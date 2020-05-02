all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp ../Vector/VectorHandling.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
