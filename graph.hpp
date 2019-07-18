#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <graphviz/gvc.h>
using namespace std;

struct graph_writer {
    void operator()(std::ostream& out) const {
      out << "graph [bgcolor=white]" << std::endl;
      out << "node [shape=rectangle color=black]" << std::endl;
      out << "edge [style=solid]" << std::endl;
    }
};



typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::directedS, 
							boost::property<boost::vertex_name_t, string>> MyGraph;


void createFlowGraph(vector<string> &lines);
vector<string> createListOfBB(vector<string> &lines, map<string, int>&);
vector<pair<int, int>> findAllEdges(const vector<string>&);


