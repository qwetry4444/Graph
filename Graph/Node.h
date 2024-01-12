#pragma once

class Node {
private:
	int id;
	int value;

public:
	Node();
	Node(int, int);
	Node(int);
	~Node();
	void Print();
	void Input();

	friend class Graph;
};
