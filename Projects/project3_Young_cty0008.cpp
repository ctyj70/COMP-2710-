/**
* project3_Young_cty0008
* 
* @author CJ Young
* 
* cty0008
* COMP 2710 Project 3
* Compiled in Visual Studio 2019
* 
*/

#include <fstream>
#include <iostream>
using namespace std;
const int Max = 100;

// Reads inputted files in index of array.
int readfile(int inputArray[], ifstream& instream) {

    int index = 0;

    instream >> inputArray[index];

    while (!instream.eof()) {

        index++;
        instream >> inputArray[index];
    }

    return index;
}

// Merges arrays.
void merge(int array[], int lo, int mu, int rho) {

    int i;
    int h;
    int o;

    int numb_1 = mu - lo + 1;
    int numb_2 = rho - mu;

    int* Liq = new int[numb_1];
    int* Rum = new int[numb_2];


    for (i = 0; i < numb_1; i++) {

        Liq[i] = array[lo + i];
    }

    for (h = 0; h < numb_2; h++) {

        Rum[h] = array[mu + 1 + h];
    }

    i = 0;
    h = 0;
    o = lo;
    while (i < numb_1 && h < numb_2) {


        if (Liq[i] <= Rum[h]) {

            array[o] = Liq[i];
            i++;
        }
        else {

            array[o] = Rum[h];
            h++;
        }

        o++;
    }

    while (i < numb_1) {
        array[o] = Liq[i];
        i++;
        o++;
    }

    while (h < numb_2) {
        array[o] = Rum[h];
        h++;
        o++;
    }

    delete[] Liq;
    delete[] Rum;
}

// Merges/Sorts arrays.
void mergeAndSort(int array[], int lo, int rho)
{
    if (lo < rho) {

        int mu = lo + (rho - lo) / 2;

        mergeAndSort(array, lo, mu);

        mergeAndSort(array, mu + 1, rho);

        merge(array, lo, mu, rho);

    }

}

// Combines and Sorts Arrays for files.
int combineAndSort(int arr_01[], int arr_01Size, int arr_02[], int arr_02Size, int arrayOut[]) {

    int arrayOut_Size = arr_01Size + arr_02Size;

    for (int i = 0; i < arr_01Size; i++) {

        arrayOut[i] = arr_01[i];
    }
    for (int i = 0; i < arr_02Size; i++) {

        arrayOut[i + arr_01Size] = arr_02[i];
    }
    mergeAndSort(arrayOut, 0, arrayOut_Size - 1);

    return arrayOut_Size;
}

//Writes/Overwrites files.
void newFile(int arrayOut[], int arrayOut_Size) {
    ofstream outstream;
    string outputFileName;

    cout << "Enter the output file name: ";
    cin >> outputFileName;

    outstream.open((char*)outputFileName.c_str());

    for (int i = 0; i < arrayOut_Size; i++) {

        outstream << arrayOut[i] << "\n";
    }
    outstream.close();

    cout << "*** Please check the new file - " << outputFileName << " ***\n";

}

// Main function of program
int main() {

    int arr_01[Max];
    int arr_01Size;
    int arr_02[Max];
    int arr_02Size;
    cout << endl << "*** Welcome to CJ's sorting program ***\n";
    ifstream instream;
    string fileName;
    bool validFile = false;
    while (!validFile) {

        cout << "Enter the first input file name: ";
        cin >> fileName;
        instream.open((char*)fileName.c_str());
        validFile = instream.good();
        if (!validFile) {
            cout << "Error: Invalid filename, please try again\n";
            cout << endl;
        }
    }

    arr_01Size = readfile(arr_01, instream);
    instream.close();

    cout << "The list of " << arr_01Size << " numbers in file " << fileName << " is:\n";

    for (int i = 0; i < arr_01Size; i++) {

        cout << arr_01[i] << "\n";

    }
    cout << endl;

    string fileName2;

    bool validFile2 = false;

    while (!validFile2) {

        cout << "Enter the second input file name: ";
        cin >> fileName2;

        instream.open((char*)fileName2.c_str());
        validFile2 = instream.good();
        if (!validFile2) {

            cout << "Error: Invalid filename, please try again\n";
            cout << endl;

        }

    }

    arr_02Size = readfile(arr_02, instream);
    instream.close();

    cout << "The list of " << arr_02Size << " numbers in file " << fileName2 << " is:\n";

    for (int i = 0; i < arr_02Size; i++) {

        cout << arr_02[i] << "\n";
    }

    cout << endl;

    int arrayOut[Max];
    int arrayOut_Size = combineAndSort(arr_01, arr_01Size, arr_02, arr_02Size, arrayOut);

    cout << "The sorted list of " << arrayOut_Size << " numbers is:";
    for (int i = 0; i < arrayOut_Size; i++) {

        cout << " " << arrayOut[i];

    }
    cout << endl;

    newFile(arrayOut, arrayOut_Size);

    cout << "*** Goodbye. ***" << endl;

    return 0;
}