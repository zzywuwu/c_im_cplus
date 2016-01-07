
all:
	rm -rf test.o test a.out
#	g++ -g -std=c++11 -fno-elide-constructors test.c -o test
	g++ -g -std=c++11 test.c -o test
	./test

clean:
	rm -rf test.o test a.out
