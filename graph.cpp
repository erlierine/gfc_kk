#include "graph.hpp"

using namespace std;


void createFlowGraph(vector<string> &lines) {
	vector<string> nodes = createListOfBB(lines);
	//TODO
}

vector<string> createListOfBB(vector<string> &lines) {
	
	vector<bool> ins_leader(lines.size(), false);
	ins_leader[0] = true;
	regex gotoStat(".+ goto .*");
	regex lbl_start(".+:");
	map<string, int> lbl_ixs;
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
			cout << basic_block << endl;
			bbs.push_back(basic_block);
		}
	}	

	return bbs;	
}

