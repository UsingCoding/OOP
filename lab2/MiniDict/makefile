all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Dictionary/Dictionary.cpp CommandLineController/CommandLineController.cpp ../../Utils/StringUtils.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
