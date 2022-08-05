//
// Created by Melike on 28.12.2021.
//

#ifndef ASSIG4_TRIE_H
#define ASSIG4_TRIE_H
#include <bits/stdc++.h>

#include <utility>
using namespace std;
const int ALPHABET_SIZE = 26;

// trie node
struct TrieNode
{
    struct TrieNode *next[ALPHABET_SIZE]{};
    char key{};
    string value;
};

// Returning new trie node
struct TrieNode *getNode()
{
    auto *Nodeptr =  new TrieNode;
    Nodeptr->value = " ";
    Nodeptr->key = ' ';
    for (auto & i : Nodeptr->next)
        i = nullptr;

    return Nodeptr;
}

// insert function for insert command
void insert(struct TrieNode *root, string& key,string& value)
{
    struct TrieNode *currentptr = root;

    for (int i = 0; i < key.length(); i++){
        int index = key[i] - 'a';
        if (!currentptr->next[index]){
            currentptr->next[index] = getNode();
            currentptr->next[index]->key = key[i];
        }
        if (i==key.length()-1){                             // Appending value at the end of the key
            currentptr->next[index]->value = value;
        }
        currentptr = currentptr->next[index];
    }

}

// Search function for search command
string search(struct TrieNode *root, string& key)
{
    struct TrieNode *currentptr = root;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!currentptr->next[index]){
            if (currentptr==root){                          // If the first character of the key is not referenced by the root node
                return "no record";
            }
            return "incorrect Dothraki word";               // If the first n character of the k exists on the tree, but the remainder is not
        }

        currentptr = currentptr->next[index];
    }
    if (currentptr->value==" "){                            // If all characters of the key exist on the tree, but the last character has no English equivalent
        return "not enough Dothraki word";
    }
    return (currentptr->value);
}

// Function that determines whether there is a branch and the number of branches
bool isBranchExist(TrieNode* root,TrieNode* last,int& counter){
    counter = 0;
    if (last==root){
        return true;
    }
    for (auto & i : last->next) {
        if (i){
            counter++;
        }
    }
    for (int i = 0; i < ALPHABET_SIZE; i++){
        if (last==NULL){
            return false;
        }
        if (last->next[i]){
            return true;
        }
    }
    return false;
}

// Function for finding the TrieNode* pointer
TrieNode* findNode(TrieNode* root,TrieNode* last,string& key){
    struct TrieNode *currentptr = root;
    if (last==root){
        return root;
    }
    for (char i : key)
    {
        int index = i - 'a';
        if (currentptr->next[index]==last){
            return currentptr;
        }
        currentptr = currentptr->next[index];
    }
    return root;
}

// deletion function for delete command
string deletion(TrieNode* root, string& key){
    struct TrieNode *currentptr = root;
    int counter;
    for (int i = 0; i < key.length(); i++)
    {
        int index = key[i] - 'a';
        if (!currentptr->next[index]){
            if (currentptr==root){
                return "\"no record\"";
            }
            return "\"incorrect Dothraki word\"";
        }

        currentptr = currentptr->next[index];
    }
    if (currentptr->value==" "){
        return "\"not enough Dothraki word\"";
    }
    // deletion while a char has another child
    while(!isBranchExist(root,currentptr,counter)){
        struct TrieNode *temporaryLast = currentptr;
        int index = currentptr->key - 'a';
        currentptr = findNode(root,temporaryLast,key);
        delete (currentptr->next[index]);
        currentptr->next[index] = NULL;

    }
    currentptr->value = " ";
    return "\""+key+"\""+" deletion is successful";
}

//listing function for list command
void listing(TrieNode* root,TrieNode* searchNode,string& word,string& prefix,int& prefixCounter,bool isFirst,bool isAdded,ofstream& output){
    struct TrieNode *currentptr;
    int counter;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (isFirst){
            prefix.clear();
            word.clear();
            prefixCounter = 0;
        }
        currentptr = root->next[i];
        // If the next pointer has a char
        if (root->next[i]){
            word.push_back(root->next[i]->key);
            bool flag = isBranchExist(root,currentptr,counter);
            // If branch exist but there is no value
            if (flag && (currentptr->value == " ")){
                if (counter>=2){
                    for (int i=0; i<prefixCounter;i++){
                        output<<"\t";
                    }
                        prefix  = word;
                        prefixCounter++;
                        output<<"-"<<prefix<<endl;
                }
                listing(root->next[i],searchNode,word,prefix,prefixCounter, false,false,output);
            }
            // If the branch not exist and there is a value, the leaf
            else if (!flag && (currentptr->value != " ")){
                for (int i=0; i<prefixCounter;i++)
                    output<<"\t";
                output<<"-"<<word<<"("<<search(searchNode,word)<<")"<<endl;
                word.clear();
            }
            // If the branch exist and there is a value
            else if(flag && (currentptr->value != " ")){
                for (int i=0; i<prefixCounter;i++)
                    output<<"\t";
                if (counter>=2){
                    prefix  = word;
                    prefixCounter++;
                }
                output<<"-"<<word<<"("<<search(searchNode,word)<<")"<<endl;
                listing(root->next[i],searchNode,word,prefix,prefixCounter,false, false,output);
            }
            if (!isAdded){
                word.append(prefix);
            }
        }
    }
    word.clear();
    isBranchExist(searchNode,root,counter);
    if (prefixCounter>1 && counter>=2){
        isAdded = true;
        prefix.pop_back();
        prefixCounter--;
    }
}


#endif //ASSIG4_TRIE_H
