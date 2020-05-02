all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp ../HtmlDecode/Decode.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
