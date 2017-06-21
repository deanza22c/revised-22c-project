/*
This program reads in data to create pokemon class objects, which the pointers are stored in linked lists
binary search tree, and a hashed table

The main functions of the program are to read in new data, remove data, display sorted data and calculate effeincy

The option part of the programs emulates the functions of a pokedex scanner and shows two pictures to demostrate that effect
*/

#include<iostream>
#include<string>
#include<fstream>
#include<Windows.h>
#include"Globals.h"
#include"Scanner.h"
#include"Pokemon.h"
#include"BinarySearchTree.h"
#include"HashTable.h"
#include"OffenseDefenseLinkedList.h"

using namespace std;
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


	BinarySearchTree<Pokemon*> pokemonBST;  // Binary Search Tree structure
	HashTable pokemonHashedTable(ARRAY_SIZE);  // Hased Table structure
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
		cout << "1: add new Pokemon (add data)\n";
		cout << "2: remove Pokemon (remove data)\n";
		cout << "3: search and display a Pokemon\n";
		cout << "4: list data in the hash table\n";
		cout << "5: list data with sorting (key attribute, secondary attribute, tertiary attribute)\n";
		cout << "6: print indented binary search tree\n";
		cout << "7: display effiency numbers\n";
		cout << "8: scan for pokemon (team choice option)\n";
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
			cout << "enter in pokemon's pokedex number, the number must be a whole number greater than zero\n";
			cout << "enter the number: ";
			creatureIndexNumber = getIntegerInput();

			// if the number is less than 1, re-prompt for input
			while (creatureIndexNumber < 1)
			{
				cout << "the pokedex number must be greater than zero, enter in a new number: ";
				creatureIndexNumber = getIntegerInput();
			}

			cout << "enter in pokemon's elements: ";
			getline(cin, elements);
			cout << "enter in pokemon's offense (only whole numbers are valid) number: ";
			offense = getIntegerInput();
			cout << "enter in pokemon's defense (only whole numbers are valid) number: ";
			defense = getIntegerInput();
			cout << "\npress <Enter> to return to main menu...";
			cin.get();

			// now create a new pokemon instance and update the data structures
			Pokemon *addThisPokemon = nullptr;
			addThisPokemon = new Pokemon(name, creatureIndexNumber, elements, offense, defense);
			pokemonOffenseLinkedList.insertNode(addThisPokemon);
			pokemonDefenseLinkedList.insertNode(addThisPokemon);
			pokemonBST.addValue(addThisPokemon);
			pokemonHashedTable.add(addThisPokemon);
			totalDataItems++;  // increment the data counter

			if (!fileIsOpen) // check to see if the file is all ready open
			{

				writeToDataRecordsFile.open("PokeStats.txt", ios::app | ios::ate);
				fileIsOpen = true;
			}

			// write the new item to PokeStats.txt file
			writeToDataRecordsFile << endl << creatureIndexNumber << "|" << name << "|" << elements << "|" << offense << "|" << defense;
			break;
		}  // end of add new data option

		case 2:
		{
			// call to remove data function
			// prompt the user for the pokedex number of the creature to remove
			// after the number is validated, remove the item from the data structures

			system("cls");
			cout << "this is the remove data choice\n";
			cout << "enter the pokedex number of the pokemon you wish to remove: ";
			int removeNumber = getIntegerInput();

			// delete the item from the linked lists
			pokemonOffenseLinkedList.deleteThisSerialNumber(removeNumber); // remove the item from the offense linked list
			pokemonDefenseLinkedList.deleteThisSerialNumber(removeNumber); // remove the item from the defense linked list

			tempPokemon = new Pokemon();
			tempPokemon->setSerialNumber(removeNumber);

			// delete the item from the binary search tree and hashed table
			bool status = pokemonBST.deleteValue(tempPokemon); // remove the item from the binary search tree
			bool status2 = pokemonHashedTable.removebyData(tempPokemon); // remove the item from the hashed table

			// print out the results of the search
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
			delete tempPokemon;
			break;
		}  // end of remove data option

		case 3:
		{
			// call to find and display data function
			// this function will use the binary search tree to find and display the creature based on the number entered

			system("cls");
			cout << "\nenter in pokemon's pokedex number to search for, the number must be a whole number greater than zero.\n";
			cout << "enter the number: ";
			creatureIndexNumber = getIntegerInput();

			Pokemon *displayThisPokemon = nullptr;


			// send the number to the BST search function and print out the results of the search
			status = pokemonBST.searchForValue(creatureIndexNumber, displayThisPokemon);

			if (status)
			{
				cout << "pokedex number: " << creatureIndexNumber << " has been found\n";
				cout << endl;
				cout << "displaying the information of the pokemon:\n";
				cout << "------------------------------------------\n";
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
			cout << "this is the list of data stored in the hash table array:\n\n";
			pokemonHashedTable.hashDisplayAll();
			cout << "\npress <Enter> to return to main menu...";
			cin.get();
			break;
		}
		case 5:
		{
			// call to list data in key sequence (sorted)
			// list all data using the creature number as the sort method

			// display list using serial key as the sort method
			system("cls");
			cout << "this is the list data sorted by the key attribute using inorder traverse\n";
			cout << "------------------------\n";
			pokemonBST.printBreadthFirstTraverse();
			cout << endl;
			cout << "press <Enter> to sort by offense stat...";
			cin.get();

			// display list using offense number as the sort method
			system("cls");
			cout << "this is the list data sorted by the offense number\n";
			cout << endl;
			pokemonOffenseLinkedList.displayList();
			cout << endl;
			cout << "press <Enter> to sort by defense stat...";
			cin.get();

			// display list using defense numbers as the sort method
			system("cls");
			cout << "this is the list data sorted by the defense number\n";
			cout << endl;
			pokemonDefenseLinkedList.displayList();
			cout << endl;
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
			int linkedListEffiency = linkedListEffiencyCounter / (totalDataItems * 2);
			system("cls");
			cout << "this is the effiency of the three data structures:\n";
			cout << "--------------------------------------------------\n\n";
			cout << "Hashed Table fill rate is: " << hashedTableFillRate << "% with " << hashedTableCollisionCounter << " collision(s)\n";
			cout << "Binary Search Tree performed " << bstEffiencyCounter << " operations to insert " << totalDataItems << " items, " << bstInsertEffiency << " per item average.\n";
			cout << "Linked List performed " << static_cast<int>((linkedListEffiencyCounter / 2)) << " operations to insert " << totalDataItems << " items, " << linkedListEffiency << " per item average.\n";
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
} // end of main()