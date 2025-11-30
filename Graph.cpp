#include "Graph.h"
#include <sstream>
#include <fstream>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Graph& graph) {
    bool toConsole = (&os == &std::cout);
    std::string data;
    std::map<std::string, std::vector<std::string>> adjacency = graph.getAdjacency();

    if (toConsole) {
        std::system("cls");
        data = "Список смежности графа\n";

        for (const auto& pair : adjacency) {
            data = data + pair.first + ": ";
            for (int x = 0; x < pair.second.size(); x++) {
                data += pair.second[x];
                if (x + 1 != pair.second.size()) data += " ";
            }
            data += "\n";
        }
        data += "\n";

        os << data;
    }
    else {
        for (const auto& pair : adjacency) {
            data += pair.first + "\n";
            for (int x = 0; x < pair.second.size(); x++) {
                data += pair.second[x] + " ";
            }
            data += "\n";
        }

        os << data;
    }

    return os;
}

std::istream& operator>>(std::istream& is, Graph& graph) {
    bool fromConsole = (&is == &std::cin);
    std::map<std::string, std::vector<std::string>> adjacency;

    if (fromConsole) {
        std::string name = " ";

        while (name != "") {
            std::cout << "(Для завершения нажмите Enter)" << std::endl;
            name = " ";
            while (name.find(' ') != std::string::npos) {
                std::cout << "Вершина: ";
                std::getline(std::cin, name);
            }
            if (name == "") { break; }

            std::cout << "(Для перехода к следущей вершине нажмите Enter)" << std::endl;
            std::string input = " ";
            std::vector<std::string> v = {};

            while (input != "") {
                input = " ";
                while (input.find(' ') != std::string::npos) {
                    std::cout << "Связанная вершина: ";
                    std::getline(std::cin, input);
                }

                if (input != "") v.push_back(input);
            }

            if (name != "") adjacency[name] = v;
        }
    }
    else {
        std::string name;
        std::string line;

        while (true) {
            if (!std::getline(is, name)) break;
            if (name.empty()) continue;
            if (!std::getline(is, line)) break;

            std::istringstream iss(line);
            std::vector<std::string> neighbors;
            std::string neighbor;

            while (iss >> neighbor)
                neighbors.push_back(neighbor);



            adjacency[name] = neighbors;
        }
    }

    graph.setAdjacency(adjacency);
    return is;
}

void Graph::get_keys() {
    keys = {};
    for (const auto& pair : adjacency)
        keys.push_back(pair.first);
}
