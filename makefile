move: build
	cd ~/Desktop/Mini-C-Language-Preprocessor/checker/multi/; make -f Makefile.checker > result.out
	
build: 
	gcc main.c -o2 -o ./checker/multi/so-cpp
	
local: build
	gcc main.c -o2 -o so-cpp
run: local
	./so-cpp < ceva.txt > out.out


