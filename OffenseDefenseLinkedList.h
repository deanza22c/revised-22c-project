// A linked list that inserts the data by offense or defense number
// Performs add node, delete node, display items in the list and get list size
// other linked list functions were removed to make the file easier to read

#ifndef OFFENSEDEFENSELINKEDLIST_H
#define OFFENSEDEFENSELINKEDLIST_H
#include <iostream>
#include"Pokemon.h"



//*********************************************
// The node for the Offense Defense Linked List
// contains two pointers, a pokemon class pointer
// and a node class pointer to store the next node's address
//*********************************************

class OffenseDefenseNode
{
private:
	Pokemon* pokemonCreature; // Node value
	OffenseDefenseNode* next; // Pointer to the next node

public:
	// Constructor
	OffenseDefenseNode()
	{
		pokemonCreature = nullptr;
		next = nullptr;
	}

	// Constructor
	OffenseDefenseNode(Pokemon* nodeValue)
	{
		pokemonCreature = nodeValue;
		next = nullptr;
	}

	int getOffenseNumber()
	{
		return pokemonCreature->getOffenseStat();
	}

	int getDefenseNumber()
	{
		return pokemonCreature->getDefenseStat();
	}

	int getSerialNum()
	{
		return pokemonCreature->getSerialNumber();
	}
	friend class OffenseDefenseList;
};




//*********************************************
// OffenseDefenseList class
// A linked list that inserts the data based on the offense or defense number of the pokemon
//*********************************************

class OffenseDefenseList
{
private:
	OffenseDefenseNode* head;  // pointer to the first node
	int listCount = 0;   // another way of tracking the list's size
	bool sortedByOffenseNumber;  // flag for the sort method

public:
	// Constructor
	OffenseDefenseList()
	{
		head = nullptr;
		sortedByOffenseNumber = false;
	}

	// if the constructor is called with <int> 1, sort the data by offense number
	OffenseDefenseList(int sortByOffense)
	{
		head = nullptr;
		if (sortByOffense == 1)
		{
			sortedByOffenseNumber = true;
		}
		else
		{
			sortedByOffenseNumber = false;
		}
	}

	// Destructor
	//**************************************************
	// This function deletes every node in the list. *
	//**************************************************
	~OffenseDefenseList()
	{
		OffenseDefenseNode *traversalNodePtr; // To traverse the list
		OffenseDefenseNode *nextNode; // To point to the next node

		// Position nodePtr at the head of the list.
		traversalNodePtr = head;

		// While nodePtr is not at the end of the list...
		while (traversalNodePtr != nullptr)
		{
			// Save a pointer to the next node.
			nextNode = traversalNodePtr->next;

			// Delete the current node.
			delete traversalNodePtr;

			// Position nodePtr at the next node.
			traversalNodePtr = nextNode;
		}
	}


	// Linked list operations

	//**************************************************
	// insert the pokemon based on the offense or defense value of the pokemon
	//**************************************************
	void insertNode(Pokemon* newValue)
	{
		OffenseDefenseNode *newNode = nullptr; // A new node
		OffenseDefenseNode *nodePtr = nullptr; // To traverse the list
		OffenseDefenseNode *previousNode = nullptr; // The previous node
													// Allocate a new node and store newValue there.
		newNode = new OffenseDefenseNode(newValue);

		// If there are no nodes in the list
		// make newNode the first node.
		if (!head)
		{
			head = newNode;
			newNode->next = nullptr;
			linkedListEffiencyCounter++;
		}
		else // Otherwise, insert newNode.
		{
			// Position nodePtr at the head of list.
			nodePtr = head;

			if (sortedByOffenseNumber == true)
			{
				// Skip all nodes whose offense is less than the new node
				while (nodePtr != nullptr && nodePtr->pokemonCreature->getOffenseStat() < newNode->pokemonCreature->getOffenseStat())
				{
					previousNode = nodePtr;
					nodePtr = nodePtr->next;
					linkedListEffiencyCounter++;
				}

				// If the new node is to be the 1st in the list,
				// insert it before all other nodes.
				if (previousNode == nullptr)
				{
					head = newNode;
					newNode->next = nodePtr;
				}
				else // Otherwise insert after the previous node.
				{
					previousNode->next = newNode;
					newNode->next = nodePtr;
				}
			}

			// else the list is sorted by the defense number
			else
			{
				// Skip all nodes whose offense is less than the new node
				while (nodePtr != nullptr && nodePtr->pokemonCreature->getDefenseStat() < newValue->getDefenseStat())
				{
					previousNode = nodePtr;
					nodePtr = nodePtr->next;
					linkedListEffiencyCounter++;
				}

				// If the new node is to be the 1st in the list,
				// insert it before all other nodes.
				if (previousNode == nullptr)
				{
					head = newNode;
					newNode->next = nodePtr;
				}
				else // Otherwise insert after the previous node.
				{
					previousNode->next = newNode;
					newNode->next = nodePtr;
				}
			}
		}
		// update the list size
		listCount++;
	}


	//******************************************************
	// The deleteNode function searches for a node *
	// with searchValue as its value. The node, if found, *
	// is deleted from the list and from memory. *
	//******************************************************
	void deleteThisSerialNumber(int searchValue)
	{
		OffenseDefenseNode *currentNode = nullptr; // To move through the list
		currentNode = head; // Position nodePtr at the head of the list.


		// If the list is empty, do nothing and exit the function
		if (head == nullptr)
		{
			return;
		}

		else
		{
			OffenseDefenseNode* previousNode = nullptr; // To point to the previous node

			// check if the first node has the desired value
			if (head->pokemonCreature->getSerialNumber() == searchValue)
			{
				if (head->next == nullptr)
				{
					delete currentNode;
					head = nullptr;
				}
				else
				{
					head = head->next;
					delete currentNode;
				}
			}

			// if the first node does not contain the value, search the rest of the list
			else
			{
				// Skip all nodes whose value member is not equal to searchValue.
				while (currentNode->next != nullptr && currentNode->pokemonCreature->getSerialNumber() != searchValue)
				{
					previousNode = currentNode;
					currentNode = currentNode->next;
				}

				// If nodePtr is not at the end of the list, return
				if (currentNode->next == nullptr && currentNode->pokemonCreature->getSerialNumber() != searchValue)
				{
					return;
				}
				else if (currentNode != nullptr && currentNode->pokemonCreature->getSerialNumber() == searchValue)
				{
					previousNode->next = currentNode->next;
					delete currentNode;
				}
			}
			// update the list size
			listCount--;
		}
	}


	//***************************************************
	// displayList shows the value stored in each node *
	// of the linked list pointed to by head. *
	//***************************************************
	void displayList() const
	{
		OffenseDefenseNode *nodePtr; // To move through the list

		// Position nodePtr at the head of the list.
		nodePtr = head;

		// check if the list has items before printing out the top line
		if (head != nullptr)
		{
			if (sortedByOffenseNumber)
			{
				std::cout << std::setw(20) << std::left << "name" << std::setw(15) << "offense #" << std::setw(15) << "defense #" << std::setw(15) << "pokedex #" << std::endl;
				std::cout << "-----------------------------------------------------------" << std::endl;
			}
			else
			{
				std::cout << std::setw(20) << std::left << "name" << std::setw(15) << "defense #" << std::setw(15) << "offense #" << std::setw(15) << "pokedex #" << std::endl;
				std::cout << "-----------------------------------------------------------" << std::endl;
			}
		}

		// loop through the list printing out each item
		while (nodePtr)
		{
			if (sortedByOffenseNumber)
			{
				// display the name and numbers of this pokemon
				std::cout << std::setw(20) << std::left << nodePtr->pokemonCreature->getPokemonName() << std::setw(15) << nodePtr->pokemonCreature->getOffenseStat() << std::setw(15) << nodePtr->pokemonCreature->getDefenseStat() << std::setw(15) << nodePtr->pokemonCreature->getSerialNumber() << std::endl;
			}
			else
			{
				// display the name and defense numbers of this pokemon

				std::cout << std::setw(20) << std::left << nodePtr->pokemonCreature->getPokemonName() << std::setw(15) << nodePtr->pokemonCreature->getDefenseStat() << std::setw(15) << nodePtr->pokemonCreature->getOffenseStat() << std::setw(15) << nodePtr->pokemonCreature->getSerialNumber() << std::endl;
			}

			// Move to the next node.
			nodePtr = nodePtr->next;
		}
	}

	int getListSize()
	{
		// return the number of items in the list
		return listCount;
	}

};


#endif