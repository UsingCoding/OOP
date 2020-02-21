all: build run
test: build test-only

mainFile = main

.PHONY: build
build:
	# g++ $(mainFile).cpp Matrix/Matrix.cpp -o $(mainFile)
	g++ $(mainFile).cpp -o $(mainFile)

.PHONY: run
run:
	./$(mainFile)

.PHONY: test-only
test-only:
	# dart ./Tests/test.dart
	echo 'No test specified'
