#include <vector>          // Including necessary "external" library files.
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

extern ifstream dpdaFileObj;

// Function for splitting string in dpda input file
vector<string> split (const string &s, char delim) {
    vector<string> result;
    istringstream ss (s);
    string item = " ";
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    result[0] = result[0].substr(2,result[0].size()-2);

    return result;
}

// Function for reading dpda input file
void readCommands(vector<string>& QList,vector<string>& AList,vector<string>& ZList,vector<vector<string>>& rules,string& starting_state,vector<string>& final_states,ofstream& output) {
    vector<string> tokens;
    string commandLine;
    while (getline(dpdaFileObj, commandLine)) {
        istringstream iss(commandLine);
        string token= " ";

        while (getline(iss, token,'\n')) {
            tokens.push_back(token);
        }
    }
    for (auto & token : tokens) {
        if (token[0]== 'Q'){                                                // If dpda input file line is states
            QList = split(token,',');
            for (auto & state : QList) {
                if (state.find("=>") != string::npos) {
                    starting_state = state.substr(state.find("=>")+4,state.size()-2);
                    state = state.substr(0,state.find("=>")-1);

                    if (starting_state.back()==')'){
                        starting_state = starting_state.substr(0,starting_state.size()-1);
                    }
                }else if (state[0] =='['){
                    state = state.substr(1,state.size()-2);
                    final_states.push_back(state);
                }
            }
        }else if (token[0]== 'A'){                                           // If dpda input file line is input alphabet
            AList = split(token,',');

        }else if (token[0]== 'Z'){                                           // If dpda input file line is stack alphabet
            ZList = split(token,',');

        }else if (token[0]== 'T'){                                          // If dpda input file line is rules
            vector<string> TList;
            TList = split(token,',');
            rules.push_back(TList);
        }
    }

    // Checking input alphabet, stack alphabet, states is true or not
    for (auto & rule : rules) {
        if (!(find(QList.begin(), QList.end(),rule[0])!= QList.end())){
            output<<"Error [1]:DPDA description is invalid!"<<endl;
            exit(0);
        }
        if (!(find(AList.begin(), AList.end(),rule[1])!= AList.end())){
            if (rule[1]!="e"){
                output<<"Error [1]:DPDA description is invalid!"<<endl;
                exit(0);
            }
        }
        if (!(find(ZList.begin(), ZList.end(),rule[2])!= ZList.end())){
            if (rule[2]!="e"){
                output<<"Error [1]:DPDA description is invalid!"<<endl;
                exit(0);
            }
        }
        if (!(find(QList.begin(), QList.end(),rule[3])!= QList.end())){
            output<<"Error [1]:DPDA description is invalid!"<<endl;
            exit(0);
        }
        if (!(find(ZList.begin(), ZList.end(),rule[4])!= ZList.end())){
            if (rule[4]!="e"){
                output<<"Error [1]:DPDA description is invalid!"<<endl;
                exit(0);
            }
        }
    }
}

