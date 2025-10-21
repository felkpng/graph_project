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
                data += pair.second[x] + " ";
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

    if (fromConsole) {
        std::string name = " ";
        std::map<std::string, std::vector<std::string>> adjacency;

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

        graph.setAdjacency(adjacency);
    }
    else {}

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
