#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;

class Graph {
private:
    int edgesList;
    int edgesMat;
    int nodes;
    vector<int>* adjList;
    int* adjMatrix;

public:
    Graph(int);
    Graph();
    void addEdgeAdjList(int, int);
    void addEdgeAdjMatrix(int, int);
    string printAdjList();
    string printAdjMat();
    string printAdjMat_clean();
    
    string DFS(int, int);
    string depthHelper(int, int, stack<int>&, list<int>&,
                       vector<vector<int>>&, vector<bool>&);

    string BFS(int, int);
    string breadthHelper(int, int, queue<int>&, list<int>&,
                         vector<vector<int>>&, vector<bool>&);

    string print_visited(list<int>);
    string print_path(vector<vector<int>>&, int, int);
    bool contains(list<int>, int);
    void sortAdjList();

    void loadGraphList(string, int);
    void loadGraphMat(string, int, int);
};


void Graph::loadGraphList(string input, int a) {
    adjList = new vector<int>[a];
    nodes = a;

    int u, v;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '(') {
            u = input[i + 1] - '0';
            v = input[i + 3] - '0';
            addEdgeAdjList(u, v);
        }
    }
    sortAdjList();
}


void Graph::loadGraphMat(string input, int a, int b) {
    adjMatrix = new int[a * b];
    nodes = a;

    for (int i = 0; i < a * b; i++)
        adjMatrix[i] = 0;

    int u, v;
    for (int i = 0; i < input.size(); i++) {
        if (input[i] == '(') {
            u = input[i + 1] - '0';
            v = input[i + 3] - '0';
            addEdgeAdjMatrix(u, v);
        }
    }
}

Graph::Graph() {
    edgesList = 0;
    edgesMat = 0;
}

Graph::Graph(int n) {
    nodes = n;
    adjList = new vector<int>[nodes];
    adjMatrix = new int[nodes * nodes];
    for (int i = 0; i < nodes * nodes; i++)
        adjMatrix[i] = 0;
    edgesList = 0;
    edgesMat = 0;
}

void Graph::addEdgeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edgesList++;
}

void Graph::addEdgeAdjMatrix(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
    edgesMat++;
}

string Graph::printAdjList() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        aux << "vertex " << i << " :";
        for (int j = 0; j < adjList[i].size(); j++) {
            aux << " " << adjList[i][j];
        }
        aux << " ";
    }
    return aux.str();
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i++)
        sort(adjList[i].begin(), adjList[i].end());
}

string Graph::printAdjMat() {
    stringstream aux;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            aux << adjMatrix[i * nodes + j] << " ";
        }
    }
    return aux.str();
}


string Graph::DFS(int start, int goal) {
    list<int> visited;
    stack<int> st;
    vector<vector<int>> paths(nodes, vector<int>(1, -1));
    vector<bool> seen(nodes, false);

    st.push(start);
    seen[start] = true;

    string ans = depthHelper(start, goal, st, visited, paths, seen);
    ans += print_path(paths, start, goal);
    return ans;
}

string Graph::depthHelper(int current, int goal, stack<int>& st,
    list<int>& visited, vector<vector<int>>& paths, vector<bool>& seen) {

    if (st.empty())
        return " node not found";

    current = st.top();
    st.pop();

    visited.push_back(current);

    if (current == goal)
        return print_visited(visited);

    for (int nxt : adjList[current]) {
        if (!seen[nxt]) {
            seen[nxt] = true;
            st.push(nxt);
            paths[nxt][0] = current;
        }
    }

    return depthHelper(current, goal, st, visited, paths, seen);
}

string Graph::BFS(int start, int goal) {
    list<int> visited;
    queue<int> qu;
    vector<vector<int>> paths(nodes, vector<int>(1, -1));
    vector<bool> seen(nodes, false);

    qu.push(start);
    seen[start] = true;

    string ans = breadthHelper(start, goal, qu, visited, paths, seen);
    ans += print_path(paths, start, goal);
    return ans;
}

string Graph::breadthHelper(int current, int goal, queue<int>& qu,
    list<int>& visited, vector<vector<int>>& paths, vector<bool>& seen) {

    if (qu.empty())
        return " node not found";

    current = qu.front();
    qu.pop();

    visited.push_back(current);

    if (current == goal)
        return print_visited(visited);

    for (int nxt : adjList[current]) {
        if (!seen[nxt]) {
            seen[nxt] = true;
            qu.push(nxt);
            paths[nxt][0] = current;
        }
    }

    return breadthHelper(current, goal, qu, visited, paths, seen);
}

bool Graph::contains(list<int> ls, int node){
		list<int>::iterator it;
		it = find(ls.begin(), ls.end(), node);
		if(it != ls.end())
			return true;
		else
			return false;
}


string Graph::print_visited(list<int> q) {
    stringstream aux;
    aux << "visited: ";
    while (!q.empty()) {
        aux << q.front() << " ";
        q.pop_front();
    }
    return aux.str();
}

string Graph::print_path(vector<vector<int>>& path, int start, int goal) {
    int node = goal;
    stack<int> reverse;

    while (node != -1) {
        reverse.push(node);
        if(node == start){
            break;
        }
        node = path[node][0];
        
    }
    stringstream aux;
    aux << "path:";

    while (!reverse.empty()) {
        aux << " " << reverse.top();
        reverse.pop();
    }
    return aux.str();
}

#endif /* Graph_H_ */
