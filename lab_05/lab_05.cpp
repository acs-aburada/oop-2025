#include <iostream>

using std::cout;
using std::endl;
using std::string;

enum Team {
    RED_BULL, // 0
    FERRARI, // 1
    MCLAREN // 2
};

class FormulaOneRacer {
    // by default attributes are private
    unsigned int age = 18;
    string name = "John Doe";
    Team team = Team::RED_BULL;
    unsigned int raceCount = 0; //no. of races they completed
    float* raceTimes = nullptr;

    static int NUMBER_RACERS;

public:
    FormulaOneRacer() {
        cout << "\nNo parameter c-tor";
        NUMBER_RACERS++;
    }

    // custom c-tor
    FormulaOneRacer(const int age, const string name, const Team team) {
        cout << "\nCustomer params c-tor";

        /*this->age = age;
        this->name = name;
        this->team = team;*/

        // instead of assigning in the c-tor, user setters
        // setters always should have validations
        setAge(age);
        setName(name);
        setTeam(team);

        NUMBER_RACERS++;
    }

    // age
    void setAge(const int age) {
        if (age < 18 || age > 50) {
            throw "Invalid age value.";
        }
        this->age = age;
    }

    unsigned int getAge() const {   // const -> ensures we don't modify any class attributes
        return this->age;
    }

    // name
    void setName(const string name) {
        if (name.empty()) {
            throw "Invalid name value.";
        }
        this->name = name;
    }

    string getName() const {
        return this->name;
    }

    // team
    void setTeam(const Team team) {
        this->team = team;
    }

    Team getTeam() const {
        return this->team;
    }

    // race times
    // getRaceTime(int) -> get the race time at given index
    // addRaceTime(float) -> expand the array of race times by one with new value
    // setRaceTimes(float*, int) -> set the array of race times through deep copy to given array
    // getRaceTimes() -> get the entire array of race times
    // TODO: setRaceCount -> set the attribute AND allocate memory
    // we can also consider that setRaceCount is only modified when the array is also changed
    // thus omitting this method altogether

    // const float* -> pointer to const float
    // float* const -> const pointer to float
    void setRaceTimes(float* const raceTimes, const int raceCount) {
        // check if there are races already
        if (this->raceTimes) {
            delete[] this->raceTimes;
        }

        this->raceCount = raceCount;
        this->raceTimes = new float[this->raceCount]{ 0.0F };

        // deep copy
        for (int i = 0; i < raceCount; i++) {
            this->raceTimes[i] = raceTimes[i];
        }
    }

    float* getRaceTimes() const {
        // DO NOT DO THIS
        //return this->raceTimes;

        if (this->raceCount == 0) {
            return nullptr;
        }

        // deep copy
        float* temp = new float[this->raceCount];
        for (int i = 0; i < this->raceCount; i++) {
            temp[i] = this->raceTimes[i];
        }

        return temp;
    }

    float getRaceTime(const int index) const {
        // validation
        if (index < 0 || index >= this->raceCount) {
            throw "Invalid index for getRaceTime";
        }
        if (this->raceCount == 0 && index == 0) {
            return 0.0F;
        }
        return this->raceTimes[index];
    }

    int getRaceCounter() const {
        return this->raceCount;
    }

    void addRaceTime(const float newTime) {
        // appending at the end of the array newTime
        if (this->raceCount == 0) {
            // if we had no prior races and the array was empty
            // it means that we make a new array with only one element = newTime
            this->raceTimes = new float[++this->raceCount] { newTime };
        }
        else {
            // if we had races already, we need to expand by one the array
            float* temp = new float[(++this->raceCount)](); // () -> 0 for all values

            // if the counter was 5, now it is 6
            // the original array was from index 0 to 4
            for (int i = 0; i < this->raceCount - 1; i++) {
                temp[i] = this->raceTimes[i];
            }
            // at this moment in temp we have all the elements that exist in this->raceTimes
            // we need to do add the new element value
            temp[this->raceCount - 1] = newTime;

            // temp -> the array expanded by 1
            // this->raceTimes -> the previous array
            // we need to deallocate the smaller array
            delete[] this->raceTimes;
            this->raceTimes = temp;
        }
    }

    // number_racers
    int getNumberRacers() {
        return FormulaOneRacer::NUMBER_RACERS;
    }

    static int getNumberRacersStatic() {
        return FormulaOneRacer::NUMBER_RACERS;
    }

    // print
    void printRacer() const {
        // determine the team
        string team;
        switch (this->team) {
        case Team::RED_BULL:
            team = "Red Bull";
            break;
        case Team::MCLAREN:
            team = "McLaren";
            break;
        case Team::FERRARI:
            team = "Ferrari";
            break;
        default:
            team = "unknown";
        }

        cout << "\nRacer: " << this->name << "; age: " << this->age
            << "; team: " << team << endl;
        if (this->raceCount > 0) {
            for (int i = 0; i < this->raceCount; i++) {
                cout << this->raceTimes[i] << "s ";
            }
        }
        cout << endl;
    }

    ~FormulaOneRacer() {
        cout << "\nDestructor";
        if (this->raceTimes)
            delete[] this->raceTimes;
    }
};

int FormulaOneRacer::NUMBER_RACERS = 0;

int main()
{
    FormulaOneRacer racer1;
    cout << "\nracer counter: " << racer1.getNumberRacers();
    cout << "\nracer counter: " << FormulaOneRacer::getNumberRacersStatic();
    
    racer1.printRacer();

    racer1.addRaceTime(12.1);
    racer1.addRaceTime(9.3);
    racer1.addRaceTime(7.13);
    racer1.printRacer();

    FormulaOneRacer* racer2 = new FormulaOneRacer(23, "Jane Doe", Team::MCLAREN);
    racer2->addRaceTime(9.43);
    racer2->addRaceTime(0.1);
    racer2->printRacer();

    FormulaOneRacer racer3(40, "Hewis Lamilton", Team::FERRARI);

    unsigned int size = 10;
    float* array = new float[size] { 0.0F };
    for (int i = 0; i < size; i++) {
        array[i] = (i * 7.0 + 2) / 5 + 0.1; // just a random formula
    }
    racer3.setRaceTimes(array, size);
    racer3.printRacer();

    float* array2 = racer3.getRaceTimes();
    cout << ((array2 == array) ? "\nshallow copy happened\n" : "\ndeep copy happened\n");

    cout << "\nracer2's second race time: " << racer3.getRaceTime(1);
    //cout << "\nracer2's 20th race time: " << racer3.getRaceTime(20); // will throw runtime exception

    delete racer2;
    racer2 = nullptr;

    delete[] array;
    array = nullptr;

    delete[] array2;
    array2 = nullptr;

    return 0;
}

