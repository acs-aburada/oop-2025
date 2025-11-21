#include <iostream>

using namespace std;

enum A {one, two};
//enum B {one, two}; // can't use the same items
enum B {three, four};

int main()
{
    int x = A::one; // implicit cast
    int y = B::three;
    cout << (x == y) << endl;
    cout << (B::three == A::one) << endl;
    A a = A::one;
    B b = B::three;
    cout << (a == b);
    return 0;
}
