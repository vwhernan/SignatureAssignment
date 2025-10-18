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
private:  //Only accessible by Analyzer
    //Copys the array and returns a Copys
    int* cloneValues(int* original, int s) {
        int* copy = new int[s];
        for (int i = 0; i < s; ++i)
            copy[i] = original[i];
        return copy;
    }
protected: //Accessible by all derived classes
    int* arr;
    int size;

public:

    Analyzer(int* a, int s) : arr(a), size(s) { cloneValues(arr, size); }
    ~Analyzer() {}
    void deleteArr() {
        delete[] arr;
        arr = nullptr;
    }

    virtual string  analyze() = 0;
};

class DuplicatesAnalyzer :public Analyzer {
    public:
    DuplicatesAnalyzer(int* a, int s) : Analyzer(a, s) {}
    string analyze() override {
        int counter = 0;
        int compareNum;
        int NestedNum;

        //Counts all duplicate values. NOT unique values
        for (int i = 0; i < size; i++) {
            compareNum = arr[i];

            for (int j = i + 1; j < size; j++) {
                NestedNum = arr[j];

                if (compareNum == NestedNum) {
                    counter++;
                    break;
                }
            }
        }
        return to_string(counter);
    }
};

class MissingAnalyzer : public Analyzer {
    MissingAnalyzer(int* a, int s) : Analyzer(a, s) {}
    string analyze() override {
        
        int testNum= 0;
        
        while (testNum < size) {
           
            test
        }
    
    }
};

class StatisticsAnalyzer : public Analyzer {

public:
    StatisticsAnalyzer(int* a, int s) : Analyzer(a, s) {}
    string analyze() override {
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
        string results = "The mean of the array is: " + to_string(mean) + "\nThe min is: " + to_string(min) + "\nThe max is: " + to_string(max);
        return results;

    }
};


int main(){
    //Set string path
    string fileName = "binary.dat";

    //Creates the random intedger array and saves to a binary file
    BinaryReader File(fileName);
    File.createBinaryFile(fileName);

    //Creates Analyzer Objects
    DuplicatesAnalyzer DupAnalyzer(File.getvalues(), File.getSize());
    StatisticsAnalyzer StatAnalyzer(File.getvalues(), File.getSize());
    
    //Clear below comment to read array data
    //test.printData();

    //Gets the min max and mean
    cout << StatAnalyzer.analyze();

    //Gets Dublpicates
    cout << DupAnalyzer.analyze();

    //deletes the array from memory
    DupAnalyzer.deleteArr();
    
    return 0;
}
