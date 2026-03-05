CXX=g++
CXXFLAGS= -std=c++17 -O3 -Wall -Iinclude -Wpedantic -Wextra -ffast-math -march=native
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SRC = src/main.cpp src/NCAEngine.cpp src/GenomeOps.cpp src/TinyML.cpp src/PopulationManager.cpp
OBJ=$(SRC:src/%.cpp=obj/%.o)

TARGET= build/NCAEngine

all:dir $(TARGET)

dir:
	mkdir -p build obj

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET) $(LDFLAGS)

obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(TARGET) build obj
