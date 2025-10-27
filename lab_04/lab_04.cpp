#include <iostream>
#include <cstring>

// struct
struct CardsPlayerStruct {
//public: -> by default
	char value;	// value of the card
	int score;
	char* name = nullptr;

	void sayMyName() {
		if (name) {
			std::cout << "\nMy name is " << name << std::endl;
		}
		else {
			std::cout << "\nI don't have a name :(" << std::endl;
		}
	}
};

// class
// this -> keyword which reffers to the current object that the code is running in
// it's a pointer
class CardsPlayerClass {
//private: -> by default / encapsulation
	char value = '1';	// value of the card
	int score = 0;
	char* name = nullptr;

public:
	//CardsPlayerClass() {}	// given by default

	// if we declare a constructor with no arguments but with certain behaviour
	// we lose the default given one (line 31)
	CardsPlayerClass() {
		std::cout << "\nCalling constructor with no arguments\n";
	}

	CardsPlayerClass(const char value, const int score, const char* name) {
		// in the constructor to call setters instead of doing the assignations
		// because inside the setters you should have the validation logic
		setValue(value);
		setScore(score);
		setName(name);
	}

	// setters - general rule: return void, have parameters
	void setName(const char* name) {
		// validation - parameter name is not nullptr
		// name is max length 20
		if (name == nullptr) {
			throw "Value for name is invalid. (nullptr)";
		}

		if (strlen(name) > 20) {
			throw "Value for name is invalid. (over 20 characters)";
		}

		// allocate memory for name from class
		// deep copy
		this->name = new char[21];
		strcpy_s(this->name, 21, name);
	}

	char* getName() {
		//return this->name;	// NO -> shallow copy
	
		// create a deep copy instead
		// we create a new char* that will be returned having the same value as this->name
		unsigned int size = strlen(this->name) + 1;

		// allocation and initialization
		char* name = new char[size] {'\0'};
		// deep copying the name
		// = we created another space in memory in which we copy all the char values
		strcpy_s(name, size, this->name);

		return name;
	}

	void setScore(const int score) {
		// validation
		if (score <= 30 && score >= 0) {
			this->score = score;
		}
		else {
			throw "Value for score is invalid.";
		}
	}

	void setValue(const char value) {
		// validate value
		// value has to be 123456789AJQK
		if (strchr("123456789AJQKajqk", value))	// strchr -> returns the pointer of the first occurance of the char you're searching for (otherwise nullptr)
		{
			this->value = value;
			//value = value;
		}
		else {
			throw "Value for card is invalid. Please check your code.";		// const char*
		}
	}

	// getters - general rule: return a type, have no parameters
	char getValue() {
		return this->value;
	}

	void sayMyName() {
		if (name) {
			std::cout << "\nMy name is " << name << std::endl;
		}
		else {
			std::cout << "\nI don't have a name :(" << std::endl;
		}
	}

	void print() {
		if (this->name == nullptr)
			std::cout << "\nNo player name; score: " << this->score << "; card: " << this->value << std::endl;
		else
			std::cout << "\nName of player: " << this->name << "; score: " << this->score << "; card: " << this->value << std::endl;
	}

	// destructor
	~CardsPlayerClass() {
		if (this->name != nullptr) {
			delete[] this->name;
			this->name = nullptr;
		}
	}
};

int main() {
	// try is follow by a block of code that COULD throw errors
	try {
		// struct
		CardsPlayerStruct alice;
		alice.value = '1';
		std::cout << "\nAlice has value " << alice.value << std::endl;
		//	alice.value = 10; // this is an invalid value that was allowed to be assigned because the attribute is public

		alice.sayMyName();
		char* aliceName = new char[21];
		strcpy_s(aliceName, 21, "Alice");
		alice.name = aliceName;		// shallow copy
		// shallow copy -> instead of allocating new memory space and THEN copying the values
		// i simply copy the pointer
		// right now, alice.name (char*) and aliceName (char*) point to the SAME memory space
		// if I called delete[] alice.name -> aliceName would become a dangling pointer
		alice.sayMyName();

		// class
		CardsPlayerClass bob;
		//bob.value = 'A';	// member inaccessible -> because it is PRIVATE
		bob.setValue('A');
		std::cout << "\nBob has value " << bob.getValue() << std::endl;
		//bob.setValue('B');

		bob.sayMyName();

		char* charlieName = new char[21];
		strcpy_s(charlieName, 21, "Charlie");
		char charlieValue = 'K';
		int charlieScore = 1;
		//char* dummy = nullptr;

		// call the constructor
		CardsPlayerClass charlie(charlieValue, charlieScore, charlieName);
		charlie.print();
		char* charlieName2 = charlie.getName();
		std::cout << "\nCharlie's name: " << charlieName2 << std::endl;

		delete[] aliceName;
		aliceName = nullptr;
		//delete[] alice.name; // no because the memory has been deallocated already -> because we shallow copied
		alice.name = nullptr;

		delete[] charlieName;
		charlieName = nullptr;

		delete[] charlieName2;
		charlieName2 = nullptr;
	}
	// catch
	catch (const char* errorMessage) {
		std::cout << "\nError caught!!! Error message: " << errorMessage << std::endl;
		return -1;
	}
	catch (...) {
		std::cout << "\nError caught!!! Unknown error.\n";
		return -2;
	}

	return 0;
}