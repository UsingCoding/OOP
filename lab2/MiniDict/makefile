all: build run

mainFile = main

.PHONY: build
build:
	g++ $(mainFile).cpp Dictionary/Dictionary.cpp Dictionary/Exception/DictionaryException.cpp Dictionary/DictionarySerializable.cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)
