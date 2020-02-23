 #pragma once
#include <string>
#include <fstream>
#include "Graph.h"

// convert input to graph
class GraphGenerator
{
private:
	std::ifstream _file;

public:
	GraphGenerator(const std::string path);
	Graph buildGraph();
	~GraphGenerator();
};
