CXX = g++
CXXFLAGS = -std=c++11 -O2 -Wall -Wextra -Wno-unused-function -Wno-unused-variable -Iinclude

SRCS = src/globals.cpp src/utils.cpp src/TGraph.cpp src/TIndividual.cpp src/DistrictBFS.cpp src/geneticOps.cpp src/GeneticPopulation.cpp src/NSGAII.cpp src/geneticGenerations.cpp src/main.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = PACGAMP

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
