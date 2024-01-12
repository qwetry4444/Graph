#include "Node.h"
#include <iostream>

using namespace std;

Node::Node()
	: value(0)
{}

Node::Node(int _id)
	: id(_id)
{}

Node::Node(int _id, int _value)
	: id(_id)
	, value(_value)
{}


Node::~Node()
{}

void Node::Print() {
	cout << value << endl;
}

void Node::Input() {
	cout << "  ¬вод вершины:" << endl;
	cout << "  id = ";
	cin >> id;
	cout << "  value = ";
	cin >> value;
}

