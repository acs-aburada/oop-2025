#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum EngineType { GASOLINE, DIESEL, ELECTRIC };

class DeliveryVan {
    char* driver = nullptr;
    float km = 0;
    string* addresses = nullptr;
    int noAddresses = 0;
    EngineType type = EngineType::DIESEL;

public:
    DeliveryVan() {
        cout << endl << "Default ctor";
    }

    DeliveryVan(const char* driver, const float km, const EngineType type,
        const string* v, const int count) : km(km), type(type)
    {
        this->driver = new char[strlen(driver) + 1];
        strcpy_s(this->driver, strlen(driver) + 1, driver);
        this->addresses = new string[count];
        for (int i = 0; i < count; i++) {
            this->addresses[i] = v[i];
        }
        this->noAddresses = count;
    }

    ~DeliveryVan() {
        delete[] this->addresses;
        delete[] this->driver;
    }

    void print() const {
        cout << endl << "DeliveryVan" << endl;
        if (this->driver != nullptr) {
            cout << this->driver << endl;
        }
        cout << this->km << endl;
        switch (this->type) {
        case EngineType::GASOLINE:
            cout << "Gasoline" << endl;
            break;
        case EngineType::DIESEL:
            cout << "DIESEL" << endl;
            break;
        case EngineType::ELECTRIC:
            cout << "Electric" << endl;
            break;
        }
        cout << this->noAddresses << endl;
        for (int i = 0; i < this->noAddresses; i++) {
            cout << this->addresses[i] << endl;
        }
    }

    // serializing an object = converting the object inta stream of bytes or a string format
    // in a manner that can be reinterpreted to reconstruct the object (de-serialize)
    void serialize(ofstream& file) {
        // write element by element to binary file
        // write method -> array of chars of what we save; the size in B of the type we save

        // write the size of name - you need this later when reading from the file
        int nameSize = strlen(this->driver) + 1; //include \0
        file.write((char*)&nameSize, sizeof(int));
        // write the actual name
        file.write(this->driver, nameSize);

        //write the van km
        file.write((char*)&this->km, sizeof(float));

        //write the type -> will get cast to int
        file.write((char*)&this->type, sizeof(EngineType));

        // write the array size so we know how much space to allocate when
        // we de-serialize
        file.write((char*)&this->noAddresses, sizeof(int));

        // write the addresses
        for (int i = 0; i < this->noAddresses; i++) {
            // write string size
            int addressSize = this->addresses[i].size() + 1; //include \0
            file.write((char*)&addressSize, sizeof(int));
            // write string
            file.write(this->addresses[i].c_str(), sizeof(char) * addressSize);
        }
    }

    void deserialize(ifstream& file) {
        // read everything in the order that was written in the binary file
        int nameSize;
        file.read((char*)&nameSize, sizeof(int)); // this is why it is important to have +1 for \0

        delete[] this->driver;
        this->driver = new char[nameSize];
        file.read(this->driver, nameSize);

        file.read((char*)&this->km, sizeof(float));

        file.read((char*)&this->type, sizeof(EngineType));

        file.read((char*)&this->noAddresses, sizeof(int));
        delete[] this->addresses;
        this->addresses = new string[this->noAddresses];
        for (int i = 0; i < this->noAddresses; i++) {
            // read size of address string
            file.read((char*)&nameSize, sizeof(int));
            char* temp = new char[nameSize];
            file.read(temp, nameSize);
            this->addresses[i] = temp;
            delete[] temp;
        }
    }
};

int main() {
    string destinations[3] = {
        "Town 1",
        "Town 2",
        "Town 3"
    };
    char name[] = "John";
    DeliveryVan van(name, 1300, EngineType::GASOLINE, destinations, 3);
    van.print();

    // write to file
    ofstream backupOut("van.bin", ios::binary | ios::trunc);
    if (backupOut.is_open()) {
        van.serialize(backupOut);
        backupOut.close();
    }
    else {
        cout << endl << "Backup file corrupted";
    }

    // read from file
    DeliveryVan backup;
    backup.print();

    ifstream backupIn("van.bin", ios::binary);
    if (backupIn.is_open()) {
        backup.deserialize(backupIn);
        backupIn.close();
    }
    else {
        cout << endl << "Backup file corrupted";
    }
    backup.print();

    return 0;
}
\