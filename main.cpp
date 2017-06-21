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
#include"OffenseDefenseLinkedList.h"

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
	// before any choices are give, load the data file and build the hash table, binary search tree, and linked list
	ifstream dataRecordsFile;
	dataRecordsFile.open("PokeStats.txt");
	ofstream writeToDataRecordsFile; // in case add data is called, now the data can be written to the PokeStats.txt file


	BinarySearchTree<Pokemon*> pokemonBST;
	HashTable pokemonHashedTable(ARRAY_SIZE);
	OffenseDefenseList pokemonOffenseLinkedList(1);  // linked list sorting the pokemon by offense number
	OffenseDefenseList pokemonDefenseLinkedList(0);  // linked list sorting the pokemon by defense number

	Pokemon *tempPokemon = nullptr;

	// build the data structures
	while (!dataRecordsFile.eof())
	{
		tempPokemon = getDataMemoryAddress(dataRecordsFile);
		pokemonBST.addValue(tempPokemon);
		pokemonHashedTable.add(tempPokemon);
		pokemonOffenseLinkedList.insertNode(tempPokemon);
		pokemonDefenseLinkedList.insertNode(tempPokemon);
		totalDataItems++;
	}

	dataRecordsFile.close(); // close the file


	int creatureIndexNumber;
	string name;
	string elements;
	int offense;
	int defense;
	bool status;
	bool fileIsOpen = false;

	int choice = 0;
	while (choice != 9)
	{
		// display the menu options and prompt the user for input
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
			// add a new pokemon entry to the binary search tree, hashed table, and linked lists

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
			pokemonOffenseLinkedList.insertNode(addThisPokemon);
			pokemonDefenseLinkedList.insertNode(addThisPokemon);
			pokemonBST.addValue(addThisPokemon);
			pokemonHashedTable.add(addThisPokemon);
			totalDataItems++;
			if (!fileIsOpen)
			{
				// check to see if the file is all ready open
				writeToDataRecordsFile.open("PokeStats.txt", ios::app | ios::ate);
				fileIsOpen = true;
			}
			writeToDataRecordsFile << endl << creatureIndexNumber << "|" << name << "|" << elements << "|" << offense << "|" << defense;
			break;
		}
		case 2:
		{
			// call to remove data function
			// both the hash table and binary search tree need remove functions
			// use this case to call those remove functions

			system("cls");
			cout << "this is the remove data choice\n";
			cout << "enter the pokedex number of the pokemon you wish to remove: ";
			int removeNumber = getIntegerInput();

			pokemonOffenseLinkedList.deleteThisSerialNumber(removeNumber);
			pokemonDefenseLinkedList.deleteThisSerialNumber(removeNumber);
			// create a new pokemon instance and set its serial number with the input value
			//Pokemon *removeThisPokemon = nullptr;
			//removeThisPokemon = new Pokemon();
			tempPokemon->setSerialNumber(removeNumber);

			// delete the item from the data structures
			bool status = pokemonBST.deleteValue(tempPokemon); // remove the item from the binary search tree
			bool status2 = pokemonHashedTable.removebyData(tempPokemon); // remove the item from the hashed table



			if (!status && !status2)
			{
				cout << "pokemon NOT found\n";
			}
			else
			{
				cout << "pokemon number: " << removeNumber << " has been removed from the database\n";
			}

			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			//delete removeThisPokemon;
			break;
		}
		case 3:
		{
			// call to find and display data function
			// this function will use the binary search tree to find and display the creature based on the number entered

			system("cls");
			cout << "\n  enter in creature number to search for: ";
			creatureIndexNumber = getIntegerInput();

			Pokemon *displayThisPokemon = nullptr;


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
			// list all the data stored in the hashed table based array

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
			system("cls");
			pokemonOffenseLinkedList.displayList();
			cin.get();
			system("cls");
			pokemonDefenseLinkedList.displayList();
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
			cout << "Binary Search Tree performed " << bstEffiencyCounter << " operations to insert " << totalDataItems << " items, " << bstInsertEffiency << " per item average.\n";
			cout << "Linked List performed " << linkedListEffiencyCounter << " operations to insert " << pokemonHashedTable.getLinkedListCount() << " items, " << linkedListEffiency << " per item average.\n";
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