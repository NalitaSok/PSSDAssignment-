all:  Schedule.cpp
	g++ -std=c++11 Schedule.cpp -o schedule
	./schedule medium1.ucs
