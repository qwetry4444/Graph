#include "Graph.h"

class GraphPerformanceTester {
public:
    GraphPerformanceTester(int maxNodes, int step, int edgesPerNode);
    void RunTests();
private:
    void CreateGraph(Graph& graph, int numNodes, int numEdges);
    double MeasureDeleteNodeTime(Graph& graph, int nodeId);

    int maxNodes;
    int step;
    int edgesPerNode;
};