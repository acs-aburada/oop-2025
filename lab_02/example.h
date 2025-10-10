#pragma once // includes file only once during compilation

// scope 1 = global scope

// global variable
int GLOBAL_B;

void helloWorld() {
	printf("hello world\n");
}

namespace insideExample {
	// scope 2 = insideExample

	void byeWorld() {
		printf("bye world\n");
	}
}