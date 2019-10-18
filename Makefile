all:  Schedule.cpp
	g++ Schedule.cpp -o schedule
	./schedule simple1.txt
