#include "MapColoring.h"


MapColoring::MapColoring(Graph & _initialGraph, vector<int> _colors, SolvingType _solvingType):initialGraph(_initialGraph)
{
	colors = _colors;
	solvingType = _solvingType;
	initialGraph.setDefaultDomain(_colors);
	initialGraph.setDomainForAll(_colors);
}

Graph MapColoring::colorGraph()
{
	if (solvingType == SolvingType::BACKTRACKING) {
		BackTracking back = BackTracking(initialGraph);
		return back.solve();
	}
	else if (solvingType == SolvingType::FORWARDCHECKING) {
		FWChecking fw = FWChecking(initialGraph);
		return fw.solve();
	}
	else if (solvingType == SolvingType::ARCCONSISTENCY) {
		ArcConsistency ac = ArcConsistency(initialGraph);
		return ac.solve();
	}
	else if (solvingType == SolvingType::BACKJUMPING) {
		BackJumping _backJumping = BackJumping(initialGraph);
		return _backJumping.solve();
	}
	else if (solvingType == SolvingType::FEASIBILITY) {
		Feasibility _feasibility = Feasibility(initialGraph);
		return _feasibility.solve();
	}
	else if (solvingType == SolvingType::KEMPECHAIN) {
		KempeChains kempe = KempeChains(initialGraph);
		return kempe.solve();
	}

	else if (solvingType == SolvingType::HYBRIDCHECK) {
		HybridSearch _hybridSearch = HybridSearch(initialGraph);
		return _hybridSearch.solve();
	}
}

MapColoring::~MapColoring()
{
}
