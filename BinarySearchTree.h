/*
TEMPLATE CLASS - NODE CLASS - PUBLIC
    PROPERTIES
        T data
        DualLinkDataNode<T> *leftBranch
        DualLinkDataNode<T> *rightBranch
    FUNCTIONS
        DualLinkDataNode()                  | DEFAULT CONSTUCTOR
        DualLinkDataNode(T value)         | TAKES A VALUE ASSIGNS TO DATA
TEMPLATE CLASS - BINARY SEARCH TREE - PRIVATE
    - DualLinkDataNode<T> *rootNode        
TEMPLATE CLASS - BINARY SEARCH TREE - PUBLIC FUNCTIONS
    - void addValue(T value)
        |
        | CALLES THE PROTECTED RECURSIVE FUNCTION ADDINORDER();
        | TRACKS THE BST EFFICIENCY, EFFIENCY GROWS EVERY AFTER EVERY EVALUATION TO FIND AN APPROPRIATE LEAF NODE TO MAKE AN INSERTION
        |
    -bool deleteValue(T value)
        |
        | GIVEN A VALUE OF TYPE T THIS FUNCTION FINDS THE VALUE THEN CALLS REMOVENODE()
        | CALLS PROTECTED: REMOVEVALUE()
        |  - REMOVEVALUE FIND THE NODE IN THE BST THEN CALLES REMOVENODE() WHICH REMOVES NODE
        |  - IF THE NODE HAS 2 CHILDREN FINDLEFTMOSTNODE() IS CALLED TO PRESERVE BST UPON DELETION
         |
    bool searchForValue(T value)
        |
        | CHECKS IF THE TREE HAS VALUE, 
        | CALLS PROTECTED: SEARCHTREE()
        |
    bool searchForValue(const int &pokedexNumber, T &displayPtr)
        |
        | FUNCTIONS CREATED FOR POKEMON PROJECT WHICH TAKES AN INTEGER, INSTEAD OF TYPE T
        | FUNCTION DEPENDS ON TYPE TO HANDING OPERATIONS WHICH RETURN PRIMARY DATA TYPES, FROM POINTER PROPERTY
        | CALLS PROTECTED: SEARCHTREE()
        |
    void searchAndModify(T findThis)
        |
        | TWO STEP FUNCTION, 1ST SEARCH TREE FOR VALUE, WILL COUT TO TERMINAL IF NOT FOUND
        | 2ND, IF FOUND CALLS CIN TO READ IN NEW VALUE.
        |
    IN ORDER TRAVERSAL - void printBreadthFirstTraverse() - WARNING - 
        |
        | WARNING - THIS FUNCTION WILL PRINT INORDER TRAVERSAL!! NOT BREADTH FIRST
        | CALLS THE RECURSIVE FUNCTION     coutBreadth_firstTraversal()
        |
    int findDepth()
        |
        | RETURNS THE DEPTH OF THE BST
        | CALLS THE PROTECTED RECURSIVE FUNCTION FINDDEPTH()
        | FUNCTION TAKES NOT ARGUMENT IN ORDER TO BE CALLED ANYWHERE A BST OBJECT IS CREATED
        |
    int getHeight(DualLinkDataNode<T>*find)
        |
        | RETURNS THE DEPTH OF THE BST
        |
    void printIndented2(DualLinkDataNode<T>* start, int tabs)
        |
        | PRINTS THE INDENTED TREE
        | MUST HAVE ACCESS TO THE ROOT NODE
        | CALLED BY void callPrintIndentedTree()
        | CALLS GETHEIGHT()
        |
    void callPrintIndentedTree()
        |
        | CALL TO PRINT THE INDENTED TREE
        | CALLS PRINT INDENTED TRUE
        |
*/


#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include<fstream>
#include<iostream>
//#include"QueueADT.h"
#include"Pokemon.h"

template <class T>
class DualLinkDataNode
{
public:
    T data;
    DualLinkDataNode<T> *leftBranch;
    DualLinkDataNode<T> *rightBranch;

    // defualt constructor
    DualLinkDataNode()
    {
        leftBranch = nullptr;
        rightBranch = nullptr;
    }

    // constructor
    DualLinkDataNode(T value)
    {
        data = value;
        leftBranch = nullptr;
        rightBranch = nullptr;
    }
};

template <class T>
class BinarySearchTree
{
private:
    DualLinkDataNode<T> *rootNode;

protected:
    //  add nodes to the tree using a binary search traversal, and is called by addNode() function
    //  this function is access protected from anything outside the class for safety
    DualLinkDataNode<T> *addInOrder(DualLinkDataNode<T> *currentSubTree, DualLinkDataNode<T> *newNode)
    {
        // if the current sub-tree is empty, return the address of the new node
        if (currentSubTree == nullptr)
        {
            return newNode;
            bstEffiencyCounter++;
        }

        else
        {
            // if the sub-tree's data is greater than or equal to new node's data, send new node down the left branch
            if (*currentSubTree->data >= *newNode->data)
            {
                currentSubTree->leftBranch = addInOrder(currentSubTree->leftBranch, newNode);
                bstEffiencyCounter++;
            }

            else
            {
                currentSubTree->rightBranch = addInOrder(currentSubTree->rightBranch, newNode);
                bstEffiencyCounter++;
            }

            return currentSubTree;
        }
    }

    //  This is protected function that will remove the value from the tree.
    //  First it will search the tree for the value, then if the value is found, it will call removeNode() function
    //  Remove node function will delete the node and balance the tree as required
    DualLinkDataNode<T> *removeValue(DualLinkDataNode<T> *subTreePtr, const T findThis, bool &successBoolean)
    {
        DualLinkDataNode<T> *tempPtr = nullptr;
        // if the value was not found, terminate the removeValue() recursion, and return a false for success
        if (subTreePtr == nullptr)
        {
            successBoolean = false;
            return nullptr;
        }

        // if the value was found, send this node's address to removeNode() function and set success to true
        else if (*subTreePtr->data == *findThis)
        {
            subTreePtr = removeNode(subTreePtr);
            successBoolean = true;
            return subTreePtr;
        }
        // check the left branch for the value
        else if (*subTreePtr->data > *findThis)
        {
            tempPtr = removeValue(subTreePtr->leftBranch, findThis, successBoolean);
            subTreePtr->leftBranch = tempPtr;
            return subTreePtr;
        }
        // check the right branch for the value
        else
        {
            tempPtr = removeValue(subTreePtr->rightBranch, findThis, successBoolean);
            subTreePtr->rightBranch = tempPtr;
            return subTreePtr;
        }
    }

    //  This function is valled by removeValue() function and is only called if the value was found
    //  The function will use recursion to balance the tree by calling the removeLeftNode function
    DualLinkDataNode<T> *removeNode(DualLinkDataNode<T> *currentNode)
    {
        DualLinkDataNode<T> * tempPtr = nullptr;

        // if the sub-tree has no left or right branches, delete the node and return a nullptr
        if (currentNode->leftBranch == nullptr && currentNode->rightBranch == nullptr)
        {
            delete currentNode;
            currentNode = nullptr;
            return nullptr;
        }

        // if the sub-tree has only one branch
        else if ((currentNode->leftBranch != nullptr && currentNode->rightBranch == nullptr) || (currentNode->rightBranch != nullptr && currentNode->leftBranch == nullptr))
        {
            // store currnetNode's address in tempPtr
            tempPtr = currentNode;

            //  if the sub-tree's path is only on the left branch, make subTreePtr point to the left branch
            if (currentNode->leftBranch != nullptr && currentNode->rightBranch == nullptr)
            {
                currentNode = currentNode->leftBranch;
                delete tempPtr;
                tempPtr = nullptr;
                return currentNode;
            }

            //  else, the path is only the right branch
            else
            {
                currentNode = currentNode->rightBranch;
                delete tempPtr;
                tempPtr = nullptr;
                return currentNode;
            }
        }

        // else, the sub-tree has two branches
        else
        {
            // Find the inorder successor of the entry in N: it is in the left subtree rooted at N’s right child
            tempPtr = removeLeftMostNode(currentNode->rightBranch, currentNode->data);  // data is referenced in removeleftnode function
            currentNode->rightBranch = tempPtr;
            currentNode->data = currentNode->data;  // because the data was referenced, it was changed
            return currentNode;
        }
    }

    //  Travel down the left branch looking for the end of the path and get last nodes value
    DualLinkDataNode<T> *removeLeftMostNode(DualLinkDataNode<T> *nodePtr, T &inorderSuccesssor)
    {

        if (nodePtr->leftBranch == nullptr)
        {
            // This is the node you want; it has no left child, but it might have a right subtree
            inorderSuccesssor = nodePtr->data;
            return removeNode(nodePtr);
        }

        else
        {
            return removeLeftMostNode(nodePtr->leftBranch, inorderSuccesssor);
        }

    }

    //  Search the tree for the given value using recursion.  If the value is found update the boolean to true
    //  Else set the passed boolean to false
    DualLinkDataNode<T> *searchTree(const T &findThis, DualLinkDataNode<T> *root, bool &successBoolean)
    {
        // if the value was not found, return false
        if (root == nullptr)
        {
            successBoolean = false;
            return nullptr;
        }
        // if the value is found, return true and unwind the recursion
        else if (*root->data == *findThis)
        {
            successBoolean = true;
            return root;
        }
        // if the search value is less than or equal to the data stored in the node, use recursion to travel down the left branch
        else if (findThis <= root->data)
        {
            //return searchTree(value, root->leftBranch);
            return searchTree(findThis, root->leftBranch, successBoolean);
        }
        // else travel down the right branch
        else
        {
            //return searchTree(findThis, root->rightBranch);
            return searchTree(findThis, root->rightBranch, successBoolean);
        }
    }


    // takes an int instead of a type T argument, and performs the same functions as the searchTree() funtion
    DualLinkDataNode<T> *searchTree(const int &findThis, DualLinkDataNode<T> *root, bool &successBoolean, T &displayPtr)
    {
        // if the value was not found, return false
        if (root == nullptr)
        {
            successBoolean = false;
            return nullptr;
        }
        // if the value is found, return true and unwind the recursion
        else if (*root->data == findThis)
        {
            successBoolean = true;
            displayPtr = root->data;
            return root;
        }
        // if the search value is less than or equal to the data stored in the node, use recursion to travel down the left branch
        else if (*root->data > findThis)
        {
            return searchTree(findThis, root->leftBranch, successBoolean, displayPtr);
        }
        // else travel down the right branch
        else
        {
            return searchTree(findThis, root->rightBranch, successBoolean, displayPtr);
        }
    }




    //  Use a recursion to travel down the left branches until a dead end is found
    //  Then travel down the right branch until a dead is found
    //  Once both paths are checked, print out the data in the node at the end of the branch
    //  Also this function is protected from access outside of the class
    void post_orderTraversal(DualLinkDataNode<T> *currentRoot, std::ofstream &writeFile)
    {
        // if the currentRoot is null, that means this branch's patch is at the end
        if (currentRoot == nullptr)
        {
            return;
        }
        else
        {
            post_orderTraversal(currentRoot->leftBranch, writeFile); // check the left branch for a valid path
            post_orderTraversal(currentRoot->rightBranch, writeFile); // check the right branch for a valid path
            writeFile << currentRoot->data << std::endl; // when both branches are nullptr's, print out the current node's data
        }
    }

    //this is the recursive function called when calculating the depth of tree
    int findDepth(DualLinkDataNode<T> *currentRoot, int level)
    {
        // if the currentRoot is null, that means this branch's patch is at the end
        int templevel1;
        int templevel2;
        if (currentRoot == nullptr) return level;
        level++;
        templevel1 = findDepth(currentRoot->leftBranch, level); // check the left branch for a valid path
        templevel2 = findDepth(currentRoot->rightBranch, level); // check the right branch for a valid path
        if (templevel1 > templevel2)
            templevel2 = templevel1;
        level = templevel2;
        return level;
    }

    //  Use a post order traverse to get to the bottom of the tree,
    //  then delete the node and use recursion to work back up the tree
    //  the function is protected from anything outside of the class
    void destroyTree(DualLinkDataNode<T> *currentRoot)
    {
        // if the currentRoot is null, that means this branch's patch is at the end
        if (currentRoot == nullptr)
        {
            return;
        }
        else
        {
            destroyTree(currentRoot->leftBranch); // check the left branch for a valid path
            destroyTree(currentRoot->rightBranch); // check the right branch for a valid path
            delete currentRoot; // when both branches are nullptr's, delete the node
        }
    }

public:
    //------------------------------------------------------------
    // Constructors and Destructors:
    //------------------------------------------------------------

    BinarySearchTree()
    {
        rootNode = nullptr;
    }

    ~BinarySearchTree()
    {
        // call the destroy tree function to remove all the nodes in the tree
        destroyTree(rootNode);
    }

    //------------------------------------------------------------
    // Public Methods:
    //------------------------------------------------------------

    //  Use recursion to travel down the tree until the proper location is found to add the new node
    void addValue(T value)
    {
        DualLinkDataNode<T> *newNode = new DualLinkDataNode<T>(value);

        //  if the tree has no items, set the new node as the root node
        if (!rootNode)
        {
            rootNode = newNode;
            bstEffiencyCounter++;
        }

        //  else, process the node using a binary search to find the correct location for the value
        else
        {
            rootNode = addInOrder(rootNode, newNode);
        }
    }

    //  the public remove node function
    //  removes the node holding the passed value, if the node is in the tree
    //  returns true if the node was removed, or returns false
    bool deleteValue(T value)
    {
        bool status;  // store the result of the remove node recursion

                      //  if the tree has no items, print out the error message
        if (!rootNode)
        {
            std::cout << "error: the tree has no items";
            return false;
        }

        // else, call the protected removeValue() function
        else
        {
            removeValue(rootNode, value, status);
        }
        return status;
    }

    //  The public function to search for a value
    //  This function checks to see if the tree has items, then sends the search value to the function searchTree()
    bool searchForValue(T value)
    {
        bool status;

        if (!rootNode)
        {
            return false;
        }
        else if (rootNode->data == value)
        {
            return true;
        }
        // if the search value is less than or equal to the data in rootNode, travel down the left branch
        else if (value <= rootNode->data)
        {
            //return searchTree(value, rootNode->leftBranch);
            searchTree(value, rootNode->leftBranch, status);

        }
        // else, travel down the right branch
        else
        {
            //return searchTree(value, rootNode->rightBranch);
            searchTree(value, rootNode->rightBranch, status);
        }
        return status;
    }

    //this function is used specifically for the 22c group project
    //takes an integer for the primary property and says if it is in the BST
    //this functions relies heavily on the overloaded operators in type T's definition
    bool searchForValue(const int &pokedexNumber, T &displayPtr)
    {
        bool status;

        if (!rootNode)
        {
            return false;
        }
        else if (*rootNode->data == pokedexNumber)
        {
            displayPtr = rootNode->data;
            return true;
        }
        // if the search value is less than or equal to the data in rootNode, travel down the left branch
        else if (*rootNode->data > pokedexNumber)
        {
            //return searchTree(value, rootNode->leftBranch);
            searchTree(pokedexNumber, rootNode->leftBranch, status, displayPtr);

        }
        // else, travel down the right branch
        else
        {
            //return searchTree(value, rootNode->rightBranch);
            searchTree(pokedexNumber, rootNode->rightBranch, status, displayPtr);
        }
        return status;
    }


    //  The public function to modify a value in the tree
    //  this is a two step process, the first step is search for the value
    //  if the value is found, delete the node
    //  next step is to insert a new node with a new value into the tree
    //  thus preserving the tree balance
    void searchAndModify(T findThis)
    {
        T newValue;
        bool status;
        DualLinkDataNode<T> *nodeWithSeachValue = nullptr;

        // search for a value, and if found, modify the node's data member
        if (!rootNode)
        {
            std::cout << "error: tree is empty";
            return;
        }
        else
        {
            status = deleteValue(findThis);
        }
        if (status == true)
        {
            std::cout << "current value: " << findThis << std::endl;
            std::cout << "enter a new value: ";
            getline(std::cin, newValue);
            addValue(newValue);
        }
        else
        {
            std::cout << "value: " << findThis << " was not found";
        }
    }


    //WARNING, THIS IS NOT A BREADTH FIRST TRAVERSAL - THIS IS AN INORDER TRAVERSAL
    //  FUNCTION CALLS THE THE
    void printBreadthFirstTraverse()
    {
        if (rootNode == nullptr)
        {
            return;
        }

        else
        {
            coutBreadth_firstTraversal(rootNode);
        }
    }

    //WARNING, THIS IS NOT A BREADTH FIRST TRAVERSAL - THIS IS AN INORDER TRAVERSAL
    //  breadth - first traversal mechanism - PRINTS TO TERMINAL
    void coutBreadth_firstTraversal(DualLinkDataNode<T> *nodePtr) const
    {
        if (nodePtr != nullptr)
        {
            coutBreadth_firstTraversal(nodePtr->leftBranch);
            cout << nodePtr->data << endl;
            coutBreadth_firstTraversal(nodePtr->rightBranch);

        }
    }

    //  uses post order traveresal to process the items in the tree, then writes the data to the &writeFile
    void printPostOrderTraverse(std::ofstream &writeFile)
    {
        if (!rootNode)
        {
            std::cout << "error: tree is empty";
        }
        else
        {
            //post_orderTraversal(rootNode, writeFile);
        }
    }

    //public function which can be called in main to return an integer containing the depth
    int findDepth()
    {
        int level = 0;
        if (!rootNode)
        {
            return level;
        }
        else
        {
            findDepth(rootNode, level);
        }
    }
    /*
	*******************************************************************************************************
											printIndented2
		Takes in a beginning node position and a default number of tabs to print per the depth of each node
		The character value is used to determine the direction of the node with respect to the parent
		The function prints out the data in a post order fashion so the rightmost value is printed first
		It recurses on itself so it can access the members in a specific order
	*******************************************************************************************************
	*/
	void printIndented(DualLinkDataNode<T>* start, int tabs,char c)
	{
		//Validate that the current node is not a null ptr
		if (start != nullptr)
		{
			//Recurse till we reach the rightmost non null node and change character to r so the arrows point in the right direction
			printIndented(start->rightBranch, tabs + 1,'r');
			//Print out tabs and Line breaks to signify the depth of each node
			for (int x = 0; x < tabs; x++)
			{
				std::cout << "|\t\t";
			}
			//Depending on whether it is a right or left child print the specific arrow
			if (c == 'l')
			{
				std::cout << "^---";
			}
			else if (c == 'r')
			{
				std::cout << "v---";
			}
			//Print out the data in the current node
			std::cout << start->data << std::endl;
			//Use Lines to show seperation of levels
			std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
			//Recurse to get through the left branch
			printIndented(start->leftBranch, tabs + 1,'l');
		}
	}
	/*
	*******************************************************************************************************
								callPrintIndentedTree()
		The function makes the initial call to the printIndented function with acceptable parameters
		It then provides labeling that can be used to identify the depth of particular nodes in the tree
	*******************************************************************************************************
	*/
	void callPrintIndentedTree()
	{
		//Call printIndented with the rootNode and a neutral character to prevent printing of arrows
		printIndented(rootNode, 0,'n');
		//Print initial label for root
		cout << "|Root\t\t";
		//Iterate based on the depth of the tree to print labels for each level
		for (int x = 1; x < findDepth(); x++)
		{
			//The last item printed out will always be a leaf so it prints out leaf to distinguish it from other branches
			if (x ==findDepth() - 1)
			{
				std::cout << "|Leaf" << "\t";
			}
			else
			{
				std::cout << "|Branch " << x << "\t";
			}
		}
	}

};

#endif
