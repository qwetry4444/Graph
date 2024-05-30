#include <iostream>
//#include "Graph.h"
#include "Node.h"
#include "GraphPerformanceTester.h"
#include <Windows.h>
using namespace std;

void printMenu() {
	cout << "-----Список команд-----" << endl;
	cout << "  1 - Создать граф" << endl;
	cout << "  2 - Добавить вершину" << endl;
	cout << "  3 - Добавить ребро" << endl;
	cout << "  4 - Удалить вершину" << endl;
	cout << "  5 - Удалить ребро" << endl;
	cout << "  6 - Вывести граф" << endl;
	cout << "  7 - Алгоритмы" << endl;
	//cout << "  5 - Обход в глубину" << endl;
	//cout << "  6 - Обход в ширину" << endl;
	//cout << "  7 - Найти изолированные подграфы" << endl;
	//cout << "  8 - Найти циклы" << endl;
	//cout << "  9 - Найти кратчайший путь" << endl;
	//cout << "  10 - Сохранить граф в файл" << endl;
	//cout << "  11 - Загрузить граф из файл" << endl;
	//cout << "  12 - Преобразование типа графа" << endl;
	cout << "  0 - Помощь" << endl;
	cout << "  -1 - Выход\n\n";
}

void printAlgsMenu() {
	cout << "-----Список алгоритмов-----" << endl;
	cout << "  1 - Обход в глубину" << endl;
	cout << "  2 - Обход в ширину" << endl;
	cout << "  3 - Найти изолированные подграфы" << endl;
	cout << "  4 - Найти циклы" << endl;
	cout << "  5 - Найти кратчайший путь" << endl;
	cout << "  -1 - Назад" << endl;
}

void menu() {
	int nodeId = 0;
	int idSrc, idDest;

	int command = 0;
	bool algsMenu = false;

	Graph g = Graph();
	Node n = Node();

	printMenu();
	while (command != -1 || algsMenu == true) {
		cout << "\n  Введите номер комадны: ";
		cin >> command;
		if (algsMenu == false) {
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

			case 3:
				cout << "  id вершины начала = ";
				cin >> idSrc;
				cout << "  id вершины конца = ";
				cin >> idDest;
				g.AddEdge(idSrc, idDest);
				break;

			case 4:
				cout << "  Введите id вершины, которую нужно удалить" << endl << "  id = ";
				cin >> nodeId;
				g.DeleteNode(nodeId);
				break;

			case 5:
				cout << "  id вершины начала = ";
				cin >> idSrc;
				cout << "  id вершины конца = ";
				cin >> idDest;
				g.DeleteNode(nodeId);
				break;

			case 6:
				g.Print();
				break;

			case 7:
				algsMenu = true;
				printAlgsMenu();
				break;

			default:
				cout << "  Ошибка! Не правильная команда." << endl;
				printMenu();
				break;
			}
		}
		else {
			switch (command) {
				printAlgsMenu();
			case 1: {
				int idSrc;
				cout << "  Введите начальную вершину" << endl;
				cout << "  id = ";
				cin >> idSrc;
				g.DFS(idSrc);
				break;
			}

			case 2: {
				int idSrc;
				cout << "  Введите начальную вершину" << endl;
				cout << "  id = ";
				cin >> idSrc;
				g.DFS(idSrc);
				break;
			}

			case 3:
				g.GetAllCycles();
				break;

			case 4:
				g.FindIsolatedSubgraphs();
				break;

			case 5: {
				int idSrc, idDest;
				cout << "  id вершины начала = ";
				cin >> idSrc;
				cout << "  id вершины конца = ";
				cin >> idDest;
				g.GetShortestPath(idSrc, idDest);
				break;
			}

			case -1: {
				algsMenu = false;
				command = 0;
				printMenu();
				break;
			}

			default:
				cout << "  Ошибка! Не правильная команда." << endl;
				printAlgsMenu();
				break;
			}
		}
	}
}

int main()
{
	HANDLE h;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, 0);
	system("color F0");
	setlocale(LC_ALL, "Ru");
	

	menu();
	const int maxNodes = 200000;
	const int step = 10000;
	const int edgesPerNode = 10;

	//GraphPerformanceTester tester(maxNodes, step, edgesPerNode);
	//tester.RunTests();
	return 0;
}

