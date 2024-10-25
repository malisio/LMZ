
GG=g++

all: compile

compile: main.cpp
	$(GG) main.cpp -o main
clear:
	rm main
