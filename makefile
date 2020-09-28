all:
	g++ -o npm npm.cpp -O3 -std=c++14
clean:
	rm -f npm	
