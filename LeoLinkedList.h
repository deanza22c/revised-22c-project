/*
This file contains:
Linked List
Stack
Queue
BST
*/

#ifndef _LINKED_LIST
#define _LINKED_LIST

#include "LeoNode.h"
#include <fstream>

template <class T>
class LinkedList
{
private:
	Node<T>* headPtr;
	int itemCount;
	Node<T>* rearPtr;
public:
	//Constructor
	LinkedList()
	{
		headPtr = nullptr;
		rearPtr = nullptr;
		itemCount = 0;
	}

	//Destructor
	virtual ~LinkedList()
	{
		cout << "Calling the clear function" << endl;
		clear();
		cout << "Destroying the link-list" << endl;
	}

	/*This function returns the size of a link-list
	Pre:
	Post:
	Return: size of the link-list
	*/
	int getCurrentSize() const
	{
		return itemCount;
	}

	/*This function checks to see if a link list is empty (has 0 nodes)
	Pre:
	Post:
	Return: true or false
	*/
	bool isEmpty() const
	{
		return (headPtr == nullptr);
	}

	/*This function adds a defined node into a link-list.
	Pre: index - an integer value
		 newNode - a pointer to a node 
	Post: If the operation is successful, newNode is added to the link list at position index.
	Return: True or false
	*/
	bool addAnywhere(int index, Node<T>* newNode)
	{
		bool isSuccess = false;
		if (index >= 0 && index <= itemCount)
		{
			Node<T> *curPtr = headPtr;
			Node<T> *prevPtr = nullptr;
			int i = 0;
			while (i < index)
				{
					prevPtr = curPtr;
					curPtr = curPtr->getPtrFront();
					i++;
				}
			newNode->setPtrFront(curPtr);
			if (prevPtr == nullptr)
				headPtr = newNode;
			else
			prevPtr->setPtrFront(newNode);
			itemCount++;
			isSuccess = true;
			return isSuccess;
		}
		else
			return isSuccess;
	}

	/*This function removes a node from a link-list
	Pre: index - an integer value
	Post: if the operation is successful, then the node at position index is removed from the link list.
	Return: true or false
	*/
	bool removeAnywhere(int index)
	{
		bool isSuccess = false;
		if (index >= 0 && index < itemCount)
		{
			Node<T> *curPtr = headPtr;
			Node<T> *prevPtr = nullptr;
			int i = 0;
			while (i < index)
				{
					prevPtr = curPtr;
					curPtr = curPtr->getPtrFront();
					i++;
				}
			if (prevPtr == nullptr)
				headPtr = curPtr->getPtrFront();
			else
				prevPtr->setPtrFront(curPtr->getPtrFront());
			curPtr->setPtrFront(nullptr);
			delete curPtr;
			curPtr = nullptr;
			itemCount--;
			isSuccess = true;
			return isSuccess;
		}
		else
			return isSuccess;
	}

	/*This function searches for a specific piece of data in a link-list
	Pre: searchEntry - a variable holding a value depending on the data type
	Post:
	Return: index (an integer), -1, or -2
	*/
	int searchAnywhere(T searchEntry)
	{
		if (itemCount > 0)
		{
			int index = 0;
			Node<T> *curPtr = headPtr;
			while (curPtr->getData() != searchEntry && curPtr->getPtrFront() != nullptr)
			{
				curPtr = curPtr->getPtrFront();
				index++;
			}
			if (curPtr->getData() == searchEntry)
				return index; // Data found
			else
				return -1; // Data not found
		}
		else
			return -2; // Link List doesn't have any nodes.
	}

	/*This function returns a pointer to a node in the link-list.
	Pre: index - an integer value
	Post:
	Return: curPtr - pointer to a node
	*/
	Node<T>* obtainDataAnywhere(int index)
	{
		Node<T> *curPtr = headPtr;
		if (itemCount > 0 && index < itemCount)
		{
			int i = 0;
			while (i < index)
			{
				curPtr = curPtr->getPtrFront();
				i++;
			}
			return curPtr;
		}
		else
			return nullptr;
	}

	/*This function removes all nodes in a link-list
	Pre:
	Post: If the operation is successful, all nodes in a link list are destroyed and the itemCount is set to 0.
	Return:
	*/
	void clear()
	{
		while (headPtr != nullptr)
		{
			Node<T>* deletePtr = headPtr;
			headPtr = headPtr->getPtrFront();
			deletePtr->setPtrFront(nullptr);
			delete deletePtr;
			deletePtr = nullptr;
		}
		itemCount = 0;
	}

	//Setters
	void setCount(int c)
	{
		itemCount = 0;
	}
	void setHeadPtr(Node<T>* ptr)
	{
		headPtr = ptr;
		itemCount++;
	}
	void setRearPtr(Node<T>* rPtr)
	{
		rearPtr = rPtr;
	}

	//Getters
	int getCount()
	{
		return itemCount;
	}
	Node<T>* getHeadPtr()
	{
		return headPtr;
	}
	Node<T>* getRearPtr()
	{
		return rearPtr;
	}
};

template <class T>
class Stack : protected LinkedList<T>
{
public:
	Stack() : LinkedList<T>(){}
	~Stack()
	{
		cout << "Now Destroying Stack Class." << endl;
	}

	/*This function returns the size of a stack
	Pre:
	Post:
	Return: itemCount - an integer
	*/
	int stackSize()
	{
		return getCurrentSize();
	}

	/*This function inserts a node into the top of the stack
	Pre: newNode - a pointer to a node 
	Post: If the operation is successful, then newNode is added to the top of the stack.
	Return: true or false
	*/
	bool push(Node<T>* newNode)
	{
		return addAnywhere(0, newNode);
	}

	/*This function removes a node from the top of the stack
	Pre:
	Post: If the operation is successful, then the node at the top of the stack is removed.
	Return: true or false
	*/
	bool pop()
	{
		return removeAnywhere(0);
	}

	/* This functions checks if a stack is empty
	Pre:
	Post:
	Return: true or false
	*/
	bool isStackEmpty()
	{
		return isEmpty();
	}

	/*This function returns a pointer to the first pointer in the stack
	Pre:
	Post:
	Return: a pointer to a node
	*/
	Node<T>* peek()
	{
		return obtainDataAnywhere(0);
	}
};

template <class T>
class Queue : protected LinkedList<T>
{
public:
	Queue() : LinkedList<T>(){}
	virtual ~Queue()
	{
		cout << "Now destorying the Queue object" << endl;
		setRearPtr(nullptr);
	}

	/*
	This function returns the size of a queue
	Pre:
	Post:
	Return: itemCount - an integer
	*/
	int queueSize()
	{
		return getCurrentSize();
	}

	/*This function inserts a node at the end of the queue
	Pre: newNode - a pointer to a node
	Post: If the operation is successful, then newNode is added to the end of the queue and
		  rearPtr points to newNode.
	Return: true or false
	*/
	bool enqueue(Node<T>* newNode)
	{
		setRearPtr(newNode);
		return addAnywhere(getCount(), newNode);
	}

	/*
	This function removes a node from the front of the queue
	Pre:
	Post: If the operation is successful, then the node at the front of the queue is removed.
	Return: true or false
	*/
	bool dequeue()
	{
		return removeAnywhere(0);
	}

	/* 
	This functions checks if a queue is empty
	Pre:
	Post:
	Return: true or false
	*/
	bool isQueueEmpty()
	{
		return isEmpty();
	}

	/*
	This function returns a pointer to the first node in the queue
	Pre:
	Post:
	Return: a pointer to a node
	*/
	Node<T>* peekFront()
	{
		return obtainDataAnywhere(0);
	}
	
	/*
	This function returns a pointer to the last node in the queue
	Pre:
	Post:
	Return: a pointer to a node
	*/
	Node<T>* peekRear()
	{
		return obtainDataAnywhere((getCount() - 1));
	}


};

template <class T>
class BinarySearchTree : protected LinkedList<T>
{
private:
	/*This function inserts a node into the BST if the BST is not empty
	Pre: rt - a node pointer that points to the root of the BST
		 newEntry - the data that is to be added to the BST
	Post: If the operation is successful, then a node with newEntry value is added as a leaf.
	Return: true or false
	*/
	bool add(Node<T>* rt, T newEntry)
	{
		bool isSuccessful = false;
		if (newEntry <= rt->getData())
		{
			if (rt->getPtrRear() != nullptr)
				add(rt->getPtrRear(), newEntry);
			else
			{
				Node<T>* pNode = new Node<T>(newEntry);
				rt->setPtrRear(pNode);
				isSuccessful = true;
			}
		}
		else
		{
			if (rt->getPtrFront() != nullptr)
				add(rt->getPtrFront(), newEntry);
			else
			{
				Node<T>* pNode = new Node<T>(newEntry);
				rt->setPtrFront(pNode);
				isSuccessful = true;
			}
		}
		return isSuccessful;
	}
	/*This function recursively prints out the value of a node in the BST and stores it into a file.
	Pre: rt - a node pointer that points to the root of the BST
	level - an integer value indicating the current level of the node in the BST
	Post: 
	Return:
	*/
	void printGivenLevel(Node<T>* rt, int level, std::ofstream &file)
	{
		if (rt == nullptr)
			return;
		if (level == 1)
		{
			cout << rt->getData() << endl;
			file << rt->getData() << endl;
		}
		else if (level > 1)
		{
			printGivenLevel(rt->getPtrRear(), level - 1, file);
			printGivenLevel(rt->getPtrFront(), level - 1, file);
		}
	}
	/*This function returns the height of the BST
	Pre: rt - a node pointer that points to the root of the BST
	Post: 
	Return: the height as an int.
	*/
	int height(Node<T>* rt)
	{
		if (rt == nullptr)
			return 0;
		else
		{
			/* compute the height of each subtree */
			int lheight = height(rt->getPtrRear());
			int rheight = height(rt->getPtrFront());

			/* use the larger one */
			if (lheight > rheight)
				return(lheight + 1);
			else
				return(rheight + 1);
		}
	}

public:
	//Constructor and Destructor
	BinarySearchTree() : LinkedList<T>(){}
	~BinarySearchTree()
	{
		std::cout << "Now deleting BST" << std::endl;
		BSTClear(getRoot());
		setHeadPtr(nullptr);
		std::cout << "Finished deleting BST" << std::endl;
	}

	/*This function checks to see if the BST is empty (has 0 nodes)
	Pre:
	Post:
	Return: true or false
	*/
	bool isBSTEmpty()
	{
		return isEmpty();
	}

	/*This function inserts a node into the BST if it is empty. If not, it calls overloaded add function.
	Pre: newEntry - the data that is to be added to the BST
	Post: If the operation is successful, then a node with newEntry value is added as the root. Else, refer to add(1 parameter) in private
	Return: true or false
	*/
	bool add(T newEntry)
	{
		bool isSuccessful = false;
		if (getRoot() == nullptr)
		{
			Node<T>* pNode = new Node<T>(newEntry);
			setRoot(pNode);
			isSuccessful = true;
			return isSuccessful;
		}
		else
			return add(getRoot(), newEntry);
	}
	/* This function takes in a data and searches to find if that data exists in the BST
	Pre: root - a node pointer to the root of the BST
		 entry - the data you are searching for
	Post:
	Return: True or False;
	*/
	bool search(Node<T>* root, T entry)
	{
		isFound = false;
		if (root == nullptr)
			return isFound;
		else
		{
			if (root->getData() == entry)
				isFound = true;
			if (entry < root->getData() && root->getPtrRear() == nullptr)
				return isFound;
			if (entry < root->getData() && root->getPtrRear() != nullptr)
				search(root->getPtrRear(), entry);
			if (entry > root->getData() && root->getPtrFront() == nullptr)
				return isFound;
			if (entry > root->getData() && root->getPtrFront() != nullptr)
				search(root->getPtrFront(), entry);
		}
		return isFound;
	}
	/*This function removes all nodes in a BST
	Pre: root - a node pointer pointing to the root of the BST.
	Post: If the operation is successful, all nodes in a BST are destroyed.
	Return:
	*/
	void BSTClear(Node<T>* root)
	{
		if (root != nullptr)
		{
			BSTClear(root->getPtrRear());
			BSTClear(root->getPtrFront());
			delete root;
		}
	}

	//Searches
	/*This function prints out the data stored in the nodes using inOrder traversal
	Pre: rt - a node pointing to the root of the BST
	Post:
	Return:
	*/
	void inOrder(Node<T>* rt)
	{
		if (rt != nullptr)
		{
			inOrder(rt->getPtrRear());
			std::cout << rt->getData() << std::endl;
			inOrder(rt->getPtrFront());
		}
	}
	/*This function prints out the data stored in the nodes using preOrder traversal
	Pre: rt - a node pointing to the root of the BST
	Post:
	Return:
	*/
	void preOrder(Node<T>* rt)
	{
		if (rt != nullptr)
		{
			std::cout << rt->getData() << std::endl;
			preOrder(rt->getPtrRear());
			preOrder(rt->getPtrFront());
		}
	}
	/*This function prints out the data stored in the nodes using postOrder traversal
	Pre: rt - a node pointing to the root of the BST
	Post:
	Return:
	*/
	void postOrder(Node<T>* rt, std::ofstream &file)
	{
		if (rt != nullptr)
		{
			postOrder(rt->getPtrRear(), file);
			postOrder(rt->getPtrFront(), file);
			std::cout << rt->getData() << std::endl;
			file << rt->getData() << std::endl;
		}
	}
	/*This function prints out the data stored in the nodes using breadth traversal
	Pre: rt - a node pointing to the root of the BST
	Post:
	Return:
	*/
	void breadthTraversal(Node<T>* rt, std::ofstream &file)
	{
		int h = height(rt);
		for (int i = 1; i <= h; i++)
			printGivenLevel(rt, i, file);
	}

	//Getters
	Node<T>* getRoot()
	{
		return getHeadPtr();
	}
	//Setters
	void setRoot(Node<T>* node)
	{
		setHeadPtr(node);
	}
};


#endif // !_LINKED_LIST
