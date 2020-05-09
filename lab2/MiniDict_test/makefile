all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp ../MiniDict/Dictionary/Dictionary.cpp ../../Utils/StringUtils.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
