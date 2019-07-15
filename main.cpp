#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "graph.hpp"

using namespace std;


int main(int argc, char** argv) {
	string line;
	vector<string> lines;
	ifstream file(argv[1]);
	if (file.is_open()) {
		while (getline(file, line))
			lines.push_back(line);	

		file.close();
	} else {
		cerr << "Neuspesno otvaranje datoteke" << endl;
		exit(EXIT_FAILURE);
	}
	//string* tac = compile3ac(lines);
	createFlowGraph(lines);
	return 0;
}
