#include <iostream>
#include <fstream>

using namespace std;

enum Type { PERSON, FAMILY, NATURE };

class Photo {
    const int id;
    char* desc = nullptr;
    int width = 1;
    int height = 1;
    Type type = NATURE;
public:
    explicit Photo(const int id): id(id) {}
    Photo(const int id, const char* desc, int w, int h, Type t) :
        id(id), width(w), height(h), type(t) {
        this->desc = new char[strlen(desc) + 1];
        strcpy_s(this->desc, strlen(desc) + 1, desc);
    }
    // copy ctor
    Photo(const Photo& p) : id(p.id), width(p.width), height(p.height), type(p.type) {
        if (p.desc != nullptr) {
            this->desc = new char[strlen(p.desc) + 1];
            strcpy_s(this->desc, strlen(p.desc) + 1, p.desc);
        }
    }

    ~Photo() {
        delete[] this->desc;
    }

    // write each attribute to a new line
    friend ostream& operator<<(ostream& out, const Photo& p);

    // read line by line -> attribute by attribute
    friend istream& operator>>(istream& in, Photo& p);
};

// cout << p1 << p2;

// !!! for dynamic fields, it is MANDATORY that before you output each element
// you write the SIZE of the dynamic array
ostream& operator<<(ostream& out, const Photo& p) {
    out << p.id << endl;
    if (p.desc == nullptr) {
        out << endl;
    }
    else {
        out << p.desc << endl;
    }
    out << p.width << endl;
    out << p.height << endl;
    out << p.type << endl;

    return out;
}


istream& operator>>(istream& in, Photo& p) {
    // ! first line when we wrote into the file was a const attribute
    // but when we read from a file, the object already exists
    char buffer[50];
    in.getline(buffer, 49); // because buffer now has "id", we simply do not use it

    in.getline(buffer, 49); // this now will hold our description
    delete[] p.desc;
    if (strlen(buffer) > 0) {
        p.desc = new char[strlen(buffer) + 1];
        strcpy_s(p.desc, strlen(buffer) + 1, buffer);
    }
    in >> p.width;
    in >> p.height;
    //in >> p.type;
    int typeIndex;
    in >> typeIndex;
    p.type = (Type)typeIndex;

    return in;
}

class SocialMedia {
    string name = "";
    // HAS-A relation -> 1-1
    Photo photo;
    static int NO_PROFILES;

public:
    explicit SocialMedia(const string name): name(name),
        photo(++NO_PROFILES, "social media photo", 5, 8, Type::PERSON) {}

    void print() const {
        cout << name << endl;
        cout << photo << endl;
    }
};

int SocialMedia::NO_PROFILES = 0;

class Album {
    string name = "";
    // HAS-A relation -> 1-M
    int noPhotos = 0;
    Photo** photos = nullptr;   // photos[i] is of type Photo*
public:
    Album() : name("default album") {}

    // if you allocate with new int[size]   -> delete[]
    // if you allocate with new int         -> delete
    void setPhotos(Photo* arr, int noPhotos) {
        if (this->noPhotos > 0) {
            for (int i = 0; i < this->noPhotos; i++) {
                delete photos[i];
            }
            delete[] photos;
        }
        this->photos = new Photo* [noPhotos];
        for (int i = 0; i < noPhotos; i++) {
            photos[i] = new Photo(arr[i]);  // calls copy ctor with param arr[i]
        }
        this->noPhotos = noPhotos;
    }

    void addPhoto(Photo& p) {
        Photo** temp = new Photo * [this->noPhotos + 1];
        for (int i = 0; i < noPhotos; i++) {
            temp[i] = new Photo(*(this->photos[i]));
        }
        temp[this->noPhotos] = new Photo(p);

        for (int i = 0; i < this->noPhotos; i++) {
            delete photos[i];
        }
        delete[] photos;

        this->noPhotos++;
        this->photos = temp;
    }

    void printPhotos() const {
        cout << name << endl;
        for (int i = 0; i < noPhotos; i++) {
            cout << *(this->photos[i]) << endl << "***" << endl;
        }
    }

    ~Album() {
        for (int i = 0; i < this->noPhotos; i++) {
            delete photos[i];
        }
        delete[] photos;
    }
};

int main() {
    //fstream -> for both input and output
    //ofstream -> for output (by specifying certain opening modes, we can output to binary files)
    //ifstream -> for input (the same; we can get info from binary files)

    // -- opening modes
    // ios::out -> output
    // ios::in -> input
    // ios::ate -> AT THE END -> we position ourselves (the pointer) to the end of the file
    // ios::app -> APPEND -> we always append our data at the end without erasing
    // ios::trunc -> TRUNCATE -> we always discard the information in the filed before writing

    //fstream outFile("out.txt", ios::out | ios::ate);
    ofstream outFile("out.txt");
    if (outFile.is_open()) {
        outFile << "This is my file" << endl;
    }
    else {
        cout << "Unable to open file" << endl;
    }
    outFile.close();

    // about reading from the keyboard
    //char text[50];
    //cout << "write text: ";
    ////cin >> text;
    //cin.getline(text, 49);
    //cout << text << endl;
    //// if you have more than 49 chars
    //// getline fails, the rest of the line needs to be discarded
    //// failbit will be set

    //// if the stream failed and it's not good
    //// we need to reset the flag and discard the rest of the line
    //if (!cin.good()) {
    //    cin.clear();
    //    cin.ignore(1000, '\n');
    //}

    //fstream inFile("in.txt", ios::in);
    //ifstream inFile("in.txt");
    //if (inFile.is_open()) {
    //    char buffer[200];

    //    
    //    while (!inFile.eof()) {
    //        // read line by line into the buffer
    //        inFile.getline(buffer, 199);
    //        cout << "\nline: " << buffer << endl;

    //        // word by word
    //        //inFile >> buffer;
    //        //cout << "\word: " << buffer << endl;
    //    }
    //}
    //else {
    //    cout << "Unable to open file" << endl;
    //}
    //inFile.close();

    Photo p1(1, "just a photo", 10, 20, Type::PERSON);
    cout << p1 << endl;

    ofstream pOut("p_out.txt");
    if (pOut.is_open()) {
        pOut << p1;
    }
    else {
        cout << "Unable to open file" << endl;
    }
    pOut.close();

    Photo p2(2);
    cout << p2 << endl;

    ifstream pIn("p_out.txt");
    if (pIn.is_open()) {
        pIn >> p2;
    }
    else {
        cout << "Unable to open file" << endl;
    }
    pIn.close();

    cout << p2 << endl;

    // 1-1 RELATION
    SocialMedia sm1("Jane Doe");
    sm1.print();

    SocialMedia sm2("John Doe");
    sm2.print();

    // 1-M RELATION
    Album a1;
    Photo p3(3, "summer in Italy", 4, 8, Type::FAMILY);
    a1.addPhoto(p3);
    a1.printPhotos();

    return 0;
}