all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp ../UrlParser/Parser/Parser.cpp -o $(mainFile)


.PHONY: run
run:
	./$(mainFile)
