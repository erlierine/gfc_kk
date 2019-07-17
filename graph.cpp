#include "graph.hpp"

using namespace std;


void createFlowGraph(vector<string> &lines) {
	map<string, int> lbl_ixs;
	vector<string> nodes = createListOfBB(lines, lbl_ixs);
	MyGraph G = MyGraph(nodes.size());	
	for (unsigned i = 0; i < nodes.size(); i++) {
		G[i].code = nodes[i];
		G[i].num = i;
	}

	vector<pair<int, int>> edges = findAllEdges(nodes);	
	for(auto it = edges.begin(); it != edges.end(); it++)
		boost::add_edge(it->first, it->second, G);	

	ofstream dotfile("cfg.dot");
	boost::write_graphviz(dotfile, G); 
	dotfile.close();

	string o_arg = string("-o") + " diagram.png";
	char* args[] = {
		const_cast<char*>("dot"), 
		const_cast<char*>("Tpng"), 
		const_cast<char*>("-Gsize=8,4!"), 
		const_cast<char*>("-Gdpi=100"),
		const_cast<char*>("cfg.dot"),
		const_cast<char*>(o_arg.c_str())
   	};

	//Ovaj deo je manje-vise kopiran sa adrese:
	//https://stackoverflow.com/questions/45225761/generate-image-of-graphviz-graph-given-dot-text-c
	const int argc = sizeof(args)/sizeof(args[0]);
	Agraph_t *g, *prev = NULL;
	GVC_t *gvc;
	
	gvc = gvContext();
	gvParseArgs(gvc, argc, args);

	while ((g = gvNextInputGraph(gvc))) {
		if (prev) {
			gvFreeLayout(gvc, prev);
			agclose(prev);
		}
		gvLayoutJobs(gvc, g);
		gvRenderJobs(gvc, g);
		prev = g;
	}

	gvFreeContext(gvc);
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
