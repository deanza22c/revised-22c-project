#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <fstream>
#include "Pokemon.h"

/*
Hashtable

This is status report #3. I'd say im about 95% complete with the hash table.

Explaining y 95%
Reason is: Everything is working fluidly with POKEMON POINTERS now. I mean EVERYTHING.
The only thing I havn't done yet is make a Linked-List collision solution (currently linear probing).
I also have to update my remove/search to compare Number, Name, and Type instead of just Number. (lazy right now).
I'm going to be busy Thursday and Friday, so I thought "Why not put this up now so that everyone knows I'm up to date".
Yea, once I finish all the work i have to do, Ill make a Linked List collision solution and documentation. That will
make it 100% done for me.
End of the quarter assignments are time consuming, so mb. If you need the hash table for who knows what, this file is working.

The last update should come Saturday (LinkedList collision + documentation).

Main Functions:
Constructor - complete
Destructor - complete
Add - complete with linear probing collision
Remove (by index and by data) - complete with linear probing search
Search - complete with linear probing search
Hash (Key function) - complete
Rehash - Complete.
Collision (handle collision) - Linear probing complete. No LinkedList yet.
Getters and Setters - complete.
*/
class HashTable
{
private:
	Pokemon** pArray;
	int arrayLength;
	int itemCount = 0;

	//FIXED!
	int hash(Pokemon* data) // Temporary hash/key function
	{
		return (((data->getSerialNumber() * data->getSerialNumber()) + 1) % arrayLength);
	}

	//FIXED!
	int collisionResolution(int &hashIndex)
	{
		for (int i = hashIndex + 1; i < arrayLength; i++)
		{
			if (pArray[i] == nullptr)
			{
				hashIndex = i;
				return hashIndex;
			}
		}
		for (int j = 0; j < hashIndex; j++)
		{
			if (pArray[j] == nullptr)
			{
				hashIndex = j;
				return hashIndex;
			}
		}
		hashIndex = -1;
		return hashIndex;
	} 

	//FIXED
	int collisionSearch(int &index, Pokemon* data)
	{
		for (int i = index + 1; i < arrayLength; i++)
		{
			if (pArray[i] != nullptr)
			{
				if (pArray[i]->getSerialNumber() == data->getSerialNumber())
				{
					index = i;
					return index;
				}
			}
		}
		for (int j = 0; j < index; j++)
		{
			if (pArray[j] != nullptr)
			{
				if (pArray[j]->getSerialNumber() == data->getSerialNumber())
				{
					index = j;
					return index;
				}
			}
		}
		index = -1;
		return index;
	}

public:
	//Constructor, FIXED!
	HashTable(int l)
	{
		arrayLength = (l + 1); // Hopefully Less collisions when size increased by 1.
		pArray = new Pokemon*[arrayLength];
		for (int i = 0; i < arrayLength; i++)
		{
			pArray[i] = nullptr;
		}
	}

	//Destructor, FIXED!
	~HashTable()
	{
		std::cout << "Deleting hashTable" << std::endl;
		delete[] pArray; // delete the dynamic array
		pArray = nullptr;
	}

	//FIXED
	void hashDisplay(int index)
	{
		if (pArray[index] != nullptr)
		std::cout << pArray[index] << std::endl;
	}

	//FIXED
	void hashDisplayAll()
	{
		//skip 999
		for (int i = 0; i < arrayLength; i++)
		{
				hashDisplay(i);
		}
	}

	//FIXED
	void add(Pokemon* data) //Fixed Add!
	{
		int hashIndex; //basically holds index after hash function
		hashIndex = hash(data); // Call hash function (see hash)
		if (pArray[hashIndex] == nullptr)
			pArray[hashIndex] = data; // insert data to appropriate location.
		else
		{
			collisionResolution(hashIndex); // Fixed Collision!
			pArray[hashIndex] = data;
		}
		itemCount++;
		if (((double)itemCount / (double)arrayLength) >= 0.75)
			rehash(); //Need to Fix!
	}

	//FIXED
	bool removebyData(Pokemon* data) //Searches for data. If found, remove. Else, nothing.
	{
		bool isRemoved = false;
		int index = hash(data);
		if (pArray[index] != nullptr)
		{
			if (pArray[index]->getSerialNumber() == data->getSerialNumber())
			{
				delete pArray[index];
				pArray[index] = nullptr;
			}
			else
			{
				collisionSearch(index, data);
				delete pArray[index];
				pArray[index] = nullptr;
			}
		}
		else
			{
				collisionSearch(index, data);
				delete pArray[index];
				pArray[index] = nullptr;
			}
		itemCount--;
		isRemoved = true;
		return isRemoved;
	}

	//FIXED
	void removebyIndex(int index) //Remove by index. 
	{
		if (pArray[index] != nullptr)
		{
			delete pArray[index];
			pArray[index] = nullptr;
			itemCount--;
		}
	}

	//FIXED
	int search(Pokemon* data) // Finds data. if found, returns index. if not, index is -1.
	{
		int index = hash(data);
		if (pArray[index] != nullptr)
		{
			if (pArray[index]->getSerialNumber() == data->getSerialNumber())
			{
				return index;
			}
			else
			{
				collisionSearch(index, data);
				return index;
			}
		}
		index = -1;
		return index;
	}

	//FIXED
	void rehash()
	{
		int OrigLength = arrayLength; // 6
		Pokemon** pArray2 = new Pokemon*[OrigLength]; //6
		for (int i = 0; i < OrigLength; i++)
		{
			pArray2[i] = pArray[i];
			pArray[i] = nullptr;
		}
		delete[] pArray;
		itemCount = 0;
		pArray = nullptr;
		arrayLength = (arrayLength * 2) + 1; // 13
		pArray = new Pokemon*[arrayLength]; //13
		for (int k = 0; k < arrayLength; k++)
		{
			pArray[k] = nullptr;
		}
		for (int i = 0; i < OrigLength; i++)
		{
			if (pArray2[i] != nullptr)
			{
				pArray[i] = pArray2[i];
				pArray2[i] = nullptr;
			}
		}
		delete[] pArray2;
		pArray2 = nullptr;
		/*
		Check if it worked. (It did)
		for (int i = 0; i < arrayLength; i++)
		{
			std::cout << pArray[i] << std::endl;
		}
		*/
	}

	// Getters
	Pokemon** getPArray() const{ return pArray; }
	int getLength() const{ return arrayLength; }
	int getItemCount() const{ return itemCount; }

	// Setters
	void setPArray(Pokemon** pArr){ pArray = pArr; }
	void setLength(int l){ arrayLength = l; }
	void setCount(int c){ itemCount = c; }
};
#endif // !_HASHTABLE_H
