#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <string>
#include <fstream>
#include "Pokemon.h"
#include "LinkedList.h"

class HashTable
{
private:
	Pokemon** pokemonPtrArray;
	int arrayLength;
	int itemCount;
	int linkedListItemCount; // track the number of items in the linked list
	const int reHashFillPercent = 80;  // if the fill rate is greater than this percent, rehash the array
	LinkedList<Pokemon*> linkedListOverflow;

	/*This function follows a mathematical algorithm that takes the paramater's primary data and returns an index.
	Pre: Data - a pokemon pointer
	Post:
	Return: an integer
	*/
	int hash(Pokemon* data)
	{
		return ((data->getSerialNumber() * data->getSerialNumber() + 1) * data->getSerialNumber()) % arrayLength;
	}

	/*This function takes a pokemon pointer and then adds it into a link-list.
	Pre: data - a pokemon pointer.
	Post: If successful, data is added to the linkedList.
	Return:
	*/
	void collisionLinkList(Pokemon* data)
	{
		Node<Pokemon*>* temp = new Node<Pokemon*>(data);
		linkedListOverflow.addAnywhere(0, temp);
		linkedListItemCount++;
	}

	/*This function takes a pokemon pointer and searches through the link-list for it.
	Pre: data - a pokemon pointer
	Post:
	Return: an integer that represents an index.
	*/
	int collisionLLSearch(Pokemon* data)
	{
		return linkedListOverflow.searchAnywhere(data);
	}

	/*This function adjusts the link-list when a search is called so that the searched item is placed in the front of the list.
	Pre: index - an integer
	data - a pokemon pointer.
	Post: data is moved from its original position into position 0 of the link list.
	Return:
	*/
	void selfAdjustSearch(int index, Pokemon* data)
	{
		Node<Pokemon*>* temp = new Node<Pokemon*>(data);
		linkedListOverflow.removeAnywhere(index);
		linkedListOverflow.addAnywhere(0, temp);
	}

public:
	//Constructor
	HashTable(int l)
	{
		linkedListItemCount = 0;
		itemCount = 0;
		arrayLength = (l + 1); // Hopefully Less collisions when size increased by 1.
		pokemonPtrArray = new Pokemon*[arrayLength];
		for (int i = 0; i < arrayLength; i++)
		{
			pokemonPtrArray[i] = nullptr;
		}
	}

	//Destructor
	~HashTable()
	{
		// delete the pokemon instance's that are on the heap
		for (int count = 0; count < arrayLength; count++)
		{
			if (pokemonPtrArray[count] != nullptr)
			{
				delete (pokemonPtrArray[count]);
			}
			else
			{
				continue;
			}
		}
		delete[] pokemonPtrArray; // delete the dynamic array
		pokemonPtrArray = nullptr;
	}

	/*This function displays the content stored in an index in the hashtable.
	Pre: index - an integer.
	Post:
	Return:
	*/
	void hashDisplay(int index)
	{
		if (pokemonPtrArray[index] != nullptr)
			std::cout << "[" << index << "] " << pokemonPtrArray[index]->getPokemonName() << std::endl;
		else
		{
			std::cout << "[" << index << "] <empty>" << std::endl;
		}
	}

	/*This function displays the content stored in an index in the linked list.
	Pre: index - an integer.
	Post:
	Return:
	*/
	void LinkedListDisplay(int index)
	{
		Node<Pokemon*>* temp = linkedListOverflow.obtainDataAnywhere(index);
		if (temp->getData() != nullptr)
			std::cout << *(temp->getData()) << std::endl;
	}

	/*This function displays all content stored in the hashtable and the linked list
	Pre:
	Post:
	Return:
	*/
	void hashDisplayAll()
	{
		for (int i = 0; i < arrayLength; i++)
		{
			hashDisplay(i);
		}
		std::cout << std::endl;
		int linkedSize = linkedListOverflow.getCurrentSize();
		std::cout << "Now displaying everything stored in the self adjusting linked list:" << std::endl;
		for (int j = 0; j < linkedSize; j++)
		{
			LinkedListDisplay(j);
		}

	}

	/*This function adds a pokemon pointer into the hashtable.
	Pre: data - a pokemon pointer
	Post: if successful, data is stored in the appropriate location in the hashtable. 
	If not, it is stored in the linked list in position 0.
	Return:
	*/
	void add(Pokemon* data)
	{
		int hashIndex; //holds index after hash function
		hashIndex = hash(data); // Call hash function (see hash)

		// if the hashIndex number is greater than the size of the array, add the item to the linked list
		if (hashIndex > arrayLength)
		{
			collisionLinkList(data);
		}

		else if (pokemonPtrArray[hashIndex] == nullptr)
		{
			pokemonPtrArray[hashIndex] = data; // insert data to appropriate location.
			itemCount++; //increment counter
		}

		else
		{
			collisionLinkList(data);
		}

		if (((double)itemCount / (double)arrayLength) >= (static_cast<double>(reHashFillPercent / 100.0)))
			rehash();
	}

	/*This function removes the content of an index in the hashtable.
	Pre: data - a pokemon pointer
	Post: If successful, data is removed from the hashtable, or data is removed from the linked list 
	if data is not in hashtable.
	Return: true or false
	*/
	bool removebyData(Pokemon* data)
	{
		bool isRemoved = false;
		int index = hash(data);

		// if the index number is out of bounds, check the linked list
		if (index >= arrayLength)
		{
			index = collisionLLSearch(data);
			isRemoved = linkedListOverflow.removeAnywhere(index);
			if (isRemoved)
			{
				linkedListItemCount--;
			}
			return isRemoved;
		}
		else if (pokemonPtrArray[index] != nullptr)
		{
			if (pokemonPtrArray[index]->getSerialNumber() == data->getSerialNumber())
			{
				delete pokemonPtrArray[index];
				pokemonPtrArray[index] = nullptr;
				itemCount--;
				isRemoved = true;
				return isRemoved;
			}

			else
			{
				index = collisionLLSearch(data);
				isRemoved = linkedListOverflow.removeAnywhere(index);
				if (isRemoved)
				{
					linkedListItemCount--;
				}
				return isRemoved;
			}
		}
		else
		{
			index = collisionLLSearch(data);
			isRemoved = linkedListOverflow.removeAnywhere(index);
			if (isRemoved)
			{
				linkedListItemCount--;
			}
			return isRemoved;
		}

		return isRemoved;
	}
	
	/*This function removes the content stored in an index in the hashtable.
	Pre: index - an integer.
	Post: if successful, removes the data from the hashtable.
	Return:
	*/
	void removebyIndex(int index)
	{
		if (index >= 0 && index < arrayLength && pokemonPtrArray[index] != nullptr)
		{
			delete pokemonPtrArray[index];
			pokemonPtrArray[index] = nullptr;
			itemCount--;
		}
	}

	/*This function searches for data in the hashtable and returns it's index.
	Pre: data - a pokemon pointer.
	Post: If item is in linked-list, item is moved to position 0 of linked-list.
	Return: an integer representing the index.
	*/
	int search(Pokemon* data)
	{
		int index = hash(data);
		if (pokemonPtrArray[index] != nullptr)
		{
			if (pokemonPtrArray[index]->getSerialNumber() == data->getSerialNumber())
			{
				return index;
			}

			else
			{
				std::cout << "Searching LinkList" << std::endl;
				index = collisionLLSearch(data);
				selfAdjustSearch(index, data);
				return index;
			}
		}
		else
		{
			std::cout << "Searching LinkList" << std::endl;
			index = collisionLLSearch(data);
			return index;
		}

		index = -1;
		return index;
	}

	/*This function resizes the hashtable if the fill count is 80%.
	Pre:
	Post: arrayLength is now (twice in size + 1). pArray now points to a larger dynamically created array.
	Return:
	*/
	void rehash()
	{
		int OrigLength = arrayLength;
		Pokemon** pArray2 = new Pokemon*[OrigLength];
		for (int i = 0; i < OrigLength; i++)
		{
			pArray2[i] = pokemonPtrArray[i];
			pokemonPtrArray[i] = nullptr;
		}
		delete[] pokemonPtrArray;
		pokemonPtrArray = nullptr;
		arrayLength = (arrayLength * 2) + 1;
		pokemonPtrArray = new Pokemon*[arrayLength];
		for (int k = 0; k < arrayLength; k++)
		{
			pokemonPtrArray[k] = nullptr;
		}
		for (int i = 0; i < OrigLength; i++)
		{
			if (pArray2[i] != nullptr)
			{
				pokemonPtrArray[i] = pArray2[i];
				pArray2[i] = nullptr;
			}
		}
		delete[] pArray2;
		pArray2 = nullptr;
	}

	// Getters
	Pokemon** getPArray() const
	{
		return pokemonPtrArray;
	}
	int getLength() const
	{
		return arrayLength;
	}
	int getItemCount() const
	{
		return itemCount;
	}
	int getLinkedListCount() const
	{
		return linkedListItemCount;
	}

	// Setters
	void setPArray(Pokemon** pArr)
	{
		pokemonPtrArray = pArr;
	}
	void setLength(int l)
	{
		arrayLength = l;
	}
	void setCount(int c)
	{
		itemCount = c;
	}
};
#endif // !_HASHTABLE_H
