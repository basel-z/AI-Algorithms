#include "Lecture.h"
#include "BackTracking.h"
#include "MapColoring.h"
SolvingType printStuffAndGetSolving(int& x) {
	cout << "Please choose a number for which coloring algorithm you would like to use" << endl;
	int input;
	cout << "please choose 1 for FORWARDCHECKING" << endl;
	cout << "please choose 2 for ARCCONSISTENCY" << endl;
	cout << "please choose 3 for BACKTRACKING" << endl;
	cout << "please choose 4 for BACKJUMPING" << endl;
	cout << "please choose 5 for FEASIBILITY" << endl;
	cout << "please choose 6 for KEMPECHAIN" << endl;
	cout << "please choose 7 for HYBRIDCHECK" << endl;
	cin >> input;
	while (input > 7 || input < 1) {
		cout << "please choose again a valid number" << endl;
		cin >> input;
	}
	x = input;
	if (input == 1)
		return SolvingType::FORWARDCHECKING;
	else if (input == 2)
		return SolvingType::ARCCONSISTENCY;
	else if (input == 3)
		return SolvingType::BACKTRACKING;
	else if (input == 4)
		return SolvingType::BACKJUMPING;
	else if (input == 5)
		return SolvingType::FEASIBILITY;
	else if (input == 6)
		return SolvingType::KEMPECHAIN;
	else
		return SolvingType::HYBRIDCHECK;
}
int main(int argc, char* argv[])
{
	int input;
	SolvingType solving = printStuffAndGetSolving(input);
	GraphGenerator generator("..\\src\\DSJC125.1.col");
	Graph g(generator.buildGraph());	
	int maxDegree = g.getMaxDegree();
	int nodesSize = g.getNodesSize();
	int maxGraphColorSize = maxDegree < nodesSize ? maxDegree : nodesSize;
	int minK = maxGraphColorSize;
	vector<int> colors;
	Graph bestGraph(Graph::emptyGraph());
	for (int i = 1; i <= maxGraphColorSize; i++)
	{
		colors.push_back(i);
	}
	if (input >= 1 && input <= 4) {
		int r = 1, l = maxGraphColorSize;
		while (r < l)
		{
			int mid = l + (r - l) / 2;
			vector<int> _colors;
			for (int i = 1; i <= mid; i++)
			{
				_colors.push_back(i);
			}
			MapColoring mapColoring = MapColoring(g, colors, solving);
			g = mapColoring.colorGraph();
			if (g.isEmptyGraph()) {
				r = mid + 1;
			}
			else {
				bestGraph = g;
				l = mid - 1;
				g.resetColors();
			}
		}
		bestGraph.print();
		return 0;
	}
	else {
		MapColoring mapColoring = MapColoring(g, colors, solving);
		g = mapColoring.colorGraph();
		g.print();
	}
	return 0;
}
