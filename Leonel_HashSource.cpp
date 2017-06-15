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
	Pokemon* pobject2 = new Pokemon("Magikar", 5, "Water", 300, 300);
	Pokemon* pobject3 = new Pokemon("Magika", 5, "Water", 300, 300);
	Pokemon* pobject4 = new Pokemon("Magik", 5, "Water", 300, 300);
	Pokemon* pobject5 = new Pokemon("Magi", 5, "Water", 300, 300);
	Pokemon* pobject6 = new Pokemon("Mag", 5, "Water", 300, 300);
	Pokemon* pobject7 = new Pokemon("Ma", 5, "Water", 300, 300);


	test2.add(pobject1);
	test2.add(pobject2);
	test2.add(pobject3);
	test2.add(pobject4);
	test2.hashDisplayAll();
	test2.add(pobject5);
	test2.add(pobject6);
	test2.add(pobject7);

	int index = test2.search(pobject2);
	cout << index << endl << endl;

	index = test2.search(pobject3);
	cout << index << endl << endl;

	test2.removebyIndex(2);
	test2.hashDisplay(2);

	test2.removebyData(pobject2);
	test2.hashDisplay(2);

	test2.hashDisplayAll();
	cout << "Press <Enter>";
	cin.get(endProgram);
	return 0;
}
#endif // !_SOURCE_CPP
