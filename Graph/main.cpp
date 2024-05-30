#include <iostream>
//#include "Graph.h"
#include "Node.h"
#include "GraphPerformanceTester.h"
#include <Windows.h>
using namespace std;

void printMenu() {
	cout << "-----������ ������-----" << endl;
	cout << "  1 - ������� ����" << endl;
	cout << "  2 - �������� �������" << endl;
	cout << "  3 - �������� �����" << endl;
	cout << "  4 - ������� �������" << endl;
	cout << "  5 - ������� �����" << endl;
	cout << "  6 - ������� ����" << endl;
	cout << "  7 - ���������" << endl;
	//cout << "  5 - ����� � �������" << endl;
	//cout << "  6 - ����� � ������" << endl;
	//cout << "  7 - ����� ������������� ��������" << endl;
	//cout << "  8 - ����� �����" << endl;
	//cout << "  9 - ����� ���������� ����" << endl;
	//cout << "  10 - ��������� ���� � ����" << endl;
	//cout << "  11 - ��������� ���� �� ����" << endl;
	//cout << "  12 - �������������� ���� �����" << endl;
	cout << "  0 - ������" << endl;
	cout << "  -1 - �����\n\n";
}

void printAlgsMenu() {
	cout << "-----������ ����������-----" << endl;
	cout << "  1 - ����� � �������" << endl;
	cout << "  2 - ����� � ������" << endl;
	cout << "  3 - ����� ������������� ��������" << endl;
	cout << "  4 - ����� �����" << endl;
	cout << "  5 - ����� ���������� ����" << endl;
	cout << "  -1 - �����" << endl;
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
		cout << "\n  ������� ����� �������: ";
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
				cout << "  id ������� ������ = ";
				cin >> idSrc;
				cout << "  id ������� ����� = ";
				cin >> idDest;
				g.AddEdge(idSrc, idDest);
				break;

			case 4:
				cout << "  ������� id �������, ������� ����� �������" << endl << "  id = ";
				cin >> nodeId;
				g.DeleteNode(nodeId);
				break;

			case 5:
				cout << "  id ������� ������ = ";
				cin >> idSrc;
				cout << "  id ������� ����� = ";
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
				cout << "  ������! �� ���������� �������." << endl;
				printMenu();
				break;
			}
		}
		else {
			switch (command) {
				printAlgsMenu();
			case 1: {
				int idSrc;
				cout << "  ������� ��������� �������" << endl;
				cout << "  id = ";
				cin >> idSrc;
				g.DFS(idSrc);
				break;
			}

			case 2: {
				int idSrc;
				cout << "  ������� ��������� �������" << endl;
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
				cout << "  id ������� ������ = ";
				cin >> idSrc;
				cout << "  id ������� ����� = ";
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
				cout << "  ������! �� ���������� �������." << endl;
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

