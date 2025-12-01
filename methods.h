#pragma once
#include "Graph.h"
#include "fstream"
#include "iostream"
#include <filesystem>
#include <queue>
#include <set>

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

bool bfs_method(Graph& graph) {
    map<string, vector<string>> adjacency = graph.getAdjacency();
    map<string, bool> visited;
    graph.get_keys();

    for (const auto& k : graph.keys)
        visited[k] = false;

    string start = graph.keys[0];
    queue<string> queue;
    queue.push(start);
    visited[start] = true;

    while (!queue.empty()) {
        string i = queue.front();
        queue.pop();

        for (string u : adjacency[i])
            if (!visited[u]) {
                visited[u] = true;
                queue.push(u);
            }
    }

    for (const auto& pair : visited)
        if (!pair.second)
            return false;
    return true;
}

int Find(vector<vector<string>>& sets, string key) {
    for (int i = 0; i < sets.size(); i++)
        if (find(sets[i].begin(), sets[i].end(), key) != sets[i].end())
            return i;
    return 0;
}

void Union(vector<vector<string>>& sets, int i1, int i2) {
    for (string elem : sets[i2])
        sets[i1].push_back(elem);
    sets.erase(sets.begin() + i2);
}

vector<pair<string, string>> getUniqueEdges(const map<string, vector<string>>& adjacency) {
    vector<pair<string, string>> edges;
    set<pair<string, string>> unique_edge_set;

    for (const auto& node_pair : adjacency) {
        string u = node_pair.first;
        for (const string& v : node_pair.second) {
            if (u < v) {
                unique_edge_set.insert({ u, v });
            }
            else {
                unique_edge_set.insert({ v, u });
            }
        }
    }

    for (const auto& edge : unique_edge_set) {
        edges.push_back(edge);
    }

    return edges;
}

bool dsu_method(Graph& graph) {
    map<string, vector<string>> adjacency = graph.getAdjacency();
    vector<vector<string>> sets;
    vector<pair<string, string>> edges = getUniqueEdges(adjacency);
    graph.get_keys();

    for (const auto& key : graph.keys)
        sets.push_back({ key });

    for (const auto& edge : edges) {
        int i1 = Find(sets, edge.first);
        int i2 = Find(sets, edge.second);

        if (i1 != i2)
            Union(sets, i1, i2);
    }

    return (sets.size() == 1);
}

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
        const auto& bfs_result = bfs_method(graphs[i]);
        const auto& dsu_result = dsu_method(graphs[i]);
        //const auto& floyd_result = floydWarshall_method(graphs[i]);

        cout << "Graph" << i + 1 << endl;
        cout << "DFS:           " << (dfs_result ? "связанный" : "не связанный") << endl;
        cout << "BFS:           " << (bfs_result ? "связанный" : "не связанный") << endl;
        cout << "DSU:           " << (dsu_result ? "связанный" : "не связанный") << endl;
        //cout << "FloydWarshall: " << (floyd_result ? "связанный" : "не связанный") << endl << endl;
    }
}
