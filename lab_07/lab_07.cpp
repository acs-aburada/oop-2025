#include <iostream>

using namespace std;

enum class Experience {BEGINNER, AMATEUR, PROFESSIONAL};

class ElevatorOperator {
    string name = "";
    Experience experience = Experience::BEGINNER;
    int queueLength = 0;
    int* floorQueue = nullptr;
    const int id;   // employee id
    static int NO_OPERATORS;

public:
    static const int MAX_FLOORS = 24;

    ElevatorOperator() : id(0) {
        cout << "\n\tDefault c-tor called";
        ElevatorOperator::NO_OPERATORS++;
    }

    ElevatorOperator(const string name, Experience experience, int id) : id(id) {
        cout << "\n\tParams c-tor called";
        ElevatorOperator::NO_OPERATORS++;
        if (name.empty()) {
            throw "Name cannot be empty";
        }
        this->name = name;
        this->experience = experience;
        //this->id = id;
    }

    ElevatorOperator(ElevatorOperator& op) : id(op.id) {
        cout << "\n\tCopy c-tor called";
        ElevatorOperator::NO_OPERATORS++;

        this->name = op.name;
        this->experience = op.experience;
        this->queueLength = op.queueLength;
        // deep copy
        if (op.queueLength > 0) {
            this->floorQueue = new int[this->queueLength];
            for (int i = 0; i < this->queueLength; i++) {
                this->floorQueue[i] = op.floorQueue[i];
            }
        }
    }

    void addFloor(int floor) {
        if (floor < -10 || floor > ElevatorOperator::MAX_FLOORS) {
            throw "New floor value is invalid";
        }
        int* newQueue = new int[this->queueLength + 1];
        for (int i = 0; i < this->queueLength; i++) {
            newQueue[i] = this->floorQueue[i];
        }
        this->queueLength++;
        if (this->floorQueue != nullptr) {
            delete[] this->floorQueue;
        }
        this->floorQueue = newQueue;
        // add new value
        this->floorQueue[this->queueLength - 1] = floor;
    }

    // remove floor from the first position
    void removeFloor() {
        if (this->floorQueue == nullptr) {
            cout << "\nNo floors to go to.";
        }
        else if (this->queueLength == 1) {
            cout << "\nGoing to floor " << this->floorQueue[0];

            delete[] this->floorQueue;
            this->floorQueue = nullptr;
            this->queueLength = 0;
        }
        else {
            int* newQueue = new int[this->queueLength - 1]; // index from 0 to queueLength - 2
            
            for (int i = 0; i < this->queueLength - 1; i++) {
                newQueue[i] = this->floorQueue[i + 1];
            }

            // same thing but in a different way
            //for (int i = 1; i < this->queueLength; i++) {
            //    newQueue[i - 1] = this->floorQueue[i];
            //}

            cout << "\nGoing to floor " << this->floorQueue[0];
            delete[] this->floorQueue;
            this->floorQueue = newQueue;
            this->queueLength--;
        }
    }

    string decodeExperience() {
        switch (this->experience) {
        case Experience::BEGINNER:
            return "beginner";
        case Experience::AMATEUR:
            return "amateur";
        case Experience::PROFESSIONAL:
            return "professional";
        default:
            return "unknown";
        }
    }

    static string decodeExperience(Experience experience) {
        switch (experience) {
        case Experience::BEGINNER:
            return "beginner";
        case Experience::AMATEUR:
             return "amateur";
        case Experience::PROFESSIONAL:
            return "professional";
        default:
            return "unknown";
        }
    }

    static int getNoOperators() {
        return ElevatorOperator::NO_OPERATORS;
    }

    void print() const {
        string exp;
        switch (this->experience) {
        case Experience::BEGINNER:
            exp = "beginner";
            break;
        case Experience::AMATEUR:
            exp = "amateur";
            break;
        case Experience::PROFESSIONAL:
            exp = "professional";
            break;
        default:
            exp = "unknown";
        }

        //cout << "\nname: " << name << "; id: " << id <<
        //    "; experience: " << exp << "; queue length: " << queueLength;

        cout << "\nname: " << name << "; id: " << id 
            << "; experience: " << decodeExperience(this->experience) 
            << "; queue length: " << queueLength;
        if (queueLength > 0) {
            cout << endl;
            for (int i = 0; i < queueLength; i++) {
                cout << floorQueue[i] << " ";
            }
            cout << endl;
        }
    }

    ~ElevatorOperator() {
        cout << "\n\tDestructor called";
        if (this->floorQueue != nullptr) {
            delete[] this->floorQueue;
        }
    }
};

int ElevatorOperator::NO_OPERATORS = 0;

int main()
{
    ElevatorOperator op1;
    op1.addFloor(13);

    ElevatorOperator op2("Marcel", Experience::PROFESSIONAL, 2);
    op2.addFloor(1);
    op2.addFloor(6);

    ElevatorOperator op3 = op2; // op3(op2)
    //op3 = op2;    // something else, it is operator=
    op1.print();
    op2.print();
    op3.print();

    cout << endl << ElevatorOperator::decodeExperience(Experience::AMATEUR);
    cout << endl << ElevatorOperator::getNoOperators();

    op2.removeFloor();
    op2.print();
    op2.removeFloor();
    op2.print();
    op2.removeFloor();

    return 0;
}
