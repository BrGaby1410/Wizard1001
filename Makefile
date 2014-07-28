build:
	g++ main.cpp vector.cpp -g -lGL -lGLU -lglut -o wizzard202 -Wall
run:
	./wizzard202
clear:
	rm wizzard202
