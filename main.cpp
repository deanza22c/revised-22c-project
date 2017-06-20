#include<iostream>
#include<string>
#include<fstream>
//#include<iomanip>
//#include<memory>
#include<Windows.h>
#include"Globals.h"
#include"Scanner.h"
#include"Pokemon.h"
//#include"LinkedList.h"
//#include"LeoLinkedList.h"
#include"BinarySearchTree.h"
#include"HashTable.h"

using namespace std;
//Pokemon *getDataMemoryAddress(ifstream);
int getIntegerInput();

// This is the function that creates the pokemon objects, all other functions only use pointers
// The only exception is the add new pokemon option in the main menu
Pokemon *getDataMemoryAddress(ifstream &file)
{
	Pokemon *newPokemon = nullptr;
	newPokemon = new Pokemon;
	file >> newPokemon;
	return newPokemon;
}


int main()
{

	//// this makes the console window bigger
	//HWND console = GetConsoleWindow();
	//RECT r;
	//GetWindowRect(console, &r); //stores the console's current dimensions
	//MoveWindow(console, r.left, r.top, 1000, 600, TRUE);


	// before any choices are give, load the data file and build the hash table and binary search tree
	// none of this is set in stone, but for now gives us something to work on
	// if you need to work on some file, just tag it with a "-A" or "-L" or "-H" and upload the file
	ifstream dataRecordsFile;
	dataRecordsFile.open("PokeStats.txt");
	ofstream writeToDataRecordsFile; // in case add data is called, now the data can be written to the PokeStats.txt file


	BinarySearchTree<Pokemon*> pokemonBST;
	LinkedList<Pokemon*> pokemonLinkedList;
	//HashTable<Pokemon*> pokemonHashedTable(ARRAY_SIZE);
	HashTable pokemonHashedTable(ARRAY_SIZE);


	Pokemon *tempPokemon = nullptr;
	//for (int count = 0; count < ARRAY_SIZE; count++)
	//{
	//	tempPokemon = getDataMemoryAddress(dataRecordsFile);
	//	//pokemonLinkedList.push_end(tempPokemon);
	//	pokemonBST.addValue(tempPokemon);
	//	pokemonHashedTable.add(tempPokemon);
	//}
	while (!dataRecordsFile.eof())
	{
		tempPokemon = getDataMemoryAddress(dataRecordsFile);
		//pokemonLinkedList.push_end(tempPokemon);
		pokemonBST.addValue(tempPokemon);
		pokemonHashedTable.add(tempPokemon);
		totalDataItems++;
		//Pokemon *newPokemon = nullptr;
		//newPokemon = new Pokemon;
		//dataRecordsFile >> *newPokemon;
		//cout << newPokemon << endl;
		//pokemonBST.addValue(newPokemon);
	}

	dataRecordsFile.close(); // close the file





	//dataRecordsFile.open("PokeStats.txt");
	//Pokemon pokemonArray[ARRAY_SIZE];
	//for (int count = 0; count < ARRAY_SIZE; count++)
	//{
	//	dataRecordsFile >> pokemonArray[count];
	//}

	int creatureIndexNumber;
	string name;
	string elements;
	int offense;
	int defense;
	bool status;

	int choice = 0;
	while (choice != 9)
	{
		system("cls");
		cout << "1: add new Pokemon (data)\n";
		cout << "2: remove Pokemon (data)\n";
		cout << "3: search and display a Pokemon (data)\n";
		cout << "4: list data in the hash table\n";
		cout << "5: list data sorted by the key attribute (inorder traverse)\n";
		cout << "6: print indented binary search tree\n";
		cout << "7: display effiency numbers\n";
		cout << "8: team choice (scanner)\n";
		cout << "9: exit program\n";
		cout << endl;
		cout << "Enter the choice: ";
		choice = getMenuInput(9);

		switch (choice)
		{
		case 1:
		{
			// call to add data function
			// both the hash table and binary search tree need add functions
			// use this case to call those add functions
			// leo and alex will make the add functions in the their class files
			system("cls");
			cout << "this is the add data choice\n";
			cout << "enter in pokemon's name: ";
			getline(cin, name);
			cout << "enter in pokemon's pokedex number: ";
			creatureIndexNumber = getIntegerInput();
			cout << "enter in pokemon's elements: ";
			getline(cin, elements);
			cout << "enter in pokemon's offense stat: ";
			offense = getIntegerInput();
			cout << "enter in pokemon's defense stat: ";
			defense = getIntegerInput();
			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			Pokemon *addThisPokemon = nullptr;
			addThisPokemon = new Pokemon(name, creatureIndexNumber, elements, offense, defense);
			pokemonBST.addValue(addThisPokemon);
			pokemonHashedTable.add(addThisPokemon);
			totalDataItems++;
			writeToDataRecordsFile.open("PokeStats.txt", ios::app | ios::ate);
			writeToDataRecordsFile << endl << creatureIndexNumber << "|" << name << "|" << elements << "|" << offense << "|" << defense;
			break;
		}
		case 2:
		{
			// call to remove data function
			// both the hash table and binary search tree need remove functions
			// use this case to call those remove functions
			// leo and alex will make the remove functions in the their class files
			system("cls");
			cout << "this is the remove data choice\n";
			cout << "enter the pokedex number of the pokemon you wish to remove: ";
			int removeNumber = getIntegerInput();
			Pokemon *removeThisPokemon = nullptr;
			removeThisPokemon = new Pokemon();
			removeThisPokemon->setSerialNumber(removeNumber);
			bool status = pokemonBST.deleteValue(removeThisPokemon);
			bool status2 = pokemonHashedTable.removebyData(removeThisPokemon);
			if (!status && !status2)
			{
				cout << "pokemon NOT found\n";
			}
			else
			{
				cout << "pokemon number: " << removeNumber << " has been removed from the database\n";
			}
			//cout << status << " " << status2 << endl;
			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			delete removeThisPokemon;
			break;
		}
		case 3:
		{
			// call to find and display data function
			// this function will use the binary search tree to find and display the creature based on the number entered

			system("cls");
			//cout << "this is the find and display data choice\n";
			cout << "\n  enter in creature number to search for: ";
			creatureIndexNumber = getIntegerInput();

			//Pokemon *tempPokemon = nullptr;
			Pokemon *displayThisPokemon = nullptr;
			//tempPokemon = new Pokemon;
			//tempPokemon->setSerialNumber(creatureIndexNumber);

			// send the number to the BST search function and print out the results of the search
			status = pokemonBST.searchForValue(creatureIndexNumber, displayThisPokemon);

			if (status)
			{
				cout << "pokedex number: " << creatureIndexNumber << " has been found\n";
				cout << "displaying the information of the pokemon:\n";
				cout << endl;
				cout << setw(30) << left << "pokemon name: " << displayThisPokemon->getPokemonName() << endl;
				cout << setw(30) << left << "pokemon elemental type(s): " << displayThisPokemon->getElementalType() << endl;
				cout << setw(30) << left << "pokemon offense stat: " << displayThisPokemon->getOffenseStat() << endl;
				cout << setw(30) << left << "pokemon defense stat: " << displayThisPokemon->getDefenseStat() << endl;;
			}
			else
			{
				cout << "creature number: " << creatureIndexNumber << " was NOT found\n";
			}
			cout << "\npress <Enter> to return to main menu...";
			cin.get();

			break;
		}
		case 4:
		{
			// call to list data in hash table
			// list all the data stored in the hashed table based on the order in the array
			// leo will write this function
			system("cls");
			cout << "this is the list data in hash table array:\n\n";
			pokemonHashedTable.hashDisplayAll();
			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			break;
		}
		case 5:
		{
			// call to list data in key sequence (sorted)
			// list all data using the creature number as the sort method

			system("cls");
			cout << "this is the list data in key sequence (inorder traverse) choice\n";
			pokemonBST.printBreadthFirstTraverse();
			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			break;
		}
		case 6:
		{
			// call to print indented tree function
			// cout the binary tree horizontally, with the root node on the left side of the screen
			// and the tree expanding out to the right side of the screen

			system("cls");
			cout << "this is the printed indented tree choice\n";
			pokemonBST.callPrintIndentedTree();
			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			break;
		}
		case 7:
		{
			// call to effiency display
			// display the effiency of the hashed table, binary search tree, and linked list

			int hashedTableFillRate = ((static_cast<double>(pokemonHashedTable.getItemCount()) / static_cast<double>(pokemonHashedTable.getLength())) * 100);
			int bstInsertEffiency = bstEffiencyCounter / totalDataItems;
			int linkedListEffiency = linkedListEffiencyCounter / pokemonHashedTable.getLinkedListCount();
			system("cls");
			cout << "this is the effiency of the three data structures:\n\n";
			cout << "Hashed Table fill rate is: " << hashedTableFillRate << "%\n";
			cout << "Binary Search Tree had " << bstEffiencyCounter << " operation(s) to insert " << totalDataItems << " item(s), " << bstInsertEffiency << " per item average.\n";
			cout << "Linked List had " << linkedListEffiencyCounter << " operation(s) to insert " << pokemonHashedTable.getLinkedListCount() << " item(s), " << linkedListEffiency << " per item average.\n";
			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			break;
		}
		case 8:
		{
			// call to scanner function
			// this is our team choice and for now the idea is to display a message that a wild pokemon has appeared
			// display an out line of the creature, flash the words scanning on the the screen
			// then after the 3 seconds display the full picture and some stats about the creature
			// it will only display one creature for now, and in the future it may display a random pokemon
			//cout << "this is the scanner choice\n";
			startScanner();
			break;
		}
		case 9:
		{
			// exit program 
			break;
		}
		default:
		{
			// this is here for safety
			break;
		}

		}
	}

	cout << "\npress <Enter> to exit...";
	cin.get();
	writeToDataRecordsFile.close();
	return 0;
}