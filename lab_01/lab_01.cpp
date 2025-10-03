#include <iostream> // used for standarding inputs (see end of main)

// example function for debugging
int getSum(int a, int b) {
	return a + b;
}

int global_a;	// will be initialized with 0 by default

// example function for static initalization demonstration
void staticExample() {
	static int static_a = 0;
	static_a += 1;
	printf("static_a = %d\n", static_a);
}

int main()
{
	// types
	int a = 10;				// size 4B
	unsigned int b = -3;	// the most significant bit (most left one) is the sign bit
	printf("a = %d; b = %u\n", a, b);

	float c = 1.4f;
	double d = 1.4L;

	//char character = 49;				// a single character
	//printf("one character -> %d %c\n", character, character);

	char character[] = { 49, 50, 51, 0 };	// array of characters
	printf("array of characters (with termination) -> %s\n", character); // ! %s takes a pointer to char while %c takes a char variable
	
	// the element with value 0 will determine the end of the string
	// otherwise %s will print values beyond your array (garbage values)
	// until it finds the first zero byte (0x00) (equivalent to '\0')
	// BONUS: check the "memory" panel and see where the first 0x00 byte is
	character[3] = 52;
	printf("array of characters (without termination) -> %s", character);

	bool boolean_1 = true;	// 0 or 1
	printf("%d\n", boolean_1);

	bool boolean_2 = 99;	// any non-zero value is considered as "true"
	if (boolean_2 == true)
		printf("true\n");
	else
		printf("false\n");

	// special types

	// global -> see line 8

	// static -> will be initialized only once even
	//			 if the initalization line is ran multiple times
	staticExample();	// will print 1
	staticExample();	// will print 2

	// const -> immutable = cannot change their value and MUST be initialized
	//const int const_a;	// compiler error -> not initialized
	const int const_a = 1;

	// debugging
	// using step into
	int x = getSum(1, 2);

	// errors
	// compiler and runtime

	// compiler errors
	//int z = 3
	//char hello[] = "hello;

	// runtime errors
	int number = 5;
	int g = 3;
	g = g - 3;
	//printf("%d", number / g);		// division by zero

	// dynamic memory allocation
	
	// c
	//int* array = (int*)malloc(5 * sizeof(int));
	//free(array);
	//array = NULL;

	// c++
	int* array = new int[5];
	delete[] array;
	array = nullptr;

	// pointers mistakes

	// !!! memory leak = allocating memory without deallocating it
	// this example will crash the program (might take some time)
	//while(true) {
	//	int *leaker = new int[50000];
	//	leaker[0] = 1;
	//}

	// this program will run infinitely without memory issues
	//while (true) {
	//	int* leaker = new int[50000];
	//	leaker[0] = 1;
	//	// deallocate and set pointer to null
	//	delete[] leaker;
	//	leaker = nullptr;
	//}

	// !!! dangling pointer = a pointer that points to memory that has been deallocated
	int* dangler = new int[2];
	int* dangler_copy = dangler;
	delete[] dangler;
	dangler = nullptr;
	printf("value of pointer dangler = 0x%p -> points to nothing | CORRECT\n", dangler);
	printf("value of pointer dangler_copy = 0x%p -> points to deallocated memory | WRONG\n", dangler_copy);

	// c++ specific input and output
	// input (standard (keyword std) = keyboard)
	int k;
	printf("k = ");
	std::cin >> k;
	// output (standard = console)
	std::cout << k;


	// enum = special type that represents a group of constants
	// defined outside main, for example purposes it will be included in main
	// by default the values will start from 0
	//				0		1		2		3
	enum Season { SPRING, SUMMER, AUTUMN, WINTER };
	enum Season myFavouriteSeason = Season::WINTER;
	std::cout << "\nMy favourite season is " << myFavouriteSeason;

	// enum hold integers, they can be custom defined
	//enum Season_2 { SPRING = 1, SUMMER = 2, AUTUMN = 3, WINTER = 4 };

	// mapping them to other values or code is done using switch
	// switch strucutre = select one of many code blocks to execute
	// (imagine a boat flowing down a river and diverging into multiple smaller streams)
	switch (myFavouriteSeason) {
		case Season::SPRING:
			std::cout << "\nMy favourite season is spring!\n";
			break;		// if we don't use break then the code will 
						// continue executing within the switch structure
		case Season::SUMMER:
			std::cout << "\nMy favourite season is summer!\n";
			break;
		case Season::AUTUMN:
			std::cout << "\nMy favourite season is autumn!\n";
			break;
		case Season::WINTER:
			std::cout << "\nMy favourite season is winter!\n";
			break;
	}

	return 0;	// error code -> 0
}

