#pragma once
#include "Graph.h"
#include "fstream"
#include "iostream"
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

void DFS(string i, map<string, vector<string>>& adjacency, map<string, bool>& visited) {
    visited[i] = true;
    for (string u : adjacency[i]) {
        if (!visited[u])
            DFS(u, adjacency, visited);
    }
}

bool dfs_method(Graph& graph) {
    map<string, vector<string>> adjacency = graph.getAdjacency();
    map<string, bool> visited;
    graph.get_keys();

    for (const auto& k : graph.keys)
        visited[k] = false;

    string start = graph.keys[0];

    DFS(start, adjacency, visited);

    for (const auto& pair : visited)
        if (!pair.second)
            return false;
    return true;
}

bool bfs_method(Graph& graph) { return true; }

bool dsu_method(Graph& graph) { return true; }

bool floydWarshall_method(Graph& graph) { return true; }

void LoadData(vector<Graph>& graphs) {
    string directory_path = "./data/";

    for (const auto& entry : fs::directory_iterator(directory_path)) {
        string file_path = entry.path().string();

        std::ifstream file(file_path);
        if (file.is_open()) {
            Graph NewGraph;
            file >> NewGraph;
            graphs.push_back(NewGraph);
        }
    }
}

void tester() {
    vector<Graph> graphs;
    LoadData(graphs);
    cout << "Загруженно " << graphs.size() << " графов\n\n";

    for (int i = 0; i < graphs.size(); i++) {
        const auto& dfs_result = dfs_method(graphs[i]);
        //const auto& bfs_result = bfs_method(graphs[i]);
        //const auto& dsu_result = dsu_method(graphs[i]);
        //const auto& floyd_result = floydWarshall_method(graphs[i]);

        cout << "Graph" << i + 1 << endl;
        cout << "DFS:           " << (dfs_result ? "связанный" : "не связанный") << endl;
        //cout << "BFS:           " << (bfs_result ? "связанный" : "не связанный") << endl;
        //cout << "DSU:           " << (dsu_result ? "связанный" : "не связанный") << endl;
        //cout << "FloydWarshall: " << (floyd_result ? "связанный" : "не связанный") << endl << endl;
    }
}
