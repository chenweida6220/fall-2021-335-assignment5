/*
  Name: Wei Da Chen
  Date: 12/10/2021
	Header file: graph.h
*/

/*
This file contains the Graph, AdjacentNode, and Vertex class(es)/implementation(s).
*/

#ifndef STUDENT_GRAPH
#define STUDENT_GRAPH

#include <iostream>
#include <limits>

#include "binary_heap.h"

using namespace std;

//This file is for your graph implementation.
//Add everything you need in between the "ifndef and "endif" statements.
//Do not put anything outside those statements

struct AdjacentNode {
  int number;
  double weight;
};

struct Vertex {
  vector<AdjacentNode> list;
  Vertex *paths;
  Vertex(int val) : value(val), paths(nullptr) {}
  int value;
  double distance = numeric_limits<double>::max();
  bool isKnown = false;
};

class Graph {
public:
  int numVertices;
  vector<Vertex *> Vertex_;    // the adjacency list of vectors

    Graph() : numVertices(0) {}

    Graph(int vertices) : numVertices(vertices), Vertex_(++vertices) {
        for (int i = 1; i <= vertices; ++i) {
            Vertex_[i] = new Vertex(i);
        }
    }

    void add_connection(int vertex, int connectedVertex, double weight) {
        AdjacentNode newAdjNode{connectedVertex, weight};
        Vertex_[vertex]->list.push_back(newAdjNode);
    }

    void print() {
        cout << "\nGraph: " << endl;
        for (int i = 1; i < numVertices + 1; ++i) {
          cout << i << "---> ";

          for(auto &node : Vertex_[i]->list) {
            cout << node.number << " ";
          }
        }
        cout << endl;
    }

    // Q1: Adjacency result-printer
    string is_connected(int vertex, int connectedVertex) {
        for(auto &node : Vertex_[vertex]->list)
            if (node.number == connectedVertex)
                return "connected " + to_string(node.weight).substr(0, to_string(node.weight).find_last_not_of('0') + 1);
        return "not_connected ";
    }

    // Prints out the path for Dijkstra algorithm
    void printpath(Vertex *list) {
        if(list->paths != nullptr)
        {
            printpath(list->paths);
        }
        cout << list->value << " ";
    }

    // Dijkstra's Algorithm
    void Dijkstra(int starting_vertex)
    {
        BinaryHeap<int> queue;
        queue.insert(starting_vertex);
        Vertex_[starting_vertex]->distance = 0;
        while (!queue.isEmpty())
        {
            int min_vertex = queue.findMin();
            Vertex_[min_vertex]->isKnown = true;
            queue.deleteMin();
            for (unsigned int i = 0; i < Vertex_[min_vertex]->list.size(); ++i)
            {
                // placeholder variable
                int num_of_min_vertex = Vertex_[min_vertex]->list[i].number;
                double cost = Vertex_[min_vertex]->list[i].weight;
                if (Vertex_[min_vertex]->isKnown == true && Vertex_[min_vertex]->distance + cost < Vertex_[num_of_min_vertex]->distance)
                {
                    Vertex_[num_of_min_vertex]->distance = Vertex_[min_vertex]->distance + cost;
                    Vertex_[num_of_min_vertex]->paths = Vertex_[min_vertex];
                    queue.insert(num_of_min_vertex);
                }
            }
        }

        vector<double> path_vector;
        //Print shortest_path
        for (int i = 1; i <= numVertices; i++)
        {
            cout << i << ": ";
            double cost = Vertex_[i]->distance;

            if (cost != std::numeric_limits<double>::max())
            {
                Vertex *test = Vertex_[i];
                printpath(test);
                cout.precision(1);
                cout << fixed << "cost: " << cost << endl;
            }
            else
            {
                cout << "not_possible" << endl;
            }
        }
    }
};

#endif
