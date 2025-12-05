#include <iostream>

using namespace std;

// overloading
// same function name but different parameters
// int func(int a, int b)
// int func(int c, int d) -> not overloading
// -> it's actually int(int, int)
int sum(int a, int b) {
    return a + b;
}

int sum(int a) {    // this IS overloading
    return a + 1;
}

float sum(float x, float y) { // this is ALSO overloading
    return x + y;
}

enum Color { RED, GREEN, PURPLE };

class Util {
public:
    static string colorToString(Color c) {
        switch (c) {
        case Color::RED:
            return "red";
        case Color::GREEN:
            return "green";
        case Color::PURPLE:
            return "purple";
        default:
            return "unknown";
        }
    }

    static string* deepCopy(const string* const v, const int size) {
        if (size < 0) {
            throw "Size cannot be negative";
        }

        if (size == 0) {
            return nullptr;
        }

        string* result = new string[size];
        for (int i = 0; i < size; i++) {
            result[i] = v[i];
        }

        return result;
    }
};

class Journal {
    const long barcode;
    string brand = "none";
    int noPages = 0;
    string* pages = nullptr;
    Color color = Color::RED;
public:
    static const int MAX_PAGES;

    Journal() : barcode(0) {
        cout << "\nDefault ctor called" << endl;
    }

    Journal(const int barcode, const string brand, const Color color)
        : barcode(barcode), brand(brand), color(color) {
        cout << "\nParams ctor called" << endl;
    }

    // copy constructor
    // is called at declaration
    // Object o2 = o1; -> copy ctor // equivalent to o2(o1)
    // o2 = 01; -> this is NOT copy ctor
    Journal(const Journal& j) : barcode(j.barcode) {
        this->brand = j.brand;
        this->color = j.color;

        // deep copy of pages
        this->noPages = j.noPages;
        if (this->noPages > 0) {
            this->pages = new string[this->noPages];
            for (int i = 0; i < this->noPages; i++) {
                this->pages[i] = j.pages[i];
            }
        }
    }

    void setPages(const string* const pages, const int size) {
        if (size > Journal::MAX_PAGES) {
            throw "No. of pages bigger than allowed";
        }

        delete[] this->pages;
        this->pages = Util::deepCopy(pages, size);
        this->noPages = size;
    }

    void print() const {
        cout << "Printing ... " << endl;
        cout << barcode << endl;
        cout << brand << endl;
        cout << Util::colorToString(color) << endl;
        cout << noPages << endl;
        if (noPages > 0) {
            for (int i = 0; i < noPages; i++) {
                cout << pages[i] << "; ";
            }
        }
        cout << endl << endl;
    }

    ~Journal() {
        cout << "Destructor called" << endl;
        delete[] pages;
    }

    // return types
    // void -> is restrictive, does not allow chaining
    // for example, for operator+, if return type is void
    // you cannot do o1 = o1 + o2 + o3;
    // another example, you cannot do if (o1 = o2)

    // value of class
    // this is used when the result is a temporary or new object
    // see the difference between a = b + c AND a += b (~ a = a + b)

    // reference to class
    // this is used when we want to change "this"

    // operator=
    // o1 = 02 OR o1.operator=(o2)
    // receives "this" as the first parameter
    // operator= actually has 2 parameters (o1 - first; o2 - second)
    Journal& operator=(const Journal& j) {
        cout << "\nOperator= called" << endl;
        // do NOT do this
        //this->barcode = j.barcode;
        if (this == &j) {
            return *this;
        }

        this->brand = j.brand;
        this->color = j.color;
        this->noPages = j.noPages;

        delete[] this->pages;
        this->pages = Util::deepCopy(j.pages, j.noPages);
        return *this;
    }

    // operator+ -> concat the brands
    // two params: (this, j)
    // return type: class type
    Journal operator+(const Journal& j) const {
        Journal result = *this;
        result.brand = this->brand + j.brand;
        return result;
    }

};

const int Journal::MAX_PAGES = 70;

int main()
{
    // default ctor
    Journal j1;
    j1.print();

    // params ctor
    Journal j2(1234, "Rhodia", Color::GREEN);
    j2.print();
    string p[3] = { "text", "another text", "Dear Journal, ..." };
    j2.setPages(p, 3);
    j2.print();

    // copy ctor
    Journal j3 = j2;
    j3.print();

    Journal j4(9999, "Hobonachi", Color::PURPLE);
    j4.print();
    j4 = j2;
    j4.print();

    j4 = j4 + j2; // j4.operator+(j2) then j4.operator=(j4.operator+(j2))
    // j4.operator=(const Journal&)

    // sum(const int a, const int b)
    // you can call it with sum(const int, const int)
    // sum(int, int)
    j4.print();

    return 0;
}
