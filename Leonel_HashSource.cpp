#ifndef _SOURCE_CPP
#define _SOURCE_CPP

#include <iostream>
#include <string>
#include "LeoHashTable.h"
#include "Pokemon.h"

using namespace std;

//This is my test file incase you are wondering how I made use of the HashTable.

int main()
{
	char endProgram;
	HashTable test2(5);
	Pokemon* pobject1 = new Pokemon("Pikachu", 1, "Electric", 10, 5);
	Pokemon* pobject2 = new Pokemon("Magikarp", 4, "Water", 300, 300);
	Pokemon* pobject3 = new Pokemon("Bulbasaur", 5, "Grass", 300, 300);
	Pokemon* pobject4 = new Pokemon("Charmandar", 6, "Fire", 300, 300);
	Pokemon* pobject5 = new Pokemon("Caterpie", 2, "Bug", 300, 300);
	Pokemon* pobject6 = new Pokemon("Rattata", 3, "Normal", 300, 300);
	Pokemon* pobject7 = new Pokemon("MissingNo", 0, "God", 300, 300);


	test2.add(pobject1);
	test2.add(pobject2);
	test2.add(pobject3);
	test2.add(pobject4);
	test2.add(pobject5);
	test2.add(pobject6);
	test2.add(pobject7);
	test2.hashDisplayAll();

	int index = test2.search(pobject2);
	cout << "index: " << index << endl;

	index = test2.search(pobject3);
	cout << "index: " << index << endl;

	test2.LinkedListDisplay(1);
	cout << endl;

	test2.hashDisplayAll();
	cout << endl;

	test2.removebyIndex(2);
	test2.hashDisplayAll();
	cout << endl;

	test2.removebyData(pobject2);
	test2.hashDisplayAll();
	cout << endl;

	test2.removebyData(pobject2);
	test2.hashDisplayAll();
	cout << endl;

	cout << "Press <Enter>";
	cin.get(endProgram);
	return 0;
}
#endif // !_SOURCE_CPP
