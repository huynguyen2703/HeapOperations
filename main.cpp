/*
 * Huy Quoc Nguyen : Lab 4 Heap Operations
 * CPSC 2430 : Data Structure course
*/


#include <iostream>
#include <fstream>      // fstream to readfile


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::getline;


const int HEAP_MAX_SIZE = 1000;

struct Pet {
    string name;
    int age{};

    Pet(const string &name, int &age) :    // Constructor for struct Pet
            name(name), age(age) {}
};

class PetHeap {
private:  // private members of class PetHeap
    Pet *petHeap[HEAP_MAX_SIZE]{};
    int size;

    void percolateUp(int index);

    void percolateDown(int index);

    void deleteMax();

    Pet *peekMax();

public:  // public members of class PetHeap
    PetHeap() {
        size = 0;
    }

    void insert(Pet *pet);

    Pet *adoptOldestPet();

    int numPets() const;

    void displayPets();

};


int main(int argc, char *argv[]) {
    if (argc != 2) { // check the number of arguments passed in terminal, in this case only *file name*
        cout << "Usage: lab4 <testFileName>" << endl;
        return 1;
    }
    string filename = argv[1];
    ifstream infile(filename);
    if (!infile.is_open()) {
        cout << "Unable to open file: " << filename
             << endl; // Print error message if unable to open the specified file.
        return 1;
    }


    PetHeap shelter; // Create a Shelter object to manage pets.
    string line;
    while (getline(infile, line)) {   // reading file line and store into line
        char choice = line[0];        // parsing first character from line to determine program action

        switch (choice) {
            case 'i' : {      // inserting a pet into the shelter
                string name;
                int age;
                infile >> name >> age;
                infile.ignore();
                shelter.insert(new Pet(name, age));
                break;
            }
            case 'a' : {       // adopting a pet from the shelter
                Pet *adopted = shelter.adoptOldestPet();
                if (adopted == nullptr) {
                    cout << "There are no pets in the shelter." << endl;

                } else {
                    cout << "Congratulations, you have adopted " << adopted->name << " age " <<
                         adopted->age << "." << endl;
                }
                break;
            }
            case 'n' : {       // displaying number of pets in the shelter
                cout << "The shelter heap has " << shelter.numPets() << " pets." << endl;
                break;
            }
            case 'd' : {      // displaying all pets in the shelter
                cout << "The pets in the heap in level order are:" << endl;
                shelter.displayPets();
                break;
            }
            default : {       // when option is not among those above
                cout << "Command is not recognized" << endl;
                break;
            }
        }
    }
    return 0;
}


void PetHeap::percolateUp(int index) {
    int parentIndex = (index - 1) / 2;
    if (index == 0 || petHeap[index]->age <= petHeap[parentIndex]->age) {
        return;  // Base case : current node reaches the root or its correct position is found.
    } else {
        if (parentIndex >= 0) {      // check if parent exists
            Pet *temp_pet = petHeap[index];
            petHeap[index] = petHeap[parentIndex];
            petHeap[parentIndex] = temp_pet;

            percolateUp(parentIndex);   // continue from parent
        }
    }

}

void PetHeap::percolateDown(int index) {
    int root = index;                 // [  start percolating down from root
    int leftTree = 2 * index + 1;     //    root is the value to get percolated down
    int rightTree = leftTree + 1;    // ]


    if (leftTree < size && petHeap[leftTree]->age > petHeap[root]->age) {
        root = leftTree;
    }
    if (rightTree < size && petHeap[rightTree]->age > petHeap[root]->age) {
        root = rightTree;
    }
    // after updating root, root no longer current index -> swapping is activated
    if (root != index) {
        Pet *temp_pet = petHeap[index];
        petHeap[index] = petHeap[root];
        petHeap[root] = temp_pet;

        percolateDown(root);  // percolate down from affected subtrees
    }


}


void PetHeap::deleteMax() {
    Pet *lastPet = petHeap[size - 1];
    petHeap[0] = lastPet;
    delete lastPet;
    size--;
    percolateDown(0);

}


Pet *PetHeap::peekMax() {
    if (size == 0) {
        return nullptr;
    } else {
        return petHeap[0];
    }
}

void PetHeap::insert(Pet *pet) {
    if (size < HEAP_MAX_SIZE) {
        petHeap[size] = pet;
        percolateUp(size);
        size += 1;
        cout << "Adding " << pet->name << ", age " << pet->age << endl;
    } else {
        cout << "Alert! Going over max size of heap!" << endl;
    }
}

Pet *PetHeap::adoptOldestPet() {
    Pet *adoptedPet = peekMax();
    if (size > 0) {
        deleteMax();
        return adoptedPet;
    } else {
        return nullptr;
    }
}


int PetHeap::numPets() const {
    return size;
}

void PetHeap::displayPets() {
    if (size == 0) {
        cout << "There are no pets in the shelter" << endl;
        return;
    } else {
        for (int i = 0; i < size; i++) {
            cout << petHeap[i]->name << " " << petHeap[i]->age << endl;
        }
    }
}



