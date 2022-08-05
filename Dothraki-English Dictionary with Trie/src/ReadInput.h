//
// Created by Melike on 29.12.2021.
//
#include <vector>          // Including necessary "external" library files.
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>
#include "Trie.h"

using namespace std;
extern ifstream inputFileObj;

// split function for commands in the input file
vector<string> split (const string &s, char delim) {
    vector<string> result;
    istringstream ss (s);
    string item ;
    while (getline (ss, item, delim)) {
        result.push_back (item);
    }
    return result;
}

// operation function for execute commands
void operation(vector<string>& tokens,string& key,string& value,ofstream& output){
    struct TrieNode *root = getNode();
    for (int i = 0; i < tokens.size(); ++i) {
        if (tokens[i][0] == 'i'){                                   // If command is insert
            int size = tokens[i].size();
            string pair = tokens[i].substr(7,size-8);
            vector<string> key_value = split(pair,',');
            key = key_value[0] ;
            value = key_value[1];

            string search_result = search(root,key);

            if((search_result=="no record")||(search_result=="incorrect Dothraki word")||(search_result=="not enough Dothraki word")){
                insert(root,key,value);
                output<<"\""<<key<<"\""<<" was added"<<endl;
            }
            else if(search_result==value){
                output<<"\""<<key<<"\""<<" already exist"<<endl;
            }
            else{
                insert(root,key,value);
                output<<"\""<<key<<"\""<<" was updated"<<endl;
            }

        }else if (tokens[i][0] == 's'){                             // If command is search
            int size = tokens[i].size();
            string key = tokens[i].substr(7,size-8);
            string search_result = search(root,key);
            if (search_result=="no record" || search_result=="incorrect Dothraki word" || search_result=="not enough Dothraki word")
                output<<"\""<<search_result<<"\""<<endl;
            else
                output<<"\"The English equivalent is "<<search_result<<"\""<<endl;

        }else if (tokens[i][0] == 'd'){                             // If command is delete
            int size = tokens[i].size();
            string key = tokens[i].substr(7,size-8);
            output<<deletion(root,key)<<endl;

        }else if (tokens[i][0] == 'l'){                             // If command is list
            string word;
            string prefix;
            int counter;
            int prefixCounter = 0;
            listing(root,root,word,prefix,prefixCounter, true, false,output);
        }
    }
}

// readInput function for reading input.txt file
void readInput(string& key,string& value,ofstream& output) {
    vector<string> tokens;
    string commandLine;
    while (getline(inputFileObj, commandLine)){
        istringstream iss(commandLine);
        string token;
        while (getline(iss, token)) {
            tokens.push_back(token);
        }
    }
    operation(tokens,key,value,output);
}


