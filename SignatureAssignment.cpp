using namespace std;
#include <iostream>
#include <fstream>
#include <random>
#include <string>


const int ARRAY_SIZE = 1000;

class BinaryReader {
    int* arrInt;  //A pointer to hold integer array from file
    int arrSize;  
    

    void readValues(const string& filename) {
        ifstream readFile(filename, ios::binary);
        if (!readFile) {
            cerr << "Error: could not open file for reading.\n";
            arrInt = nullptr;
            arrSize = 0;
            return;
        }

        readFile.read(reinterpret_cast<char*>(&arrSize), sizeof(arrSize)); //gets size of the array
        arrInt = new int[arrSize]; //Dynamically allocates memory for the array
        readFile.read(reinterpret_cast<char*>(arrInt), sizeof(int) * arrSize); //Reads the actual array of integers into arrInt
    }

public:
    BinaryReader(const string& filename) {
        readValues(filename); //immediatly reads data from file
    }
    
    //Creates an array of 1000 integers (0-999).  Saves it to binary.dat.  Then deallocates the temp array.  USES writeBinary()
    void createBinaryFile(string filename) {       
        int* arr = new int[ARRAY_SIZE];
        srand(static_cast<unsigned int>(time(NULL)));
        for (int i = 0; i < ARRAY_SIZE; i++) arr[i] = rand() % ARRAY_SIZE;

        writeBinary(arr, ARRAY_SIZE, filename);
        delete[] arr;
    }

    //Opens file, writes size and array to file.   USED IN createBinaryFile() FUNCTION TO WRITE RANDOM INTO FILE
    void writeBinary(int* values, int length, string& path) {

        ofstream File(path, ios::binary);

        if (!File) {
            cerr << "Error: Cannot open output file: " << path << "\n";
            return;
        }

        File.write(reinterpret_cast<char*>(&length), sizeof(length));
        File.write(reinterpret_cast<char*>(values), sizeof(int) * length);

        File.close();
    }
    
    int* getvalues() {
        return arrInt;
    }

    int getSize() {
        return arrSize;
    }

    //bonus method for testing
    void printData() {
        
        cout << "---------------------------------------------------------------------- " <<  endl;
        cout << "The size of the array is " << arrSize << endl;
        for (int i = 0; i < arrSize; i++) {
            cout << arrInt[i] << " ";
        }
        cout << "\n---------------------------------------------------------------------- " << endl;
    }

};

class Analyzer {
    int* arr;
    int size;

    int* cloneValues(int* original, int s) {
        int* copy = new int[s];
        for (int i = 0; i < s; ++i)
            copy[i] = original[i];
        return copy;
    }

public:

    Analyzer(int* a, int s) : arr(a), size(s) {  
        cloneValues(arr, size);
    }
    void deleteArr() {
        delete[] arr;
        arr = nullptr;
    }

    string analyze() {
        int mean = 0;
        int min = arr[0];
        int max = arr[0];

        for (int i = 0; i < size; i++) {
            mean += arr[i];
            if (arr[i] < min) {
                min = arr[i];
            }

            if (arr[i] > max) {
                max = arr[i];
            }
        }

        mean /= size;
        string results = "The mean of the array is: " + to_string(mean) +"\nThe min is: " + to_string(min) + "\nThe max is: " + to_string(max);
        return results;

    }

};


int main(){
    string fileName = "binary.dat";
    BinaryReader test(fileName);
    test.createBinaryFile(fileName);
    
    //Clear below comment to read array data
    //test.printData();

   Analyzer Analyze(test.getvalues(), test.getSize());
   cout << Analyze.analyze();

   Analyze.deleteArr();
   return 0;
}
