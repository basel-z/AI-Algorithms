#include "Lecture.h"
#include "Strategy.h"

class FWChecking : public Strategy
{
private:
	Graph FWCheckingAlgorithm(Graph graph);
public:
	FWChecking(Graph& g);
	Graph solve();
	~FWChecking();
};
