/*
The Pokemon class is our data class that represents the ingame characteristics of the individual creature
It contains primarily getters and setters but has operator overloads as well to allow for ease of data access, creation and output
*/

#ifndef POKEMON_H
#define POKEMON_H

#include <string>
#include <fstream>

class Pokemon
{
private:
	std::string pokemonName; // Represents the Ingame Name of the Pokemon
	int serialNumber; // Represents the Pokedex entry of the Pokemon
	std::string elementalType; // Holds the elemental typing(s) of the Pokemon
	int offense; // Based on the higher offensive stat of the Pokemon
	int defense; // Based on the defensive stats of the Pokemon

public:
	//Constructors

	/*
	The default constructor sets up default values for the Pokemon Objects so there is no conflict between existing Pokemon
	*/
	Pokemon()
	{
		pokemonName = "unknown name";
		serialNumber = -1;  // -1 because you can not enter anything less than 1 as a valid serial number
		elementalType = "unknown type";
		offense = 0;
		defense = 0;
	}

	/*
	The Secondary contructor sets all the values of the pokemon classes member variables
	*/
	Pokemon(std::string name, int idNumber, std::string emelents, int offenseNumber, int defenseNumber)
	{
		pokemonName = name;
		serialNumber = idNumber;
		elementalType = emelents;
		offense = offenseNumber;
		defense = defenseNumber;
	}

	//getters

	//Returns pokemon's name
	std::string getPokemonName()
	{
		return pokemonName;
	}
	//Returns Pokemon's Dex Number
	int getSerialNumber()
	{
		return serialNumber;
	}
	//Returns Pokemon's Elemental Type
	std::string getElementalType()
	{
		return elementalType;
	}
	//Returns Pokemon's Offense Stat
	int getOffenseStat()
	{
		return offense;
	}
	//Returns Pokemons defense stat
	int getDefenseStat()
	{
		return defense;
	}

	//setters

	//Sets the Pokemon's Name variable
	void setPokemonName(std::string name)
	{
		pokemonName = name;
	}
	//Sets the Pokemon's Dex Number
	void setSerialNumber(int idNumber)
	{
		serialNumber = idNumber;
	}
	//Sets the Pokemon's Elmental Type
	void setElementType(std::string element)
	{
		elementalType = element;
	}
	//Sets the Pokemon's Offense stat
	void setOffenseStat(int offenseNumber)
	{
		offense = offenseNumber;
	}
	//Sets the Pokemon's Defense stat
	void setDefenseStat(int defenseNumber)
	{
		defense = defenseNumber;
	}
	//Allows us to set all the Pokemon's information in one swoop
	void setAll(std::string name, int number, std::string element, int attack, int defend)
	{
		pokemonName = name;
		serialNumber = number;
		elementalType = element;
		offense = attack;
		defense = defend;
	}


	/*
	The operator overload creates a temporary string and reads it based on how the data file is structured
	It then allocates the values to the object, converting based on the member variable it needs to store into
	This can be used to create a whole array or set up multiple nodes in on fell swoop
	*/
	friend std::ifstream& operator >> (std::ifstream &file, Pokemon &creature)
	{
		std::string tempString;
		int tempNumber;
		getline(file, tempString, '|');
		tempNumber = std::stoi(tempString);
		creature.setSerialNumber(tempNumber);
		getline(file, tempString, '|');
		creature.setPokemonName(tempString);
		getline(file, tempString, '|');
		creature.setElementType(tempString);
		getline(file, tempString, '|');
		creature.setOffenseStat(std::stoi(tempString));
		getline(file, tempString, '\n');
		creature.setDefenseStat(std::stoi(tempString));
		return file;
	}

	//  Overload the instream pointer operator
	friend std::ifstream& operator >> (std::ifstream &file, Pokemon *&creature)
	{
		std::string tempString;
		int tempNumber;
		getline(file, tempString, '|');
		tempNumber = std::stoi(tempString);
		creature->setSerialNumber(tempNumber);
		getline(file, tempString, '|');
		creature->setPokemonName(tempString);
		getline(file, tempString, '|');
		creature->setElementType(tempString);
		getline(file, tempString, '|');
		creature->setOffenseStat(std::stoi(tempString));
		getline(file, tempString, '\n');
		creature->setDefenseStat(std::stoi(tempString));
		return file;
	}

	// overloaded out stream operator 
	/*
	This overload allows us to print specific data to the ostream wherever needed.
	*/
	friend std::ostream &operator << (std::ostream &outStream, Pokemon &creature)
	{
		std::cout << creature.pokemonName;
		return outStream;
	}

	//  Overload the outstream pointer operator
	/*
	This accomplishes the same as the previous but allows us to do a print via pointers
	*/
	friend std::ostream &operator << (std::ostream &outStream, Pokemon *&creature)
	{
		std::cout << creature->pokemonName << " (" << creature->serialNumber << ")";
		return outStream;
	}


	//  Overloaded multiplication operator
	// currently not used
	int operator*(const Pokemon *&right)
	{
		int temp;
		temp = this->serialNumber * right->serialNumber;
		return temp;
	}

	// Overloaded <= pointer operation
	/*
	This comparison operator allows for indirect comparison of Pokemon objects allowing us to setup the BST
	*/
	bool operator <= (const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber < rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// Overloaded >= pointer operation
	/*
	This comparison operator allows for indirect comparison of Pokemon objects allowing us to setup the BST
	*/
	bool operator >= (const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// Overloaded >= operation
	/*
	This comparison operator allows for direct comparison of Pokemon objects allowing us to setup the BST
	*/
	bool operator >= (const Pokemon &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide.serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide.serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	//Overloaded <= operator allowing for comparison of Pokemon serial numbers with integer values
	bool operator<=(const int &number)
	{
		bool status;
		if (this->serialNumber == number)
		{
			status = true;
		}
		else if (this->serialNumber < number)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	//Overloaded >= operator allowing for comparison of Pokemon serial numbers with integer values
	bool operator>=(const int &number)
	{
		bool status;
		if (this->serialNumber == number)
		{
			status = true;
		}
		else if (this->serialNumber > number)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	//Overloaded > operator allowing for comparison of Pokemon serial numbers with integer values
	bool operator > (const int &number)
	{
		bool status;
		if (this->serialNumber > number)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// overloaded > operator for the pokemon pointer allowing for indirect Comparison of serial Numbers
	bool operator > (const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// overloaded > operator for the pokemon pointer allowing for direct Comparison of serial Numbers
	bool operator > (const Pokemon &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide.serialNumber)
		{
			status = true;
		}
		else if (this->serialNumber > rightSide.serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	/*
	This type conversion allows us to deal with the serialNumber with relative ease
	*/
	operator int()
	{
		int number;
		number = this->getSerialNumber();
		return number;
	}

	// overloaded conditional equal operator,  checks the int number to the serial number of the creature
	bool operator==(const int &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	// overloaded conditional equal operator when using a pokemon class pointer
	// compares the serial numbers of the two creatures, if the numbers match it will return true, else return false
	bool operator==(const Pokemon *&rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide->serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}

	//Overloaded comparison operator that functions with Pokemon class objects
	//It compares the serial numbers of two Pokemon returning whether the values are equal or not
	bool operator==(const Pokemon &rightSide)
	{
		bool status;
		if (this->serialNumber == rightSide.serialNumber)
		{
			status = true;
		}
		else
		{
			status = false;
		}
		return status;
	}
}; // end of Pokemon class declaration


#endif