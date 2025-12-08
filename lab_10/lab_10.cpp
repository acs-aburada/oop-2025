#include <iostream>
#include <fstream>

using namespace std;

class Util {
public:
    static double* copy(double* const v, const int size) {
        if (size == 0 || v == nullptr) {
            return nullptr;
        }
        double* result = new double[size];
        for (int i = 0; i < size; i++) {
            result[i] = v[i];
        }
        return result;
    }
};

enum Type { TEMPERATURE, PRESSURE, HUMIDITY };

class Sensor {
    const int id;
    Type type = Type::TEMPERATURE;
    double* readings = nullptr;
    int noReadings = 0;

    static const int MAX_READINGS = 100; // can be defined and initialized due to being const
    static int NO_SENSORS; // can only be defined inside the class

public:
    Sensor() : id(0) { NO_SENSORS++; }
    // if explicit is not used, then Sensor s = 5 will act as an implicit cast
    // which can cause unintended behaviour
    // if we don;t use explicit we can also do Sensor s = 5;
    // if we use explicit, we can only do Sensor s(5);
    explicit Sensor(const int id) : id(id) { NO_SENSORS++; }
    Sensor(const int id, const Type type) : id(id), type(type) { NO_SENSORS++; }

    Sensor(const Sensor& s) : id(s.id), type(s.type) {
        this->noReadings = s.noReadings;
        this->readings = Util::copy(s.readings, s.noReadings);
        NO_SENSORS++;
    }

    ~Sensor() {
        delete[] this->readings;
        NO_SENSORS--;
    }

    static int getNoSensors() {
        return NO_SENSORS;
    }

    void print() const {
        cout << this->id << endl;
        string type = "";
        switch (this->type) {
        case Type::TEMPERATURE:
            type = "TEMPERATURE";
            break;
        case Type::PRESSURE:
            type = "PRESSURE";
            break;
        case Type::HUMIDITY:
            type = "HUMIDITY";
            break;
        default:
            type = "UNKNOWN";
        }
        cout << type << endl;
        cout << this->noReadings << endl;
        if (this->noReadings > 0) {
            for (int i = 0; i < noReadings; i++) {
                cout << this->readings[i] << "; ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void setReadings(double* const readings, const int noReadings) {
        if (noReadings > Sensor::MAX_READINGS) {
            throw "Too many readings";
        }
        if (noReadings <= 0) {
            throw "Not enough readings";
        }

        delete[] this->readings;
        this->readings = Util::copy(readings, noReadings);
        this->noReadings = noReadings;
    }

    // operators
    // why const is needed:
    // a = b + c -> a = b.operator+(c), BUT b.operator+(c) actually returns a temporary result
    //                                  which is const
    // ALSO, if you have a parameter that is const, you can call it with a non-const variable
    // BUT, if you have a non-const parameter, you CANNOT call it with a const
    Sensor& operator=(const Sensor& s) {
        if (this == &s) {
            return *this;
        }
        this->type = s.type;
        this->noReadings = s.noReadings;
        this->readings = Util::copy(s.readings, s.noReadings);
        //this->id = s.id;  // DO NOT DO THIS
        return *this;
    }

    // pre vs post incrementation
    // pre: modifies "this" and returns modified "this"
    Sensor& operator++() {
        // our operator logic
        for (int i = 0; i < this->noReadings; i++) {
            this->readings[i]++;
        }
        // return the result
        return *this;
    }

    // post: modifies "this" BUT returns a copy of the ORIGINAL "this"
    Sensor operator++(int) {
        // make a copy that will be the result (we keep the ORIGINAL)
        Sensor result = *this;
        // our operator logic
        this->operator++();
        //return the result
        return result;
    }

    // cout << a -> cout.operator<<(a)
    // parameter list: (cout, a)
    //operator<<(ofstream& out) -> params: this, out
    //operator<<(ofstream& out, Sensor& a) -> params: this, out, a

    // to avoid getting "this", we need to define the function header in the class
    // but implement the function outside the class
    // friend allows the definition of the function that is OUTSIDE the class
    // to access private attributes
     friend ostream& operator<<(ostream& out, const Sensor& s);

     // cast operator can be of type explicit or implicit
     // explicit -> ONLY explicit
     explicit operator int() const {
         return this->id;
     }

     // implicit -> gives BOTH implicit and explicit
     //operator int() const {
     //    return this->id;
     //}

     // s1.operator[](i) OR s1[i]
     double operator[](int i) {
        if (i < 0 || i >= this->noReadings) {
             throw "Invalid index";
        }
        return this->readings[i];
     }

     Sensor operator-(double a) {
         Sensor result = *this;
         if (result.noReadings > 0) {
             for (int i = 0; i < result.noReadings; i++) {
                 result.readings[i] = result.readings[i] - a;
             }
         }
         return result;
     }

     friend Sensor operator-(double a, Sensor& s);
};

Sensor operator-(double a, Sensor& s) {
    return s - a;   // s.operator-(a)
}

ostream& operator<<(ostream& out, const Sensor& s) {
    out << s.id << endl;
    string type = "";
    switch (s.type) {
    case Type::TEMPERATURE:
        type = "TEMPERATURE";
        break;
    case Type::PRESSURE:
        type = "PRESSURE";
        break;
    case Type::HUMIDITY:
        type = "HUMIDITY";
        break;
    default:
        type = "UNKNOWN";
    }
    out << type << endl;
    out << s.noReadings << endl;
    if (s.noReadings > 0) {
        for (int i = 0; i < s.noReadings; i++) {
            out << s.readings[i] << "; ";
        }
        out << endl;
    }
    out << endl;

    return out;
}

int Sensor::NO_SENSORS = 0;

int main() {
    Sensor s1;
    s1.print();

    Sensor s2(2, Type::HUMIDITY);
    double v1[3] = { 10.2, 23.1, 9.32 };
    s2.setReadings(v1, 3);
    s2.print();

    Sensor s3 = s2;
    s3.print();

    Sensor* s4 = new Sensor(4);
    double v2[4] = { 3.12, 9.89, 0.12, 4.55 };
    s4->setReadings(v2, 4);
    s4->print();

    Sensor s5(5);
    s5 = s2;
    s5.print();

    Sensor s6(6, Type::HUMIDITY);
    double v3[3] = { 11.23, 7.65, 10.09 };
    s6.setReadings(v3, 3);
    s6.print();

    // pre ++
    (++s6).print(); // expected result: array was changed

    // post ++
    (s6++).print(); // expected result: array was not changed, but the change will be visible after this line
    s6.print();

    cout << s6;

    int id;
    //id = s6;      // this is an implicit cast
    id = (int)s6;   // this is an explicit cast
    cout << "ID: " << id << endl;

    cout << "2nd Element of s6: " << s6[1] << endl;   // second element = index 1

    cout << endl;

    cout << (s6 - 3.1);   // s6.operator-(3.1)
    // s6 + 2       // params: s6, 2
    // 2 + s6       // params: 2, s6
 
    // if you do not overload operator-(int, Sensor) then the cast operator to int will be called
    // ONLY if the cast operator is NOT explicit
    cout << (3.1 - s6) << endl;


    delete s4;  // !!! DON'T FORGET TO DELETE IT

    return 0;
}
