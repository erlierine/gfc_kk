#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <graphviz/gvc.h>
using namespace std;

struct VertexData {
	string code;
	int num;
};


typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexData, 
							boost::property<boost::edge_weight_t, double>> MyGraph;


void createFlowGraph(vector<string> &lines);
vector<string> createListOfBB(vector<string> &lines, map<string, int>&);
vector<pair<int, int>> findAllEdges(const vector<string>&);


