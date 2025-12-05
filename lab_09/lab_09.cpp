#include <iostream>

using namespace std;

class ArrayUtil {
public:
    static string* copy(string* arr, int size) {
        if (size == 0 || arr == nullptr) {
            return nullptr;
        }
        string* result = new string[size];
        for (int i = 0; i < size; i++) {
            result[i] = arr[i];
        }
        return result;
    }
};

enum Genre { POP, ROCK, JAZZ };

class Playlist {
    const int id;
    string name = "default playlist";
    int noSongs = 0;
    string* songs = nullptr;
    Genre genre = Genre::POP;

public:
    static const int MAX_LENGTH;
    // default constructor
    Playlist() : id(0) {}

    Playlist(const int id) : id(id) {}

    // params constructor
    Playlist(const int id, const string name, const Genre genre) : id(id), name(name), genre(genre) {}

    // copy constructor
    Playlist(const Playlist& obj) : id(obj.id) {
        this->name = obj.name;
        this->genre = obj.genre;
        this->noSongs = obj.noSongs;
        // if the array is empty, then the function will return nullptr
        this->songs = ArrayUtil::copy(obj.songs, obj.noSongs);
    }

    ~Playlist() {
        delete[] this->songs;
    }

    void setSongs(string* songs, int size) {
        for (int i = 0; i < size; i++) {
            if (songs[i].length() > MAX_LENGTH) {
                throw "Song length is too long.";
            }
        }

        delete[] this->songs;

        this->songs = ArrayUtil::copy(songs, size);
        this->noSongs = size;
    }

    string* getSongs() const {
        return ArrayUtil::copy(this->songs, this->noSongs);
    }

    int getNoSongs() const {
        return this->noSongs;
    }

    void addSong(const string song) {
        if (song.length() > Playlist::MAX_LENGTH) {
            throw "Song length is too long.";
        }

        string* temp = new string[this->noSongs + 1];

        for (int i = 0; i < this->noSongs; i++) {
            temp[i] = this->songs[i];
        }
        temp[this->noSongs] = song; // this->noSongs here is not yet incremented and correctly points to the last element

        delete[] this->songs;
        this->songs = temp;

        this->noSongs++;
    }

    void print() const {
        cout << "\n\tPlaylist:\n";
        cout << "ID: " << this->id << endl;
        cout << "Name: " << this->name << endl;

        string genre;
        switch (this->genre) {
        case Genre::POP:
            genre = "POP";
            break;
        case Genre::ROCK:
            genre = "ROCK";
            break;
        case Genre::JAZZ:
            genre = "JAZZ";
            break;
        default:
            genre = "unknown";
        }
        cout << "Genre: " << genre << endl;

        cout << "No Songs: " << this->noSongs << endl;
        if (this->songs != nullptr) {
            for (int i = 0; i < this->noSongs; i++) {
                cout << " > \"" << this->songs[i] << "\"" << endl;
            }
            cout << endl;
        }
    }

    // OPERATORS
    // op=
    Playlist& operator=(const Playlist& p) {
        if (this == &p) {
            return *this;
        }

        this->name = p.name;
        this->genre = p.genre;

        this->noSongs = p.noSongs;
        delete[] this->songs;   // avoid mem leaks
        this->songs = ArrayUtil::copy(p.songs, p.noSongs);

        //this->id = p.id;  // don't do this

        return *this;
    }

    // op+
    Playlist operator+(const Playlist& p) const {
        Playlist temp(this->id + p.id, this->name + p.name, this->genre);

        // combine playlists
        temp.noSongs = this->noSongs + p.noSongs;
        temp.songs = new string[temp.noSongs];

        for (int i = 0; i < this->noSongs; i++) {
            temp.songs[i] = this->songs[i];
        }

        for (int i = 0; i < p.noSongs; i++) {
            temp.songs[i + this->noSongs] = p.songs[i];
        }

        return temp;
    }

    Playlist operator+(const int a) const {
        if (a < 0) {
            throw "Invalid value";
        }
        Playlist temp = *this;
        temp.name = "";
        for (int i = 0; i < a; i++) {
            temp.name += this->name;
        }
        return temp;
    }

    // a + 2 -> result is not saved; it CAN be saved if we assign it to a var
    // a += 2 -> result is saved in a; a changes
    Playlist& operator+=(const int a) {
        string copy = this->name;
        this->name = "";
        for (int i = 0; i < a; i++) {
            this->name = this->name + copy;
        }
        return *this;
    }

    string operator[](int i) {
        if (i >= this->noSongs) {
            throw "Invalid input.";
        }
        return this->songs[i];
    }

    bool operator==(const Playlist& p) const {
        if (this == &p) {
            return true;
        }

        if (this->id != p.id) {
            return false;
        }

        if (this->name != p.name) {
            return false;
        }

        if (this->genre != p.genre) {
            return false;
        }

        if (this->noSongs != p.noSongs) {
            return false;
        }

        for (int i = 0; i < this->noSongs; i++) {
            if (this->songs[i] != p.songs[i]) {
                return false;
            }
        }

        return true;
    }

    // a++ vs ++a
    // ++a - pre incrementation -> returns the MODIFIED value
    Playlist& operator++() {
        this->noSongs++;

        string* temp = new string[this->noSongs];
        for (int i = 0; i < this->noSongs - 1; i++) {
            temp[i] = this->songs[i];
        }
        temp[this->noSongs - 1] = "default song";

        delete[] this->songs;   // avoid mem leak
        this->songs = temp;

        return *this;
    }

    // a++ - post incrementation -> returns the ORIGINAL value but afterwards, 
    //                              the value is also MODIFIED
    Playlist operator++(int) {
        Playlist t = *this;  // we save the original value to return it
        ++(*this);  // now "this" is modified the same way pre inc. does
        return t;
    }
};

// global scope operator overloading
// for when you do not want "this" as the first parameter
Playlist operator+(const int a, const Playlist& p) {
    return p + a;   // i call the operator+ from the class
}

const int Playlist::MAX_LENGTH = 50;

int main() {
    Playlist p1;
    p1.print();

    Playlist p2(2, "My Playlist", Genre::POP);
    p2.addSong("Money, money, money");
    p2.addSong("Maneater");
    p2.addSong("Bohemian Rhapsody");
    p2.print();

    Playlist p3(3, "Party List", Genre::POP);
    string v[3] = { "Timber", "Lean On", "It's My Life" };
    p3.setSongs(v, 3);
    p3.print();

    Playlist p4 = p2;
    p4.print();

    // op=
    Playlist p5(5, "Playlist 5", Genre::JAZZ);
    p5 = p2;
    p5.print();

    //op+
    Playlist p6(6, "P6", Genre::POP);
    p6 = p2 + p3;
    p6.print();

    Playlist p7(7, "P7-", Genre::ROCK);
    p7 = p2 + 3;
    p7.print();

    Playlist p8(8, "P8*", Genre::POP);
    p8 = 6 + p8; // params: (int, Playlist)
    p8.print();

    Playlist p9(9, "9 - ", Genre::JAZZ);
    p9 += 9;
    p9.print();

    cout << endl;
    cout << p2[1] << " ; " << p3[0] << endl;
    cout << endl;
    

    cout << endl;
    cout << (p2 == p4) << endl;
    cout << (p2 == p3) << endl;
    cout << (p3 == p3) << endl;
    cout << endl;

    //(++p2).print();
    (p2++).print();
    p2.print();

    return 0;
}
