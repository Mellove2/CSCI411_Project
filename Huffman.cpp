#include <iostream>  
#include <queue>   
#include <bits/stdc++.h>   
#include <vector>                               
#include <algorithm>      
using namespace std;   

struct Node{ 
 //struct for the letter and parent/dummy nodes 
    string letter;  //holds either a char or a string of chars 
    int amount;  //frequency 
    bool parent; //is this node a parent/dummy node? 
    //childern 
    shared_ptr<Node> left;
    shared_ptr<Node> right;  

    string binary;      
    
    Node(string L, int freq){ 
     //for creating the letter nodes   
    letter = L;           
    amount = freq;   
    parent = false;  
    left = nullptr;
    right = nullptr; 
    }     

    Node(string L, int freq, shared_ptr<Node> Lt, shared_ptr<Node> Rt, bool truth){ 
     //use to create parent/add-on nodes
        letter = L;
        amount = freq;
        parent = truth;
        left = Lt;
        right = Rt;
    }
};

struct Compare{
 //used in priority queues to compare the left and right childs frequency for the creation of the table
    bool operator()(shared_ptr<Node> left, shared_ptr<Node> right){
        return right->amount < left->amount;
    }
};

void addEdges(shared_ptr<Node> &u){
 //usd to add the binary to the binary strings of the Nodes based on their parent's binary and what side they are on of the parent 
    //base case
    if(u->left == nullptr || u->right == nullptr) return;
    
    //add parent binary and "0" if on left and "1" if on right
    u->left->binary = u->binary + "0";
    u->right->binary = u->binary + "1";

    //check the childern of the left and right child of this node
    addEdges(u->left);
    addEdges(u->right);
}

void ciphertext(shared_ptr<Node> u, unordered_map<char,string> &ciphers){
 //used to de-tree the root node that is in "plaintext" for easier encoding in main

    //add letter node and such node's binary to "ciphers" 
    if(u->parent == false) ciphers[u->letter[0]] = u->binary;

    //do same to left and right child if they exist
    if(u->left != nullptr) ciphertext(u->left, ciphers);
    if(u->right != nullptr) ciphertext(u->right, ciphers);
}

void huffman(std::string message, unordered_map<char,string> &ciphers){
 //used to create frequency tree,    
    unordered_map<char, int> freq;

    //get freqency for each letter
    for(auto letter : message){ //go through all letters in "message"
        if(freq.find(letter) == freq.end()){ //if you can't alreaady find it in "freq", create place for it
            freq[letter] = 1;
        } //otherwise, add one to the frequency of that letter in "freq"
        else freq[letter]++;
    }
   
    //if there is only one letter in "message", don't go through the rest of the process and just cout "1" for the binary
    if(freq.size() == 1){
        auto holder = freq[0];
        ciphers[holder] = "1";
    }

    //create the prioriy queue that will hold all the nodes for letters and parent/dummy nodes 
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, Compare> plaintext;

    //create all the letter nodes
    for(auto holder : freq){ //go through "freq"
        //create string where 1 is the length of the string and holder.frist, aka the first char of the string letter, is the value 
        std::string s(1,holder.first);

        //create a node for each letter
        shared_ptr<Node> temp = make_shared<Node>(s,holder.second);

        //put each node into "plaintext"
        plaintext.push(temp);
    }

    //combine into a tree
    while(plaintext.size() > 1){

        //take first two letters
        shared_ptr<Node> right = plaintext.top();
        plaintext.pop();
        shared_ptr<Node> left = plaintext.top();
        plaintext.pop();

        //create parent for this left and right child 
        shared_ptr<Node> parent = make_shared<Node>(left->letter+right->letter, left->amount+right->amount, left, right, true);
        
        //add back in parent
        plaintext.push(parent);
    }
    
    //this is the last element in plaintext and thus the root
    shared_ptr<Node> root = plaintext.top(); 
    plaintext.pop();

    //use the root in addEdges
    addEdges(root);

    //after the binary is put to each node, use this in ciphertext 
    ciphertext(root, ciphers);

}

int main(){
    //get the message from the file
    string message;
    getline(cin, message);

    if(message.size() == 1 && message == " "){
            cout << "No message to encrypt" << endl;
            return 0;
    }
            unordered_map<char, string> ciphers;
        huffman(message, ciphers);
  
        string ciphertexts;
        for(auto mess : message){
                ciphertexts += " " + ciphers[mess];
            }


    if(ciphertexts.size() == 0) cout << "Encryption has failed.";
    else{
        cout << "Original message: " << message << endl;
        cout << "Encoded message:" << ciphertexts << endl;
    }
    return 0;
}
