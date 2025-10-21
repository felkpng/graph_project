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
            std::cout << "(Чтобы закончить ввод пунктов нажмите Enter)" << std::endl;
            name = " ";
            while (name.find(' ') != std::string::npos) {
                    std::cout << "Пункт: ";
                    std::getline(std::cin, name);
                }
            if (name == "") { break; }

            std::cout << "(Чтобы закончить ввод смежных пунктов нажмите Enter)" << std::endl;
            std::string input = " ";
            std::vector<std::string> v = {};

            while (input != "") {
                input = " ";
                while (input.find(' ') != std::string::npos) {
                    std::cout << "Смежного пункт: ";
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

        graph.setAdjacency(adjacency);
    }

    return is;
}

bool Graph::isWay(std::string start, std::string stop) {
    if (start == stop) return true;
    std::map<std::string, std::vector<std::string>> adjacency = getAdjacency();

    if (!adjacency.count(start) || !adjacency.count(stop)) return false;
    std::vector<std::string> v = adjacency[start];
    for (int x = 0; x < v.size(); x++) {
        if (v[x] != stop || isWay(v[x], stop)) return true;
    }

    return false;
}

void Graph::saveToFile() {
    system("cls");
    std::cout << "Имя файла для сохранения: ";
    std::string fileName;

    getline(std::cin, fileName);

    std::ofstream outFile(fileName);

    if (outFile.is_open()){
        outFile << *this;
        outFile.close();
    }
    else
        std::cout << "Ошибка открытия файла";
}

void Graph::loadFromFile() {
    system("cls");
    std::cout << "Имя файла для загрузки: ";
    std::string fileName;

    getline(std::cin, fileName);

    std::ifstream inFile(fileName);

    if (inFile.is_open()) {
        inFile >> *this;
        inFile.close();
    }
    else
        std::cout << "Ошибка открытия файла" << std::endl;
}
