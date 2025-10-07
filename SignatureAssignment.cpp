using namespace std;
#include <iostream>
#include <fstream>
#include <random>

const int ARRAY_SIZE = 1000;

int* createArray(int* length) {
    *length = ARRAY_SIZE;
    int* array = new int[ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % ARRAY_SIZE;
    }
    return array;
}

void writeBinary(int* values, int length) {
    string binarypath = "binary.dat";
    ofstream File(binarypath, ios::binary);
    
    if (!File) {
        cerr << "Error: Cannot open output file: " << binarypath << "\n";
        return;
    }

    File.write(reinterpret_cast<char*>(&length), sizeof(length));
    File.write(reinterpret_cast<char*>(values), sizeof(int) * length);
    
    File.close();
}

int* readBinary(int& length) {
    ifstream readFile("binary.dat", ios::binary);
        if (!readFile) {
            cerr << "Error: could not open file for reading.\n";
            return nullptr;
        }
        int* arr = new int[length];

        readFile.read(reinterpret_cast<char*>(arr), sizeof(int) * length);

        readFile.close();
        return arr;       
}

int main()
{
    //Declarations
    int length = 0;
    int newLength = 10;

    //Create Array
    int* integerArray = createArray(&length);
 
    //Write Binary 
    writeBinary(integerArray, length);
    delete[] integerArray;
    integerArray = nullptr;
    
    
    //Read Binary and Print
    int* PrintArr = readBinary(newLength);
    cout << "----------------------------First " << newLength << " Entries----------------------------" << endl;
    for (int i = 0; i < newLength; i++) {
        cout << PrintArr[i] << " "; 
    }
    //Delete Arrays
    delete[] PrintArr;
    PrintArr = nullptr;

}


