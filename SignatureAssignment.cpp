using namespace std;
#include <iostream>
#include <fstream>
#include <random>

const int ARRAY_SIZE = 1000;

int* createArray(int* length) {
    *length = ARRAY_SIZE;
    int* array = new int[ARRAY_SIZE];

    for (int i = 0; i < 1000; i++) {
        array[i] = rand() % 1000;
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

    File << "The Length of the Array is: " << length << "\n";
    for (int i = 0; i < length; i++) {
        File << values[i] << " ";
    }
    File.close();
}

int* readBinary(int& length) {
    return 0;
}

int main()
{
    //Declarations
    int length = 0;
   
    //Create Array
    int* integerArray = createArray(&length);
 
    //Write Binary 
    writeBinary(integerArray, length);
    
    //Read Binary and Print

    //Delete Arrays
    
}


