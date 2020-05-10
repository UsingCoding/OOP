all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Lexer/Lexer.cpp ../../Utils/StringUtils.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
