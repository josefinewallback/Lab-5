CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O3

.PHONY: clean

slm: src/main.o src/kgram.o src/smallmodel.o
	$(CXX) $(CXXFLAGS) src/main.o src/kgram.o src/smallmodel.o -o slm

src/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/kgram.o: src/kgram.cpp
	$(CXX) $(CXXFLAGS) -c src/kgram.cpp -o src/kgram.o

src/smallmodel.o: src/smallmodel.cpp
	$(CXX) $(CXXFLAGS) -c src/smallmodel.cpp -o src/smallmodel.o

clean:
	rm -f src/main.o src/kgram.o src/smallmodel.o slm