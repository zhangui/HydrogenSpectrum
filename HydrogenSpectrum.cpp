//============================================================================
// Name        : HydrogenWavelengthShell.cpp
// Author      : Yang Zhang
// Version     : 1.0
// Copyright   : @YangZhang
// Description : Hydrogen Spectrum in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

double getWavelength();
double energy(double wavelength);
void init();
double shells(int upper, int lower);
void search(double kJ);

class Node {
public:
	int upper;
	int lower;
	double kJ;
	Node* next;
	void push(int upper, int lower, double kJ);
	Node(){
		upper = 0;
		lower = 0;
		kJ = 0;
		next = NULL;
	}
	static Node* top;
	static Node* bot;
	static Node* cursor;
};
Node* Node::top;
Node* Node::bot;
Node* Node::cursor;

void Node::push(int upper, int lower, double kJ)
{
	this->upper = upper;
	this->lower = lower;
	this->kJ = kJ;
	if(Node::bot == NULL){
		Node::bot = this;
		Node::top = this;
	} else {
		Node::top->next = this;
		Node::top = this;
	}
}

int main() {
	double wavelength, kJ;
	cout << "This program transfers hydrogen spectrum from wavelength to electron energy levels." << endl; // prints !!!Hello World!!!
	wavelength = getWavelength();
	kJ = energy(wavelength);
	init();
	/*Node::cursor = Node::bot;
	while(Node::cursor != NULL){
		cout << Node::cursor->upper << ", " << Node::cursor->lower << ", " << Node::cursor->kJ << endl;
		Node::cursor = Node::cursor->next;
	}*/
	search(kJ);
	return 0;
}

double getWavelength()
{
	double wavelength;
	cout << "Type in Wavelength" << endl;
	cin >> wavelength;
	return wavelength;
}

double energy(double wavelength)
{
	double kJ;
	kJ = 119627.0/wavelength;
	return kJ;
}

void init()
{
	Node* obj;
	Node::top = NULL;
	Node::bot = NULL;
	double energy;
	for(int i = 1; i < 18; i++){
		for(int j = i; j < 18; j++){
			obj = new Node;
			energy = shells(j, i);
			obj->push(j, i, energy);
		}
	}
}

void search(double kJ)
{
	Node::cursor = Node::bot;
	while(Node::cursor != NULL)
	{
		if(int(Node::cursor->kJ) == int(kJ)){
			cout << Node::cursor->upper << ", " << Node::cursor->lower << ", " << Node::cursor->kJ << endl;
			return;
		}
		Node::cursor = Node::cursor->next;
	}
}

double shells(int upper, int lower)
{
	double lower1, upper1;
	lower1 = 1312.04/(lower*lower);
	upper1 = 1312.04/(upper*upper);
	return(lower1 - upper1);
}


