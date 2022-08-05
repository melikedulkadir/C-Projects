#include <vector>          // Including necessary "external" library files.
#include <sstream>
#include <string>
#include <fstream>
#include <stack>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

extern ifstream inputFileObj;

// Split string for input file
vector<string> splitInput (const string &s, char delim) {
    vector<string> result;
    istringstream ss (s);
    string item = " ";
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

// Print stack for output
void printStack(stack<string> stack,vector<string>& ZList,ofstream& output,int size){
    // If stack is empty
    if (stack.empty()){
        if(find(ZList.begin(), ZList.end(),"$")!= ZList.end()){         // Only Zlist contains $ we use this symbol
            output << "$";
            stack.push("$");
            if (size!=0) output<<",";
        }
        return;
    }
    string top = stack.top();
    stack.pop();
    printStack(stack,ZList,output,size);
    if (stack.size()==size-1) output << top;
    else output << top << ",";



}

// This function for transition operations
string transition(string& inputSymbol,string& starting_state,vector<vector<string>>& rules,stack<string>& stack,vector<string>& inStack,vector<string>& ZList,bool isFinal,ofstream& output){
    for (auto & rule : rules) {
        if (rule[0]== starting_state){
            if (rule[1]==inputSymbol){
                if ( rule[2]== "e" || rule[2]== "$"){
                    if (rule[4] != "$" && rule[4] != "e"){
                        stack.push(rule[4]);                                // The symbol in the rule pushed the stacked
                        inStack.push_back(rule[4]);
                    }
                    output<<starting_state<<","<< rule[1]<<","<<rule[2]<<" => "<<rule[3]<<","<<rule[4]<<" [STACK]:";
                    printStack(stack,ZList,output,stack.size());
                    output<<endl;
                    return rule[3];
                }
                else if (find(inStack.begin(), inStack.end(),rule[2])!= inStack.end()){
                    inStack.erase(find(inStack.begin(), inStack.end(), stack.top()));
                    stack.pop();
                    if (rule[4] != "$" && rule[4] != "e"){
                        stack.push(rule[4]);
                        inStack.push_back(rule[4]);
                    }
                    output<<starting_state<<","<< rule[1]<<","<<rule[2]<<" => "<<rule[3]<<","<<rule[4]<<" [STACK]:";
                    printStack(stack,ZList,output,stack.size());
                    output<<endl;
                    return rule[3];
                }
            }else if(rule[1] == "e"){                                           // The input symbol can be a symbol
                if ( rule[2]== "e" || rule[2]== "$"){                           // If the popped symbol is empty
                    if (rule[4] != "$" && rule[4] != "e"){
                        stack.push(rule[4]);
                        inStack.push_back(rule[4]);
                    }
                    output<<starting_state<<","<< rule[1]<<","<<rule[2]<<" => "<<rule[3]<<","<<rule[4]<<" [STACK]:";
                    printStack(stack,ZList,output,stack.size());
                    output<<endl;
                }
                else if (find(inStack.begin(), inStack.end(),rule[2])!= inStack.end()){     // If the popped symbol is in stack
                    inStack.erase(find(inStack.begin(), inStack.end(), stack.top()));
                    stack.pop();

                    if (rule[4] != "$" && rule[4] != "e"){
                        stack.push(rule[4]);
                        inStack.push_back(rule[4]);
                    }
                    output<<starting_state<<","<< rule[1]<<","<<rule[2]<<" => "<<rule[3]<<","<<rule[4]<<" [STACK]:";
                    printStack(stack,ZList,output,stack.size());
                    output<<endl;
                }


                if (isFinal){
                    return rule[3];
                }
                return transition(inputSymbol, rule[3], rules, stack, inStack,ZList, false,output);
            }
        }
    }
    return " ";
}

// This function for reading dpda input file
void readInput(string& inputSymbol,string& starting_state,vector<string>& final_states,vector<vector<string>>& rules,vector<string>& inStack,vector<string>& ZList,ofstream& output) {
    string fixed_state = starting_state;
    vector<string> tokens;
    string commandLine;
    while (getline(inputFileObj, commandLine)) {
        istringstream iss(commandLine);
        if (commandLine.empty()){
            string empty = "empty";
            tokens.push_back(empty);
        }
        string token;
        while (getline(iss, token)) {
            tokens.push_back(token);
        }
    }

    for (auto & token : tokens) {
        starting_state = fixed_state;
        if (token == "empty"){                                              // If the line is empty
            if (find(final_states.begin(), final_states.end(),starting_state)!= final_states.end()){
                output<<"ACCEPT\n"<<endl;
                continue;
            }else{
                output<<"REJECT\n"<<endl;
                continue;
            }
        }
        // Creating new stack for each line
        stack<string> stack;
        inStack.clear();
        vector<string> inputList = splitInput(token,',');
        for(auto & symbol: inputList) {
            inputSymbol = symbol;
            starting_state= transition(inputSymbol,starting_state,rules,stack,inStack,ZList, false,output);
            if (starting_state==" "){
                output<<"REJECT\n"<<endl;
                goto theEnd;
            }
        }
        // If the final state not in final_states list
        if(!(find(final_states.begin(), final_states.end(),starting_state)!= final_states.end())){
            string empty_string = "e";
            starting_state = transition(empty_string,starting_state,rules,stack,inStack,ZList, true,output);
            if(!(find(final_states.begin(), final_states.end(),starting_state)!= final_states.end())){
                output<<"REJECT\n"<<endl;
            }else if (!inStack.empty()){
                if (inStack.size()==1 && (find(inStack.begin(), inStack.end(),"$")!= inStack.end())){
                    output<<"ACCEPT\n"<<endl;
                }
                output<<"REJECT\n"<<endl;
            }else output<<"ACCEPT\n"<<endl;

        }else{
            if (!inStack.empty()){                                      // If the stack not empty
                if (inStack.size()==1 && (find(inStack.begin(), inStack.end(),"$")!= inStack.end())){
                    output<<"ACCEPT\n"<<endl;
                }
                output<<"REJECT\n"<<endl;
            }else output<<"ACCEPT\n"<<endl;
        }
    theEnd:
        continue;
    }
}

