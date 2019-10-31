all:  Schedule.cpp
	g++ -std=c++11 Schedule.cpp -o schedule
	./schedule simple1.txt
