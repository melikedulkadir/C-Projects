#include <iostream>
#include "ReadInput.h"
using namespace std;
ifstream inputFileObj;

int main(int argc, char** argv) {
    string key;                                 // Creating key string for Dothraki word
    string value;                               // Creating value string for English word
    ofstream output;                            // Creating output file
    inputFileObj.open(argv[1]);              // Opening input file
    output.open(argv[2], ios::out);          // Opening output file
    readInput(key,value,output);      // Reading input.text with the read Input function in 'Read Input.h'
    inputFileObj.close();                       // Closing files
    output.close();




}
