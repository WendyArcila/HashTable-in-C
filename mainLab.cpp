#include<iostream>
#include<string>
#include <fstream>
#include "HashTableLab.h" 

using namespace std; 

int main(){
    // Create a new HashTable object.
    HashTable* myHashTable = new HashTable();

    // Open an input file for reading data.
    ifstream inputFile("sample_data.txt");

    // Check if the file opened successfully
    if (!inputFile) {
        cerr << "Error opening the file." << endl;
        return 1;
    }
    
    string word; 
    int numberOfWords = 0; 

    // Output the initial size of the table and maximum size.
    cout << "Initial table size:  " << myHashTable->tableSize << endl; 
    cout << "Maximum node size: " << myHashTable->maxSize << endl; 

    // Read lines from the input file and store them in the hash table.
    while(getline(inputFile,word) && numberOfWords < 250){  
        myHashTable->setKey(word, numberOfWords);  
        numberOfWords+=1;
    }

    // Print the contents of the hash table.
    myHashTable->printTable(); 

    // Output the final size of the table and the number of nodes.
    cout << "tamanio final: " << myHashTable->tableSize << endl;
    cout << "tamanio nodos final: " << myHashTable->length << endl; 

    // Closes the file 
    inputFile.close();

    return 0; 
}