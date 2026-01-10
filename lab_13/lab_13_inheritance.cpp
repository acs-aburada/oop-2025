#include <iostream>

using namespace std;

class Character {
	// protected access modifier -> outside of the class it acts like private
	//	-> inside classes that inherit it, acts like public
protected:
	string name;
	int level = 0;
public:
	explicit Character(string name) {
		this->name = name;
	}

	Character() {
		this->name = "lonely character";
	}

	string getName() const {
		return this->name;
	}

	void describe() {
		cout << endl << "Character: " << name;
	}

	virtual void attack() {
		cout << endl << "Character " << name << " is attacking";
	}
};

// inheritance - using ":"
// it means: Mage extends/inherits class Character
// by default, inheritance is done with access modifier "private"
// but others may be used
// public: 
	// public -> public, protected -> protected, private -> private
// private: they all become private

class Mage : public Character {
	float mana = 20.5;
public:
	Mage() : Character("no name mage") { }
	Mage(string name) : Character(name) { }

	void display() {
		cout << endl << "Mage: " << name;
	}

	void attackMage() {
		cout << endl << "Mage " << name << " is attacking";
	}

	void attack() {
		cout << endl << "Mage " << name << " is attacking";
	}
};

class Wizard : public Mage {
protected:
	string staff = "golden";
public:
	Wizard() : Mage("Gandalf") { }

	void attack() {
		cout << endl << "Wizard " << name << " is attacking";
	}
};

class Warrior : public Character {
protected:
	bool hasAxe = true;
public:
	Warrior() : Character("Ragnar") { }
};

// framework of classes

int main() {
	Character c;
	Mage mage("Merlin");
	Wizard wizard;
	Warrior warrior;

	// Q: we have many types of chars, but we want to keep track of them. How?
	// one approach - BAD - impractical
	//Character v1[3];
	//Mage v2[5];
	//Wizard v3[2];
	//Warrior v4[6];

	// A: up-casting
	Character aCharacter;
	aCharacter = c;
	aCharacter = mage;	// up-casting - implicit

	// down-cast
	//Warrior warrior2 = (Warrior)aCharacter;

	//Character characters[3];
	//characters[0] = c;
	//characters[1] = mage;
	//characters[2] = wizard;

	c.attack();
	mage.attack();
	//mage.attackMage();
	wizard.attack();

	cout << endl << endl;

	//for (int i = 0; i < 3; i++) {
	//	characters[i].attack();
	//}

	Character* charactersP[3];
	charactersP[0] = &c;
	charactersP[1] = &mage;
	charactersP[2] = &wizard;

	for (int i = 0; i < 3; i++) {
		charactersP[i]->attack();
		// the compiler does EARLY-BINDING based on the type of the array elements
		// in our case, Character

		// we need to force it to do LATE-BINDING
	}

	return 0;
}