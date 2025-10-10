#include <stdio.h>	// C
#include "example.h"	// comes with all its scopes
#include <iostream>		// comes with std C++

// GLOBAL
// its reachable from anywhere in the file
// initialzied with 0 at runtime
static unsigned int STATIC_A;	// no. of times a function is called

// dummy function
void staticTest() {
	//static unsigned int STATIC_A = 0;
	STATIC_A++;		// STATIC_A += 1; same as STATIC_A = STATIC_A + 1;
	printf("%d\n", STATIC_A);
}

// namespace example
namespace insideLab02 {
	// we are inside scope insideLab02
	int b = 4;
}

//using namespace std;	// import all things from scope std
// cin, cout, endl
using std::cin;
using std::cout;
using std::endl;

int main()
{
	// CONST
	// it NEEDS to be initialized
	// immutable -> cannot change values
	//const int CONST_A;
	const int CONST_A = 16;

	//CONST_A = 10;		// compiler error

	// STATIC
	// it is initialized only once even if the code line runs more times
	staticTest();
	staticTest();

	printf("%d\n", GLOBAL_B);
	// from example.h
	helloWorld();

	// :: - scope resolution operator  scope::object (variable, function etc)
	static unsigned int STATIC_A = 10;
	printf("%d\n", STATIC_A);
	printf("%d\n", ::STATIC_A);

	// namespaces - collection
	printf("%d\n", insideLab02::b);

	//byeWorld();	// ::byeWorld();
	insideExample::byeWorld();

	// C++ input from keyboard & output to console
	int n = 10;
	char c = 'a';
	char text[] = "hello";	// add a 0x00 ('/0') at the end

	printf("C way = %d %c %s\n", n, c, text);
	std::cout << "C++ way = " << n << " " << c << " " << text << std::endl;		// !!! text is null terminated

	// read from keyboard in C++
	//int m;
	//cin >> m;
	//cout << m << endl;

	// pointers
	// static allocated array
	int v[] = { 1, 4, 6 };							// allocates memory and initializes it automatically
	cout << "v[0] = " <<  v[0] << endl;				// 1
	cout << "v[1] = " << v[1] << endl;				// 4
	cout << "v (pointer to int) = " << v << endl;	// v is the address of where the array starts
	cout << "*(v) = " << *v << endl;
	cout << "v + 1 = " << v + 1 << endl;			// the address of v + sizeof(int)
	cout << "*(v + 1) = " << *(v + 1) << endl;		// 4 -> 
	cout << "*(v) + 1 = " << *v + 1 << endl;		// 1 + 1
	int* w = v + 1;		// v + 1 * sizeof(int)
	cout << w - v << endl;

	// dynamic allocated
	int* q;	// lotto numbers

	// we have the numbers! ( 3 numbers )
	// 1. allocate space
	q = new int[6]; // uninitialized memory

	// 2. initialize the memory
	for (int i = 0; i < 6; i++) {	// positions -> 0 1 2 3 4 5
		q[i] = 0;	// initialize each element
	}

	// another approach
	//q = new int[6]();	// allocate AND initialize the memory with 0 

	q[0] = 7;	// first position is 0 because array starts at the address of q
				// which is the same as saying *(v + 0)
	q[1] = 13;
	q[2] = 9;

	for (int i = 0; i < 6; i++) {
		cout << q[i] << " ";
	}
	cout << endl;	// add a new line for visibility

	// ALWAYS deallocate
	delete[] q;		// the memory where the array was is deleted
					// but the pointer address is not reset

	q = nullptr;	// q is ready to be reallocated and the memory has been safely
					// and correctly deallocated
					// not setting it to nullptr can also be a case of a dangling pointer

	// MEMORY LEAK !!!
	// when memory doesnt get deallocated and you lose the reference to it
	//while (true) {
	//	int* wrong = new int[100000];

	//	delete[] wrong;
	//	wrong = nullptr;
	//}

	// DANGLING POINTER !!!
	int* dangler = new int[2];
	dangler[0] = 30;
	dangler[1] = 41;
	int* dangler_copy = dangler;
	cout << "*dangler_copy = " << *dangler_copy << endl;

	delete[] dangler;
	dangler = nullptr;
	// now dangler_copy is a dangling pointer
	cout << "dangler_copy is a dangling pointer pointing to 0x" << dangler_copy << endl;
	cout << "*dangler_copy = " << *dangler_copy << endl;
	//delete[] dangler_copy;	// WRONG - memory has been deallocated
	dangler_copy = nullptr;

	return 0;
}