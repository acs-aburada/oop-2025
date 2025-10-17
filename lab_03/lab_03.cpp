#include <iostream> // std::cout, std::cin, std::endl

// enum
enum Suit { HEARTS = 1, DIAMONDS, CLUBS, SPADES };
//			    0       1       2       3
//				1		2		3		4

// functions
// have return types
int sum(int a, int b) {
	return a + b;
}

void sum2(int a, int b) {
	int c = a + b;
	std::cout << c << std::endl;
}

// parameters
// by value
// function stack memory is managed by the program
// this is where the parameter copies are
// when we allocate memory -> heap
// the heap is managed by the programmer!!
void updateScoreByValue(int initialScore, const int newScore) {
	initialScore = newScore;
}

// by pointer
void updateScoreByPointer(int* initialScore, const int newScore) {
	*initialScore = newScore;
}

// by reference
// when we want to change values and pass the changes to main
// we use &
void updateScoreByReference(int &initialScore, const int newScore) {
	initialScore = newScore;
}

// dynamic memory in functions
// return copy of player name (char*)
// malloc(size * sizeof(type))
char* copyPlayer(char* player) {
	// name: Bob in memory -> 'B' 'o' 'b' '\0'
	// strlen("Bob") = 3
	int size = strlen(player) + 1;	// the no of chars until the first null byte char '\0'
	
	// allocation and initialization in one line
	char* copy = new char[size] {'\0'};	// C++ way
	// { char } -> initialize the array with the char value

	// copy
	// 3 parameters: dest, dest_size, src
	//				 char*,  (int),  char*
	strcpy_s(copy, size, player);
	// if we use src size, we can have a src bigger than dest
	// which will cause a buffer overflow
	// = writing in space you're not supposed to

	// Q: do we need to deallocate any memory?
	//delete[] copy; // A: NO -> because we are not done with it

	return copy; // after the function, var "copy" gets deleted -> in the function stack
	// the actual memory space REMAINS
}

int main() {
	// :: scope resolution operator
	Suit mySuit = Suit::DIAMONDS;
	std::cout << "my suit: " << mySuit << std::endl;

	int result = sum(1, 2);

	int score = 11;
	// by value
	updateScoreByValue(score, 13);
	std::cout << "update by value: " << score << std::endl;

	// by pointer
	updateScoreByPointer(&score, 14);
	std::cout << "update by pointer: " << score << std::endl;

	// by reference
	updateScoreByReference(score, 15);
	std::cout << "update by reference: " << score << std::endl;

	// function memory allocation
	char myPlayer[] = "Bob";
	myPlayer[3] = 'c';
	std::cout << myPlayer << std::endl;
	myPlayer[3] = '\0';
	std::cout << myPlayer << std::endl;

	char* myPlayerCopy = copyPlayer(myPlayer);
	// myPlayerCopy -> dynamically allocated memory
	// it is our job to mamange it
	std::cout << "player copy: " << myPlayerCopy << std::endl;

	// are we done with the dynamically allocated memories now?
	delete[] myPlayerCopy; // does not set the address of the pointer to null
	myPlayerCopy = nullptr;

	// C++ string
	std::string anotherPlayer = "Alice";
	std::cout << "another player: " << anotherPlayer << std::endl;
	// length
	std::cout << "length: " << anotherPlayer.length() << std::endl;
	// string to char*
	// gives you a pointer to char that points in memory where the buffer of anotherPlayer starts
	// you should not modify the returned value which is why the return type is const!
	const char* anotherPlayerCopy = anotherPlayer.c_str();
	std::cout << "another player copy: " << anotherPlayerCopy << std::endl;
	// anotherPlayerCopy is not managed by us, we don't need to deallocate it
	return 0;
}
