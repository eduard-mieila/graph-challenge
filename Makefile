#! /bin/bash

build: b-poduri b-adrese b-lego

b-poduri:
	g++ -g -Wall -Wextra -std=c++17 poduri.cpp -o poduri

b-adrese:
	g++ -g -Wall -Wextra -std=c++17 adrese.cpp -o adrese

b-lego:
	g++ -g -Wall -Wextra -std=c++17 lego.cpp -o lego

run-p1:
	./poduri
	
run-p2:
	./adrese

run-p3:
	./lego

clean:
	rm -f poduri adrese lego
