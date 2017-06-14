#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <fstream>
#include "Pokemon.h"

/*
Hashtable

This is status report #2. I'd say im about 80% complete with the hash table.
First, talk about Pokemon.h
Cliff, I had to comment out the >> with unique_pointer because that was the source of the hashtable/pokemon.h error. I'll discuss tomorrow
about it. I also uncommented the << operator that used Pokemon obj because i was testing with poke obj.

Second, explaining y 80%
Reason is: Everything is working fluidly with POKEMON objects. Collision is in, rehashing (apparently an extra i didnt
have to do) is in, and yea.
Last update (later this week) will modify my code so it works with POKEMON NODE/Pointers/the thing we agreed on.

Main Functions:
Constructor - complete
Destructor - complete
Add - Tested with pokemon. Will modify for pointer
Remove (by index and by data) - Both tested with pokemon class. Will modify/test for pokemon pointer next.
Search - Tested with pokemon class. Will modify/test for pokemon pointer.
Hash (Key function) - tested with pokemon class. Will modify/test for pokemon pointer soon.
Rehash - Tested with pokemon class. Will modify/test for pokemon pointer soon
Collision (handle collision) - Tested with pokemon class. Will modify/test for pokemon pointer soon.
Getters and Setters - complete.
*/
class HashTable
{
private:
	Pokemon* pArray;
	int arrayLength;
	int itemCount = 0;

	int hash(Pokemon data) // Temporary hash/key function
	{
		return (((data.getSerialNumber() * data.getSerialNumber()) + 1) % arrayLength);
	}
	int collisionResolution(int &hashIndex)
	{
		for (int i = hashIndex + 1; i < arrayLength; i++)
		{
			if (pArray[i] == 999)
			{
				hashIndex = i;
				return hashIndex;
			}
		}
		for (int j = 0; j < hashIndex; j++)
		{
			if (pArray[j] == 999)
			{
				hashIndex = j;
				return hashIndex;
			}
		}
		return hashIndex;
	}
	int collisionSearch(int &index, Pokemon data)
	{
		for (int i = index + 1; i < arrayLength; i++)
		{
			if (pArray[i] == data)
			{
				index = i;
				return index;
			}
		}
		for (int j = 0; j < index; j++)
		{
			if (pArray[j] == data)
			{
				index = j;
				return index;
			}
		}
		index = -1;
		return index;
	}

public:
	//Constructor
	HashTable(int l)
	{
		arrayLength = (l + 1); // Hopefully Less collisions when size increased by 1.
		pArray = new Pokemon[arrayLength]; //Dynamically allocated array
	}

	//Destructor
	~HashTable()
	{
		std::cout << "Deleting hashTable" << std::endl;
		delete[] pArray; // delete the dynamic array
		pArray = nullptr;
	}

	void hashDisplay(int index)
	{
		std::cout << pArray[index] << std::endl;
	}

	void hashDisplayAll()
	{
		for (int i = 0; i < arrayLength; i++)
			hashDisplay(i);
	}
	void add(Pokemon data)
	{
		int hashIndex; //basically holds index after hash function
		hashIndex = hash(data); // Call hash function (see hash)
		if (pArray[hashIndex] == 999)
			pArray[hashIndex] = data; // insert data to appropriate location.
		else
		{
			collisionResolution(hashIndex);
			pArray[hashIndex] = data;
		}
		itemCount++;
		if (((double)itemCount / (double)arrayLength) >= 0.75)
			rehash();
	}

	bool removebyData(Pokemon data) //Searches for data. If found, remove. Else, nothing.
	{
		bool isRemoved = false;
		int index = hash(data);
		Pokemon temp;
		if (pArray[index] == data)
			pArray[index] = temp;
		else
		{
			collisionSearch(index, data);
			pArray[index] = temp;
		}
		itemCount--;
		isRemoved = true;
		return isRemoved;
	}

	void removebyIndex(int index) //Remove by index. 
	{
		Pokemon temp;
		pArray[index] = temp;
		itemCount--;
	}

	int search(Pokemon data) // Finds data. if found, returns index. if not, index is -1.
	{
		int index = hash(data);
		if (pArray[index] == data)
			{
				return index;
			}
		else
		{
			collisionSearch(index, data);
		}
		return index;
	}

	void rehash()
	{
		int OrigLength = arrayLength; // 6
		Pokemon* pArray2 = new Pokemon[OrigLength]; //6
		for (int i = 0; i < OrigLength; i++)
		{
			pArray2[i] = pArray[i];
		}
		delete[] pArray;
		itemCount = 0;
		pArray = nullptr;
		arrayLength = (arrayLength * 2) + 1; // 13
		pArray = new Pokemon[arrayLength]; //13
		for (int i = 0; i < OrigLength; i++)
		{
			if (pArray2[i] != 999)
			{
				add(pArray2[i]);
			}
		}
		delete[] pArray2;
		/*
		Check if it worked. (It did)
		for (int i = 0; i < arrayLength; i++)
		{
			std::cout << pArray[i] << std::endl;
		}
		*/
	}

	// Getters
	Pokemon* getPArray() const{ return pArray; }
	int getLength() const{ return arrayLength; }
	int getItemCount() const{ return itemCount; }

	// Setters
	void setPArray(Pokemon* pArr){ pArray = pArr; }
	void setLength(int l){ arrayLength = l; }
	void setCount(int c){ itemCount = c; }
};
#endif // !_HASHTABLE_H
