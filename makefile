CXX=g++
CXXFLAGS= -std=c++17 -O3 -Wall -Iinclude -Wpedantic -Wextra
LDFLAGS= -lsfml-graphics -lsfml-window -lsfml-system
SRC = src/main.cpp src/NCAEngine.cpp src/Genome.cpp src/TinyML.cpp src/GeneticOps.cpp
OBJ=$(SRC:.cpp=.o)

TARGET= build/NCAEngine

all:dir $(TARGET)

dir:
	mkdir -p build

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJ) -o $(TARGET)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(TARGET) build
