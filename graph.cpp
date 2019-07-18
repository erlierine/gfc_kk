#include "graph.hpp"

using namespace std;


void createFlowGraph(vector<string> &lines) {
	map<string, int> lbl_ixs;
	vector<string> nodes = createListOfBB(lines, lbl_ixs);
	map<string, MyGraph::vertex_descriptor> indexes;
	MyGraph G = MyGraph(nodes.size());	
	for (size_t i = 0; i < nodes.size(); i++) {
		boost::put(boost::vertex_name_t(), G, i, nodes[i].c_str());
		indexes[nodes[i]] = boost::vertex(i, G);
	}
	vector<pair<int, int>> edges = findAllEdges(nodes);	
	for(auto it = edges.begin(); it != edges.end(); it++)
		boost::add_edge(it->first, it->second, G);	
	ofstream dotfile("cfg.dot");
	boost::write_graphviz(dotfile, G,
			boost::make_label_writer(boost::get(boost::vertex_name_t(), G))); 

	dotfile.close();

	GVC_t *gvc;
    Agraph_t *g;
    FILE *fp;
    gvc = gvContext();
    fp = fopen("cfg.dot", "r");
    g = agread(fp, 0);
    gvLayout(gvc, g, "dot");
    gvRender(gvc, g, "png", fopen("diagram.png", "w"));
    gvFreeLayout(gvc, g);
    agclose(g);
    gvFreeContext(gvc);
//	remove("cfg.dot");
}
vector<string> createListOfBB(vector<string> &lines, map<string, int> &lbl_ixs) {
	vector<bool> ins_leader(lines.size(), false);
	ins_leader[0] = true;
	regex gotoStat(".+ goto .*");
	regex lbl_start(".+:");
	for (unsigned i = 0; i < lines.size(); i++) 
		if (regex_match(lines[i], lbl_start)) 
				lbl_ixs[lines[i]] = i;
		
	

	for(unsigned i = 0; i < lines.size(); i++) 
		if (regex_match(lines[i], gotoStat)) {
			size_t pos_lbl = lines[i].find_last_of(' ');
			string lbl = lines[i].substr(pos_lbl+1) + ":";

			ins_leader[lbl_ixs[lbl]] = true;
			if (i + 1 < lines.size())
				ins_leader[i+1] = true;

		}	
	
	vector<string> bbs;
	for (unsigned i = 0; i < lines.size(); i++) {
		if (ins_leader[i]) {
			string basic_block = "";
			do {
				basic_block += lines[i++] + "\n";
			} while(i < lines.size() and !ins_leader[i]);
			i--;
			bbs.push_back(basic_block);
		}
	}	

	return bbs;	
}

vector<pair<int, int>> findAllEdges(const vector<string>& nodes) {
	vector<pair<int, int>> edges;
	map<string, int> lbl_ixs;
	regex gotoStat("(.|\n)* goto.+\n");
	regex lbl_start(".+:\n(.|\n)*");
	for (unsigned i = 0; i < nodes.size() - 1; i++) { 
		edges.push_back(make_pair(i, i+1));
		if (regex_match(nodes[i], lbl_start)) 
				lbl_ixs[nodes[i].substr(0, nodes[i].find_first_of(":"))] = i;
		
	}

	//FIXME
	if (regex_match(nodes[nodes.size()-1], lbl_start)) { 
		string tmp = nodes[nodes.size()-1].substr(0, nodes[nodes.size()-1].find_first_of(":"));
		lbl_ixs[tmp] = nodes.size()-1;
	}

	for (unsigned i = 0; i < nodes.size(); i++) {
		if (regex_match(nodes[i], gotoStat)) {
			string tmp = nodes[i].substr(nodes[i].find_last_of(' ')+1, nodes[i].find_last_of('\n')-1);
			tmp.replace(tmp.length()-1, 1, "\0");
			edges.push_back(make_pair(i, lbl_ixs[tmp]));
		}
	
	}

	return edges;
}
