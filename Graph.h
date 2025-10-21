#pragma once
#include <map>
#include <string>
#include <vector>

class Graph
{
private:
	std::map<std::string, std::vector<std::string>> adjacency;
public:
	bool isWay(std::string start, std::string stop);
	std::map<std::string, std::vector<std::string>> getAdjacency() const { return adjacency; };
	void setAdjacency(const std::map<std::string, std::vector<std::string>> a) { adjacency = a; }
	void saveToFile();
	void loadFromFile();

	friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
	friend std::istream& operator>>(std::istream& os, Graph& graph);
};

