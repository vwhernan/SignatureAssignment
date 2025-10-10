using namespace std;
#include <iostream>
#include <fstream>
#include <random>
#include <string>

const int ARRAY_SIZE = 1000;

class BinaryReader {
    int* arrInt;
    int arrSize;
    
    int* readValues(int& length) {
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

public:
    BinaryReader(const char filename) {
        readValues(arrSize);
    }
    
    
    int* getvalues() {
        return arrInt;
    }

    int getSize() {
        return arrSize;
    }

};

class Analyzer {
    int* arr;
    int size;

    int* cloneValues(int* original) {
        int* copy = original;
        return copy;
    }

public:

    Analyzer(int* a, int s) : arr(a), size(s) {  
        cloneValues(arr);
    }
    void deleteArr(int* a) {
        delete[] a;
        a = nullptr;
    }

    string analyze(int* array, int arraysize) {
        int mean = 0;
        int min = array[0];
        int max = array[0];

        for (int i = 0; i < arraysize; i++) {
            mean += array[i];
            if (array[i] < min) {
                min = array[i];
            }

            if (array[i] > max) {
                max = array[i];
            }
        }

        mean /= arraysize;
        string results = "The mean of the array is: " + std::to_string(mean); +"\nThe min is: " + std::to_string(min) + "\nThe max is: " + std::to_string(max);
        return results;

    }

};

//--------------------------------------------------------------------------------------
int* createArray(int* length) {
    *length = ARRAY_SIZE;
    int* array = new int[ARRAY_SIZE];
    srand(static_cast<unsigned int>(time(NULL))); //Seeds the random
    
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % ARRAY_SIZE;
    }
    return array;

}

void createBinaryFile() {

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
    
    
    /*Read Binary and Print
    int* PrintArr = readBinary(newLength);
    cout << "----------------------------First " << newLength << " Entries----------------------------" << endl;
    for (int i = 0; i < newLength; i++) {
        cout << PrintArr[i] << " "; 
    }
    //Delete Arrays
    delete[] PrintArr;
    PrintArr = nullptr;*/

}


