#include <string>
#include <iostream>
#include "Graph.h"

using namespace std;

bool toInt(string &str) {
    try {
        string str1 = to_string(stoi(str));
        if (str1.length() != str.length()) {
            cerr << "Ошибка: " << str << " не может быть преобразована в int (неверный аргумент)." << endl;
            return false;
        }

        if (stoi(str) < 0) {
            cerr << "Ошибка: Число должно быть положительным" << endl;
            return false;
        }
        return true;
    }
    catch (const invalid_argument) {
        cerr << "Ошибка: " << str << " не может быть преобразована в int (неверный аргумент)." << endl;
        return false;
    }
    catch (const out_of_range) {
        cerr << "Ошибка: " << str << " выходит за пределы диапазона int." << endl;
        return false;
    }
}

void Menu(Graph& graph) {
    while (true) {
        cout << "Меню:\n1.Создать\n2.Загрузить\n3.Посмотреть\n4.Сохранить\n5.Поиск пути\n6.Проверка связности\n";
        string enter = "";
        cout << "Выбор: ";
        getline(cin, enter);

        while (!toInt(enter)) {
            cout << "Выбор: ";
            getline(cin, enter);
        }

        switch (stoi(enter)) {
        case 1:
            cin >> graph;
            break;
        case 2:
            graph.loadFromFile();
            break;
        case 3:
            cout << graph;
            break;
        case 4:
            graph.saveToFile();
            break;
        case 5:
            graph.checkWay();
            break;
        case 6:
            graph.checkConnection();
            break;
        }
    }
}

int main() {
    Graph graph;
    setlocale(LC_ALL, "rus");

    Menu(graph);
}