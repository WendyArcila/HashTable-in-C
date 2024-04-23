#ifndef HASHTABLE_H
#define HASHTABLE_H

#include<iostream>
#include <string>
#include <optional>
#define DFTABLESIZE 256

using namespace std; 


/* Node class, this class has as attributes the key, the value and the link to the next node.
the value and the link to the next node. With its respective constructor. Represents the nodes in the hash table.
*/
class Node {
public: 
    string key;
    int value;
    Node* next; 
    Node(){}; 
    Node(string key, int value){
        this->key = key;
        this->value = value;
        next = nullptr; 
    }
}; 


/* HashTable class represents a hash table that maps keys to integer values.
*/
class HashTable {

private: 
    float lFactor; //Load Factor recommended
    Node** dataMap;

public:
    int tableSize;
    int length;  // total data saved
    int maxSize;  // maximum size of data in the hashtable according to the load factor 

    // Constructor initializes the hash table with default values.
    HashTable() {
            length = 0;
            lFactor = 0.75; 
            tableSize = DFTABLESIZE;
            maxSize = (int) (tableSize * lFactor);
            dataMap = new Node*[tableSize];
            for (int i = 0; i < tableSize; i++)
                dataMap[i] = NULL;
    }

    // Destructor releases memory used by the hash table.
    ~HashTable() {
        for (int i = 0; i < tableSize; i++){
            if (dataMap[i] != NULL) {
                Node* prevEntry = NULL;
                Node* entry = dataMap[i];
                while (entry != NULL) {
                    prevEntry = entry;
                    entry = entry->next;
                    delete prevEntry;
                }
            }
        }
        delete[] dataMap;
    }

    // Resize the hash table to accommodate more elements when needed.
    void resize(){
        int oldSize = tableSize;
        tableSize = tableSize* 2; 
        tableSize % 2 == 0 ? tableSize+=1 : 0; //rules out that the tableSize is multiplot of 2 
        maxSize = (int) (tableSize * lFactor); 
        Node** oldTable = dataMap; 
        dataMap = new Node*[tableSize];//HashTable is created/updated with new size
        for(int i = 0; i < oldSize; i++){
            dataMap[i] = NULL;
        }
        length = 0; //The node count is initialized to 0.
        for(int i = 0; i < oldSize; i++){
            if(oldTable[i] != NULL){
                Node* oldEntry; 
                Node* entry = oldTable[i];
                while(entry != NULL){
                    setKey(entry->key, entry->value);
                    oldEntry = entry; 
                    entry = entry->next;
                    delete oldEntry; 
                }
            }
        }
        delete[] oldTable;
    }


    /* Hash function that converts characters to integers and returns an index.
    */
    int hashFuntion(const string& key) const{
        int rhash = 0;
        for(int i = 0; i < key.size(); i++){
            int ascciValue = int(key[i]);
            rhash = (rhash + ascciValue);  
        }
        rhash = (rhash*97)%tableSize;
        return rhash;
    }

   
    // Insert or update a key-value pair in the hash table..
    void setKey(const string& key, int value){
        int index = hashFuntion(key);         //sets index
        if(!exist(key)){                      //evaluates whether it is a new data or an update 
            Node* newNode = new Node(key, value);
            if(dataMap[index] == nullptr){
                dataMap[index] = newNode;
                length = length+1; 
            } else {
                Node* temp = dataMap[index]; 
                while(temp->next != nullptr){ //scrolls down the list to the last position 
                    temp = temp->next; 
                }
                temp->next = newNode;
                length = length+1;
            }
        } else {
            Node* temp = dataMap[index]; 
                while(temp->key !=  key && temp->next != NULL){
                    temp = temp->next; 
                }
                temp->value = value; //update value
        }
        if(length >= maxSize){
            resize(); //if the amount of data is greater than or equal to the maximum size, resizing is required. 
        }
    }

    // Get value by key. Returns nullopt if key is not found.
    optional<int> getKey(const string& key) const{
        int index = hashFuntion(key);
        Node* temp = dataMap[index];
        while (temp != nullptr) {
            if (temp->key == key) return temp ->value; 
            temp = temp->next; 
        }
        return nullopt; 
    }

    /*int getKey(const string& key) const{
        int index = hashFuntion(key);
        Node* temp = dataMap[index];
        while (temp != nullptr) {
            if (temp->key == key) return temp ->value; 
            temp = temp->next; 
        }
        return -1; 
    }*/

    // Check if a key exists in the hash table.
    bool exist(string key) {
    optional<int> result = getKey(key); // Get the optional<int> result.
    return result.has_value(); // Check if the optional has a value (key exists).
}


    // Remove all key-value pairs from the hashFuntion table.
    void clear(){
        for(int i = 0; i < tableSize; i++){
            if(dataMap[i] != NULL){
                Node* ptr = dataMap[i]; 
                while(ptr->next != nullptr){
                    Node* deleted = ptr; 
                    ptr= ptr->next; 
                    delete(deleted); 
                    length --; 
                }
            }
        }
    }

    // Print the contents of the hash table.
    void printTable(){
        for(int i = 0; i < tableSize;  i++){
            cout << i << ":" << endl; 
            if(dataMap[i]){
                Node* temp = dataMap[i];
                while(temp){
                    cout <<"    {" << temp->key << ", " << temp->value <<  "}" << endl; 
                    temp = temp->next; 
                }
            }
        }
    }
}; 



#endif // HASHTABLE_H
