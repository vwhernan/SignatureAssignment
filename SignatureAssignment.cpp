//Vincent Hernandez, Clint Woods, Jeremy Sherman

using namespace std;
#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <algorithm>


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

    ~BinaryReader() {
        delete[] arrInt; // Deletes the data read from the file
        arrInt = nullptr;
    }
    //Creates an array of 1000 integers (0-999).  Saves it to binary.dat.  Then deallocates the temp array.  USES writeBinary()
    static void createBinaryFile(string filename) {
        int* arr = new int[ARRAY_SIZE];
        srand(static_cast<unsigned int>(time(NULL)));
        for (int i = 0; i < ARRAY_SIZE; i++) arr[i] = rand() % ARRAY_SIZE;

        writeBinary(arr, ARRAY_SIZE, filename);
        delete[] arr;
    }

    //Opens file, writes size and array to file.   USED IN createBinaryFile() FUNCTION TO WRITE RANDOM INTO FILE
    static void writeBinary(int* values, int length, string& path) {

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

        cout << "The size of the array is " << arrSize << endl;
        cout << "------------------------------------------------------------------------- " << endl;
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

    Analyzer(int* a, int s) : size(s) {
        // 1. Allocate space for the copy
        arr = new int[size];
        // 2. Copy the values
        for (int i = 0; i < s; ++i)
            arr[i] = a[i];
    }

    ~Analyzer() {
        delete[] arr;
        arr = nullptr;
    }


    virtual string  analyze() = 0;
};

class SearchAnalyzer : public Analyzer {
public:

    SearchAnalyzer(int* arr, int size) : Analyzer(arr, size) {
        selection_sort(arr, size);
    }

    string analyze() override {
        int random[100];
        int count = 0;
        
        for (int i = 0; i < 100; i++) random[i] = rand() % 1000;

        for (int i = 0; i < 100; i++) {
            if (binary_search(arr, random[i], size)) { count++; }
        }
        string results = "There were " + to_string(count) + " out of 100 random values found";
        return results;
    }

    bool binary_search_recursive(int* arr, int key, int start, int end) {
        if (end < start) {
            return false;
        }
        int mid = (start + end) / 2;

        if (arr[mid] == key) {
            return true;
        }
        if (arr[mid] < key)
            return binary_search_recursive(arr, key, mid + 1, end);
        else
            return binary_search_recursive(arr, key, start, mid - 1);
    }

    bool binary_search(int* arr, int key, int size) {
        return binary_search_recursive(arr, key, 0, size);
    }

    static void selection_sort(int* arr, int size) {
        // Outer loop iterates through all elements except the last one.
        for (int i = 0; i < size - 1; ++i) {
            int currentMin = i;

            // Inner loop finds the minimum element in the *unsorted* portion
            for (int j = i + 1; j < size; ++j) {
                // Check if the current element arr[j] is smaller than the current minimum
                if (arr[j] < arr[currentMin]) {
                    currentMin = j;
                }
            }

            // If the minimum element found is not the one we started with, swap them.
            if (currentMin != i) {
                std::swap(arr[i], arr[currentMin]);
            }
        }
    }
};

class StatisticsAnalyzer : public Analyzer {

public:
    StatisticsAnalyzer(int* arr, int size) : Analyzer(arr, size) {
        SearchAnalyzer::selection_sort(arr, size);
    }
    string analyze() override {
        double sum = 0;
        for (int i = 0; i < size; ++i) {
            sum += arr[i];
        }
        
        int min = 0;
        int max = 0;
        double mean = static_cast<double>(sum) / size;
        min = arr[0];
        max = arr[size - 1]; 
    
        string results = "The mean of the array is: " + to_string(mean) + "\nThe min is: " + to_string(min) + "\nThe max is: " + to_string(max);
        return results;

    }
};

class DuplicatesAnalyzer : public Analyzer
{
public:
    DuplicatesAnalyzer(int* a, int s) : Analyzer(a, s) {}

    string analyze() override
    {
        if (size == 0) return "The total count of duplicates: 0";

        // Group the identical values
        std::sort(arr, arr + size);

        int NumberOfDuplicates = 0;

        // Count each value in the array that appears more than once
        for (int index = 1; index < size; )
        {
            if (arr[index] == arr[index - 1])
            {
                ++NumberOfDuplicates;

                // Skip the remaining duplicate group to count only once
                int val = arr[index];
                while (index < size && arr[index] == val)
                {
                    ++index;
                }
            }
            else
            {
                ++index;
            }
        }

        return "Total count of duplicates: " + std::to_string(NumberOfDuplicates);
    }
};

class MissingAnalyzer : public Analyzer {
public:
    MissingAnalyzer(int* a, int s) : Analyzer(a, s) {}
    string analyze() override {

        int counter = 0;
        int compareNum;
        int NestedNum;


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

        return "Total Missing Numbers: " + to_string(counter);
    }

};


int main() {
    //Set string path
    string fileName = "binary.dat";

    //Creates the random intedger array and saves to a binary file

    BinaryReader::createBinaryFile(fileName);

    BinaryReader File(fileName);
    //Creates Analyzer Objects
    SearchAnalyzer SearchA(File.getvalues(), File.getSize());
    DuplicatesAnalyzer DupAnalyzer(File.getvalues(), File.getSize());
    MissingAnalyzer MissAnalyzer(File.getvalues(), File.getSize());
    StatisticsAnalyzer StatAnalyzer(File.getvalues(), File.getSize());


    //Prints Arrays before and after sort
    cout << "Before Sort" << endl;
    File.printData();
    SearchA.selection_sort(File.getvalues(), File.getSize());
    
    cout << "After Sort" << endl;
    File.printData();

    //Gets the min max and mean
    cout << StatAnalyzer.analyze() << endl;

    //Get Median, Mode
    
    
    //Gets Dublpicates
    cout << DupAnalyzer.analyze() << endl;

    //Gets Missing Numbers
    cout << MissAnalyzer.analyze() << endl;

    //Get total random values
    cout << SearchA.analyze() << endl;

    return 0;
}


