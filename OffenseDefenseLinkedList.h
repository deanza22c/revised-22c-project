// A linked list that sorts the data by offense or defense number
// Performs all the basics of a linked list

#ifndef OFFENSEDEFENSELINKEDLIST_H
#define OFFENSEDEFENSELINKEDLIST_H
#include <iostream>
#include"Pokemon.h"


//*********************************************
// The ListNode class creates a type used to *
// store a node of the linked list. *
//*********************************************

//template <class T>
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
	friend class OffenseDefenseList;
};

//*********************************************
// OffenseDefenseList class *
//*********************************************

//template <class T>
class OffenseDefenseList
{
private:
	OffenseDefenseNode* head;  // pointer to the first node
	int listCount = 0;   // another way of tracking the list's size
	bool sortedByOffenseNumber;

protected:
	OffenseDefenseNode *push_front(Pokemon* newValue)
	{
		// creates a new node, sets nodes value as the sent value
		// sets new node as the first item in the list, and updates head and next node pointers

		// insert a node at the front of the list
		OffenseDefenseNode *newNode; // To point to a new node

		// Allocate a new node and store newValue there.
		newNode = new OffenseDefenseNode(newValue);

		// point newNode->next to the old first node and make newNode the first node in the list
		newNode->next = head;
		head = newNode;

		// update the list size
		listCount++;
		return newNode;
	}

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
	~OffenseDefenseList();

	// Linked list operations

	////**************************************************
	//// appendNode appends a node containing the value *
	//// passed into newValue, to the end of the list. *
	////**************************************************
	//void appendNode(Pokemon* newValue)
	//{
	//	OffenseDefenseNode *newNode; // To point to a new node
	//	OffenseDefenseNode *nodePtr; // To move through the list

	//	// Allocate a new node and store newValue there.
	//	newNode = new OffenseDefenseNode(newValue);

	//	// If there are no nodes in the list
	//	// make newNode the first node.
	//	if (!head)
	//		head = newNode;
	//	else // Otherwise, insert newNode at end.
	//	{
	//		// Initialize nodePtr to head of list.
	//		nodePtr = head;

	//		// Find the last node in the list.
	//		while (nodePtr->next)
	//			nodePtr = nodePtr->next;

	//		// Insert newNode as the last node.
	//		nodePtr->next = newNode;
	//	}

	//	// update the list size
	//	listCount++;
	//}

	void emptyTheList()
	{
		int size = this->getListSize();
		for (int count = 0; count < size; count++)
		{
			this->deleteNode(head->pokemonCreature);
		}
	}


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
		}
		else // Otherwise, insert newNode.
		{
			// Position nodePtr at the head of list.
			nodePtr = head;

			if (sortedByOffenseNumber)
			{
				// Skip all nodes whose offense is less than the new node
				while (nodePtr != nullptr && nodePtr->pokemonCreature->getOffenseStat() < newValue->getOffenseStat())
				{
					previousNode = nodePtr;
					nodePtr = nodePtr->next;
				}

				// If the new node is to be the 1st in the list,
				// insert it before all other nodes.
				if (previousNode == nullptr)
				{
					newNode->next = head;
					head = newNode;
					//newNode->next = nodePtr;
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
	void deleteNode(Pokemon* searchValue)
	{
		OffenseDefenseNode* nodePtr; // To traverse the list
		OffenseDefenseNode* previousNode = nullptr; // To point to the previous node

		// If the list is empty, do nothing and exit the function
		if (head == nullptr)
			return;

		// if the list is sorted by the offense
		if (sortedByOffenseNumber)
		{
			// Determine if the first node is the one.
			if (head->pokemonCreature->getSerialNumber() == searchValue->getSerialNumber())
			{
				nodePtr = head->next;
				delete head;
				head = nodePtr;
			}
			else
			{
				// Initialize nodePtr to head of list
				nodePtr = head;

				// Skip all nodes whose value member is not equal to searchValue.
				while (nodePtr != nullptr && nodePtr->pokemonCreature->getSerialNumber() != searchValue->getSerialNumber())
				{
					previousNode = nodePtr;
					nodePtr = nodePtr->next;
				}

				// If nodePtr is not at the end of the list,
				// link the previous node to the node after
				// nodePtr, then delete nodePtr.
				if (nodePtr->next != nullptr)
				{
					previousNode->next = nodePtr->next;
					delete nodePtr;
				}
				// if the last item in the list is the desired value, set previousNode-> to null and delete nodePtr
				else if (nodePtr->pokemonCreature->getSerialNumber() == searchValue->getSerialNumber() && nodePtr->next == nullptr)
				{
					previousNode->next = nullptr;
					delete nodePtr;
				}
			}
		}

		// else the list is sorted by the defense number
		else
		{
			// Determine if the first node is the one.
			if (head->pokemonCreature->getSerialNumber() == searchValue->getSerialNumber())
			{
				nodePtr = head->next;
				delete head;
				head = nodePtr;
			}
			else
			{
				// Initialize nodePtr to head of list
				nodePtr = head;

				// Skip all nodes whose value member is not equal to searchValue.
				while (nodePtr != nullptr && nodePtr->pokemonCreature->getSerialNumber() != searchValue->getSerialNumber())
				{
					previousNode = nodePtr;
					nodePtr = nodePtr->next;
				}

				// If nodePtr is not at the end of the list,
				// link the previous node to the node after
				// nodePtr, then delete nodePtr.
				if (nodePtr->next != nullptr)
				{
					previousNode->next = nodePtr->next;
					delete nodePtr;
				}
				// if the last item in the list is the desired value, set previousNode-> to null and delete nodePtr
				else if (nodePtr->pokemonCreature->getSerialNumber() == searchValue->getSerialNumber() && nodePtr->next == nullptr)
				{
					previousNode->next = nullptr;
					delete nodePtr;
				}
			}
		}

		// update the list size
		listCount--;
	}


	void displayList() const;

	//void insertNodeAtIndex(Pokemon* newValue, int location)
	//{
	//	//  insert node at any location by sending the location as an argument, along with the value to insert also
	//	//  using this method will NOT SORT THE DATA

	//	// check location for value errors.  If location is less than 1, set it to 1, and if location is greater than
	//	// the size of the list, set location to size + 1
	//	if (location < 1)
	//	{
	//		location = 1;
	//	}
	//	else if (location >(listCount + 1))
	//	{
	//		location = (listCount + 1);
	//	}

	//	OffenseDefenseNode *newNode; // To point to a new node
	//	OffenseDefenseNode *traversingPtr; // To move through the list
	//	OffenseDefenseNode *previousNode;

	//	// Allocate a new node and store newValue there.
	//	newNode = new OffenseDefenseNode(newValue);

	//	// If there are no nodes in the list make newNode the first node.
	//	//  if head does not exist, head will now point to the memory address of newNode
	//	if (!head)
	//		head = newNode;

	//	else // Otherwise, insert newNode at the desired location.
	//	{
	//		// Initialize nodePtr to head of list.
	//		traversingPtr = head;
	//		previousNode = nullptr;


	//		if (location == 1)  // if the location is 1, make newNode the first node in the list, and point newNode->next to the next node
	//		{
	//			head = newNode;
	//			newNode->next = traversingPtr;
	//		}

	//		else
	//		{

	//			for (int count = 0; count < (location - 1); count++) // keep pushing nodePtr until it gets the to location
	//			{

	//				previousNode = traversingPtr;
	//				traversingPtr = traversingPtr->next;
	//			}

	//			previousNode->next = newNode;
	//			newNode->next = traversingPtr;
	//		}
	//	}
	//	// update list count 
	//	listCount++;
	//}

	int searchNodes(Pokemon* searchValue)
	{
		// search the nodes for the value sent
		// if the value is found, return the position and maybe cout the value
		// if the value was not found, return -1, simalar to a binary search

		int listLocation = 0;
		OffenseDefenseNode *nodePtr; // To traverse the list

		// If the list is empty, return -1
		if (!head)
			return -1;

		// if the first node is the value, return its index, 1
		//if (sortedByOffenseNumber)
		//{
		if (head->pokemonCreature->getOffenseStat() == searchValue->getOffenseStat())
		{
			return 1;
		}
		else
		{
			// Initialize nodePtr to head of list and increment the location counter
			nodePtr = head;
			listLocation++;

			// Skip all nodes whose value member is not equal to searchValue.
			while (nodePtr != nullptr && nodePtr->pokemonCreature->getOffenseStat() != searchValue->getOffenseStat())
			{
				nodePtr = nodePtr->next;
				listLocation++;
			}

			//  if the value was not found, and the list is at the end, return -1
			if (nodePtr == nullptr)
			{
				return -1;
			}

			// else, return the index of where the value was found
			else
			{
				return listLocation;
			}
		}
		//}
		//else
		//{
		//
		//}
	}

	int getListSize()
	{
		// return the number of items in the list
		return listCount;
	}

};


//***************************************************
// displayList shows the value stored in each node *
// of the linked list pointed to by head. *
//***************************************************

void OffenseDefenseList::displayList() const
{
	OffenseDefenseNode *nodePtr; // To move through the list

	// Position nodePtr at the head of the list.
	nodePtr = head;

	// While nodePtr points to a node, traverse
	// the list.
	while (nodePtr)
	{
		if (sortedByOffenseNumber)
		{
			// display the name and numbers of this pokemon
			std::cout << nodePtr->pokemonCreature->getPokemonName() << " " << nodePtr->pokemonCreature->getOffenseStat() << std::endl;
		}
		else
		{
			// display the name and defense numbers of this pokemon
			std::cout << nodePtr->pokemonCreature->getPokemonName() << " " << nodePtr->pokemonCreature->getDefenseStat() << std::endl;
		}

		// Move to the next node.
		nodePtr = nodePtr->next;
	}
}

//**************************************************
// Destructor *
// This function deletes every node in the list. *
//**************************************************
//

OffenseDefenseList::~OffenseDefenseList()
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
#endif
