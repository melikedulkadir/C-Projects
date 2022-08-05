#include <iostream>
#include <vector>
#include <string>
#include "DpdaSystem.h"
#include "Operations.h"
using namespace std;

ifstream dpdaFileObj;
ifstream inputFileObj;

int main(int argc, char** argv) {
    dpdaFileObj.open(argv[1]);                                  // Open dpda file for dpda system
    inputFileObj.open(argv[2]);                                 // Open input file
    ofstream output;
    output.open(argv[3], ios::out);                             // Create output file
    vector<string> QList;                                          // Creating set of states
    vector<string> AList;                                          // Creating input alphabet
    vector<string> ZList;                                          // Creating stack alphabet
    vector<vector<string>> rules;                                  // Creating rules list for transition rule
    string starting_state;
    string inputSymbol;
    vector<string> final_states;                                    // Creating list for final_States
    vector<string> inStack;
    readCommands(QList,AList,ZList,rules,starting_state,final_states,output);
    readInput(inputSymbol,starting_state,final_states,rules,inStack,ZList,output);
    dpdaFileObj.close();                                            // Closing dpda file
    inputFileObj.close();                                           // Closing input file
    output.close();                                                 // Closing output file
    return 0;
}
