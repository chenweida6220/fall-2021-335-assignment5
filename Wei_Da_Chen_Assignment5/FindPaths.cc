/*
  Name: Wei Da Chen
  Date: 12/10/2021
	File: FindPaths.cc
*/

/*
This file contains the driver program that uses Dijkstra’s	Algorithm	to	find
the	shortest	paths	from	a	given	starting	vertex	to	all	vertices	in	the	graph	file.
*/

#include "graph.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int pathfindDriver(int argc, char **argv) {

  //Begin your code here. Feel free to add any helper functions or classes you need,
  //as long as we only have to call this function to run the specified assignment.

	const string graph_filename(argv[1]);
	int originVertex(atoi(argv[2]));

	// splitting string
	auto splitterString = [&] (string &line, string &line2) {
		line2 = line.substr(0, line.find(" "));
		line = line.substr(line.find(" ") + 1);
	};

	// opens the graph file
	ifstream inputFile;
	inputFile.open(graph_filename);
	if (inputFile.fail()) {
		cerr << "Cannot open graph file." << endl;
		exit(EXIT_FAILURE);
	}

	string line, line2;
	getline(inputFile, line);
	Graph graph(stoi(line));

	while (getline(inputFile, line)) {
		splitterString(line, line2);
		int vertex = stoi(line2);
		int connected;
		double weight;
		while (line.find(" ") != string::npos) {
			splitterString(line, line2);
			connected = stoi(line2);
			splitterString(line, line2);
			weight = stod(line2);
			graph.add_connection(vertex, connected, weight);
		}
	}

	// closing graph file
	inputFile.close();
  graph.Dijkstra(originVertex);

  return 0;
}

int main(int argc, char **argv) {
    if (argc != 3) {
		cout << "Usage: " << argv[0] << " <GRAPH_File>" << "<ADJACENCY_QUERYFILE>" << endl;
		return 0;
    }

    pathfindDriver(argc, argv);

    return 0;
}
