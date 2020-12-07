all: proj5.exe

project5.o: project5.cpp IntersectionSimulationClass.h SortedListClass.h EventClass.h FIFOQueueClass.h CarClass.h LinkedNodeClass.h constants.h random.h
	g++ -std=c++98 -g -Wall -c project5.cpp -o  project5.o

CarClass.o: CarClass.cpp CarClass.h constants.h
	g++ -std=c++98 -g -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: EventClass.cpp EventClass.h constants.h
	g++ -std=c++98 -g -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: IntersectionSimulationClass.cpp IntersectionSimulationClass.h SortedListClass.h EventClass.h FIFOQueueClass.h LinkedNodeClass.h CarClass.h constants.h
	g++ -std=c++98 -g -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

random.o: random.cpp random.h
	g++ -std=c++98 -g -Wall -c random.cpp -o random.o

proj5.exe: project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o 
	g++ -std=c++98 project5.o CarClass.o EventClass.o IntersectionSimulationClass.o random.o -o proj5.exe

clean:
	rm -f *.o *.exe
