CCFLAGS = -Wall -std=c++11

assignment7: assignment7.o
	g++ $(CCFLAGS) -o assignment7 assignment7.o

assignment7.o: assignment7.cc
	g++ $(CCFALGS) -c assignment7.cc

clean:
	-rm *.o assignment7
