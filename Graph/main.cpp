#include <iostream>
#include "Graph.h"
#include "Node.h"
#include <Windows.h>
using namespace std;

void printMenu() {
	cout << "-----������ ������-----" << endl;
	cout << "  1 - ������� ����" << endl;
	cout << "  2 - �������� �������" << endl;
	cout << "  3 - �������� �����" << endl;
	cout << "  4 - ������� ����" << endl;
	cout << "  5 - ����� � �������" << endl;
	cout << "  6 - ����� � ������" << endl;
	cout << "  7 - ����� ������������� ��������" << endl;
	cout << "  8 - ����� �����" << endl;
	cout << "  9 - ����� ���������� ����" << endl;
	cout << "  10 - ��������� ���� � ����" << endl;
	cout << "  11 - ��������� ���� �� ����" << endl;
	cout << "  12 - �������������� ���� �����" << endl;
	cout << "  0 - ������" << endl;
	cout << "  -1 - �����\n\n";
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
		cout << "\n  ������� ����� �������: ";
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
			cout << "  id ������� ������ = ";
			cin >> idSrc;
			cout << "  id ������� ����� = ";
			cin >> idDest;
			g.AddEdge(idSrc, idDest);
			break;
		}


		case 4:
			g.Print();
			break;

		case 5: {
			int idSrc;
			cout << "  ������� ��������� �������" << endl;
			cout << "  id = ";
			cin >> idSrc;
			g.DFS(idSrc);
			break;
		}

		case 6: {
			int idSrc;
			cout << "  ������� ��������� �������" << endl;
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
			cout << "  id ������� ������ = ";
			cin >> idSrc;
			cout << "  id ������� ����� = ";
			cin >> idDest;
			g.GetShortestPath(idSrc, idDest);
			break;
		}

		case 10: {
			string filename;
			cout << "  ������� �������� �����: ";
			cin >> filename;
			g.SaveToFile(filename);
			break;
		}

		case 11: {
			string filename;
			cout << "  ������� �������� �����: ";
			cin >> filename;
			g.LoadFromFile(filename);
			break;
		}

		case 12: {
			cout << "  ����� ��� �� ������ ��������";
			cout << "  1 - �����������������";
			cout << "  2 - ������";
			cout << "  3 - ��������������";
			int type, value;
			cin >> type;
			cout << "  1 - ��  2 - ��� : ";
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
			cout << "  ������! �� ���������� �������." << endl;
			printMenu();
			break;
		}
	}
	return 0;
}

