CXX = g++
CXXFLAGS = --std=c++11 -pthread

sources = preambule.cpp Q1.cpp Q2.cpp
headers = $(patsubst %.cpp,%.hpp,$(sources))
objects = $(patsubst %.cpp,%.o,$(sources))

preambule.o: preambule.cpp preambule.hpp
Q1.o:	Q1.cpp preambule.o ThreadPool.h
Q2.o:	Q2.cpp preambule.o ThreadPool.h

simulation: Modal.cpp Q1.o Q2.o preambule.o ThreadPool.h
	$(CXX) $(CXXFLAGS) -o $@ Modal.cpp Q1.o Q2.o preambule.o ThreadPool.h

clean-objects:
	rm -vf *.o

clean-programs:
	rm -vf simulation

clean: clean-objects clean-programs
	rm -vf *~
