/*
 * WeightedGraph.h
 *
 *  Created on: 29 Apr 2023
 *      Author: 2002345
 */
#ifndef H_weightedGraph
#define H_weightedGraph

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>

using namespace std;

class WeightedGraphType {
protected:
	int gSize;      //number of vertices
	list<int> *graph; // Store adjacency list
	double **weights; // Store weights of edges
public:
	WeightedGraphType(int size = 0);
	~WeightedGraphType();
	void breadthFirstTraversal();

	list<int> getAdjancencyList(int index) {
		return graph[index];
	}

	double getWeight(int i, int j) {
		return weights[i][j];
	}

	void printAdjacencyList();
	void printAdjacencyMatrix();
};

WeightedGraphType::WeightedGraphType(int size) {
	gSize = 0;
	ifstream infile;
	char fileName[50] = "Weights.txt";

	cout << "Enter graph adjacency matrix file name: ";
	cin >> fileName;
	cout << endl;

	infile.open(fileName);

	if (!infile) {
		cout << "Cannot open input file." << endl;
		return;
	}

	gSize = size;

	graph = new list<int> [gSize];

	weights = new double*[gSize];

	for (int i = 0; i < gSize; i++)
		weights[i] = new double[gSize];

	for (int i = 0; i < gSize; i++) {
		for (int j = 0; j < gSize; j++) {
			double value;
			infile >> value;
			if (value == 0)
				weights[i][j] = DBL_MAX; //system constant - maximum value of double
			else {
				weights[i][j] = value;
				graph[i].push_back(j);
			}
		}
	}
	infile.close();
}

WeightedGraphType::~WeightedGraphType() {
	for (int i = 0; i < gSize; i++)
		delete[] weights[i];

	delete[] weights;

	for (int index = 0; index < gSize; index++)
		graph[index].clear();

	delete[] graph;
}

void WeightedGraphType::printAdjacencyMatrix() { //print adjacency matrix for debug purpose
	cout<<"\nAdjacency Matrix" << endl;
	for (int i = 0; i < gSize; i++) {
		for (int j = 0; j < gSize; j++) {
			cout << setw(8) << (weights[i][j] == DBL_MAX ? 0.0 : weights[i][j]); //as adjacency value, zero means no direct connection
		}
		cout << endl;
	}
}

void WeightedGraphType::printAdjacencyList() { //print adjacency list for debug purpose
	cout<<"\nAdjacency List" << endl;
	for (int index = 0; index < gSize; index++) {
		cout << index << ": ";
		for (int e : graph[index])
			cout << e << " ";
		cout << endl;
	}

	cout << endl;
}
void WeightedGraphType::breadthFirstTraversal() {
	queue<int> queue;

	bool *visited;
	visited = new bool[gSize];

	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false;

	list<int>::iterator graphIt;

	for (int index = 0; index < gSize; index++)
		if (!visited[index]) {
			queue.push(index);
			visited[index] = true;
			cout << " " << index << " ";

			while (!queue.empty()) {
				int u = queue.front();
				queue.pop();

				for (graphIt = graph[u].begin(); graphIt != graph[u].end();
						++graphIt) {
					int w = *graphIt;
					if (!visited[w]) {
						queue.push(w);
						visited[w] = true;
						cout << " " << w << " ";
					}
				}
			}
		}

	delete[] visited;
}


#endif
