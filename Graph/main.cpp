#include <iostream>
#include "Graph.h"
#include "Node.h"
#include <Windows.h>
using namespace std;

void printMenu() {
	cout << "-----Список команд-----" << endl;
	cout << "  1 - Создать граф" << endl;
	cout << "  2 - Добавить вершину" << endl;
	cout << "  3 - Добавить ребро" << endl;
	cout << "  4 - Вывести граф" << endl;
	cout << "  5 - Обход в глубину" << endl;
	cout << "  6 - Обход в ширину" << endl;
	cout << "  7 - Найти изолированные подграфы" << endl;
	cout << "  8 - Найти циклы" << endl;
	cout << "  9 - Найти кратчайший путь" << endl;
	cout << "  10 - Сохранить граф в файл" << endl;
	cout << "  11 - Загрузить граф из файл" << endl;
	cout << "  12 - Преобразование типа графа" << endl;
	cout << "  0 - Помощь" << endl;
	cout << "  -1 - Выход\n\n";
}

int main()
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0);

	system("color F0");
	setlocale(LC_ALL, "Ru");
	Graph g = Graph();
	Node n = Node();

	int command = 0;
	printMenu();
	while (command != -1) {
		cout << "\n  Введите номер комадны: ";
		cin >> command;
		switch (command)
		{
		case 0:
			printMenu();
			break;

		case 1:
			g.Input();
			break;

		case 2:
			n.Input();
			g.AddNode(n);
			break;

		case 3: {
			int idSrc, idDest;
			cout << "  id вершины начала = ";
			cin >> idSrc;
			cout << "  id вершины конца = ";
			cin >> idDest;
			g.AddEdge(idSrc, idDest);
			break;
		}


		case 4:
			g.Print();
			break;

		case 5: {
			int idSrc;
			cout << "  Введите начальную вершину" << endl;
			cout << "  id = ";
			cin >> idSrc;
			g.DFS(idSrc);
			break;
		}

		case 6: {
			int idSrc;
			cout << "  Введите начальную вершину" << endl;
			cout << "  id = ";
			cin >> idSrc;
			g.DFS(idSrc);
			break;
		}

		case 7:
			g.FindIsolatedSubgraphs();
			break;

		case 8:
			g.GetAllCycles();
			break;

		case 9: {
			int idSrc, idDest;
			cout << "  id вершины начала = ";
			cin >> idSrc;
			cout << "  id вершины конца = ";
			cin >> idDest;
			g.GetShortestPath(idSrc, idDest);
			break;
		}

		case 10: {
			string filename;
			cout << "  Введите название файла: ";
			cin >> filename;
			g.SaveToFile(filename);
			break;
		}

		case 11: {
			string filename;
			cout << "  Введите название файла: ";
			cin >> filename;
			g.LoadFromFile(filename);
			break;
		}

		case 12: {
			cout << "  Какой тип вы хотите изменить";
			cout << "  1 - Ориентированность";
			cout << "  2 - Мульти";
			cout << "  3 - Многодольность";
			int type, value;
			cin >> type;
			cout << "  1 - Да  2 - Нет : ";
			cin >> value;

			if (type == 1) {
				g.ChangeGraphTypeDirected(value == 1);
			}
			else if (type == 2) {
				g.ChangeGraphTypeMulti(value == 1);
			}
			else {
				g.ChangeGraphTypeMultiPart(value == 1);
			}

		}

		default:
			cout << "  Ошибка! Не правильная команда." << endl;
			printMenu();
			break;
		}
	}
	return 0;
}

