#include <iostream>
#include <fstream>
#include <string>

#include "graph.hpp"

using namespace std;


int main(int argc, char** argv) {
	string line;
	string lines = "";
	ifstream file(argv[1]);
	if (file.is_open()) {
		while (getline(file, line))
			lines += line + "\n";

		file.close();
	} else {
		cerr << "Neuspesno otvaranje datoteke" << endl;
		exit(EXIT_FAILURE);
	}
	cout << lines;	
	//string* tac = compile3ac(lines);
	createFlowGraph(&lines);
	return 0;
}
