all:
	g++ -o npm npm.cpp -O2 -std=c++14
clean:
	rm -f npm	
