
#include<iostream>
#include<string>
#include <fstream>
#include <cmath>
#include <vector>
#include <bitset>
#define BIT_14 16384.0 
#define BIT_8 256.0


using namespace std; 

/* Returns an unsigned long int number that is the result of a bitwise AND mask 
between the received number and the maximum allowed number based on the given bits. 
*/
unsigned long int bitOperations(int bits, unsigned long int num){
    unsigned long int big = 0; 
    for(int i = 0; i < bits; i++){
        big += 1 << i; 
    }
    big = big & num; 
    return  big; 
}

/* Convert characters in the array to integers, sum the values, and return 
the appropriate number of bits. 
*/
unsigned long int chatacterSummation( string key, int bits){
    unsigned long int rhash = 0;
    for(int i = 0; i < key.size(); i++){
        int ascciValue = int(key[i]);
        rhash += ascciValue; 
    }
    return bitOperations(bits, rhash); 
}

/* Convert characters in the array to integers, multiply the values, 
and return the appropriate number of bits.
*/
unsigned long int chatacterProducts( string key, int bits){
    unsigned long int rhash = 1;
    for(int i = 0; i < key.size(); i++){
        unsigned long int ascciValue = int(key[i]);
        rhash *= ascciValue; 
    }
    return bitOperations(bits, rhash);
}

/* Split the character array into segments of the specified number of bits. 
Return the combined exclusive OR of those values. 8 bits.
*/
unsigned long int chunkedXORs8(string key){
    unsigned long int rhash = 0;
    for(int i = 0; i < key.length(); i++){
        rhash ^= key[i]; 
    }
    return rhash; 
}

/* Split the character array into segments of the specified number of bits. 
Return the combined exclusive OR of those values. 14 bits. */
/*unsigned long int chunkedXORs14(string key){
    unsigned long int rhash = 0;
    for (char c : key) {
        rhash = (rhash << 8) | static_cast<unsigned char>(c);
    }
    unsigned int mask = (1 << 14) - 1;
    unsigned int XORResult = 0;

    while (rhash > 0) {
        unsigned int segment = rhash & mask;  // Get the next 14-bit segment
        XORResult ^= segment;                 // Perform XOR on the segment 
        rhash >>= 14;                         // Shift the number to process the next segment
    }


    return XORResult; 
}
*/
unsigned long int chunkedXORs14(string key) {
    string word = key; // Ejemplo de una palabra
    vector<bitset<14>> gruposDe14Bits;
    string grupoBits; // Cadena temporal para almacenar cada grupo de 14 bits
    for (char c : word) {
        bitset<8> bits(c); // Convierte cada carácter en un objeto bitset de 8 bits
        grupoBits += bits.to_string();        
    }
    if (grupoBits.length()%14 != 0) {   // Si queda algún grupo incompleto, agrégale ceros
        while (grupoBits.length()%14 != 0) {
            grupoBits += "0";
        }        
    }
    for (int i=0; i<grupoBits.length(); i+=14){
        string fourteenChar = grupoBits.substr(i,(i+14));
        gruposDe14Bits.push_back(bitset<14>(fourteenChar));
    }
    bitset<14> count=0;
    for(int i=0; i<gruposDe14Bits.size(); i++){
        count=count^gruposDe14Bits[i];
    }
    long int countAsLong = count.to_ulong();
    return countAsLong;
}

/*Compares collision rates for a hash function based on character summation.
  For each word in the list, this function computes a hash value, and the resulting
  number is used as an index into an integer array. A counter at that index is incremented
  to keep track of the number of collisions at that position.
 */
float compareSummation( float collisionRate, vector<string> list, int bits){
    float sum = 0; 
    float result = 0; 
    int tsize = bits == 8 ? BIT_8 : BIT_14; // Determine the table size based on the bit setting.
    int collisions [tsize] = {0}; // Initialize an array to count collisions.
    for(auto word : list){
        unsigned long int i = chatacterSummation(word, bits); 
        collisions[i] += 1; // Count the collisions at the computed hash value.
    }
    
    //Calculate the collision rate by comparing observed collisions to the expected rate.
    for(int i = 0; i < tsize; i++ ){
        sum += pow((collisions[i] - collisionRate), 2) ; 
    }
    sum = sqrt(sum);
    return sum; 
}

/*Compares collision rates for a hash function based on chunkedXORs8.
  For each word in the list, this function computes a hash value, and the resulting
  number is used as an index into an integer array. A counter at that index is incremented
  to keep track of the number of collisions at that position.
 */
float compareXOR8( float collisionRate, vector<string> list, int bits){
    float sum = 0; 
    float result = 0; 
    int tsize =  BIT_8 ; 
    int collisions [tsize] = {0}; //create array of collisions
    for(auto word : list){
        unsigned long int i = chunkedXORs8(word); 
        collisions[i] += 1; 
    }
    // Perform the summation operation to compare the collision rate
    for(int i = 0; i < tsize; i++ ){
        sum += pow((collisions[i] - collisionRate), 2);
    }
    sum = sqrt(sum);
    return sum; 
}

/*Compares collision rates for a hash function based on chunkedXORs14.
  For each word in the list, this function computes a hash value, and the resulting
  number is used as an index into an integer array. A counter at that index is incremented
  to keep track of the number of collisions at that position.
 */
float compareXOR14( float collisionRate, vector<string> list, int bits){
    float sum = 0; 
    float result = 0; 
    int tsize =  BIT_14 ; 
    int collisions [tsize] = {0}; //Create an array of collisions
    for(auto word : list){
        unsigned long int i = chunkedXORs14(word); 
        collisions[i] += 1; 
    }
    // Perform the summation operation to compare the collision rate
    for(int i = 0; i < tsize; i++ ){
        sum += pow((collisions[i] - collisionRate), 2);
    }
    sum = sqrt(sum);
    return sum; 
}

/*Compares collision rates for a hash function based on compareProducts.
  For each word in the list, this function computes a hash value, and the resulting
  number is used as an index into an integer array. A counter at that index is incremented
  to keep track of the number of collisions at that position.
 */
float compareProducts( float collisionRate, vector<string> list, int bits){
    float sum = 0; 
    float result = 0; 
    int tsize = bits == 8 ? BIT_8 : BIT_14; 
    int collisions [tsize] = {0}; 
    for(auto word : list){
        unsigned long int i = chatacterProducts(word, bits); 
        collisions[i] += 1; 
    }
    cout << "Colisiones xor: "<< bits << " bits " <<collisions[15] << ", " << collisions[200] << endl; 
    for(int i = 0; i < tsize; i++ ){
        sum += pow((collisions[i] - collisionRate), 2);
    }
    sum = sqrt(sum);
    return sum; 
}
/* Returns the position of the minimum value */
int betterCollisionRate(float collisionsRates[], int numberOfWords){
    float min = numberOfWords; // The minimun value of the collisions rates
    int pos = 0; 
    for (int i = 0; i < 5 ; i++){
        if(min < collisionsRates[i]){
            min = collisionsRates[i]; 
            pos = i; 
        }
    }
    return pos; 
}



int main() {
    // Open an input file for reading data.
    ifstream inputFile("sample_data.txt");

    // Check if the file opened successfully
    if (!inputFile) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }

    string word; 
    int numberOfWords = 0;
    vector<string> words;  
    
    // Read lines from the input file and store them in the hash table.
    while(getline(inputFile,word)){  
        words.push_back(word); 
        numberOfWords+=1;
    }

    //collision rate of a purely random hash of 8 bits
    float  purelyRandomCR8 = numberOfWords/BIT_8; 
    //collision rate of a purely random hash of 14 bits
    float  purelyRandomCR14 = numberOfWords/BIT_14; 

    float collisionsRate[5]; 
    string collisionsRateName[5]= {" Summation 8 ", " Summation 14 ", " Products 8 ", " Products 14 ", " XOR 8 "};

    // Compute collision rates for different hash functions and bit settings.
    collisionsRate[0] = compareSummation(purelyRandomCR8, words, 8); 
    collisionsRate[1] = compareSummation(purelyRandomCR14, words, 14); 
    collisionsRate[2] = compareProducts(purelyRandomCR8, words, 8); 
    collisionsRate[3] = compareProducts(purelyRandomCR14, words, 14); 
    collisionsRate[4] = compareXOR8(purelyRandomCR8, words, 8); 
    collisionsRate[5] = compareXOR14(purelyRandomCR14, words, 14); 


    cout << "Collision rate (8 bits): " << purelyRandomCR8 << endl; 
    cout << "Collision rate (14 bits): " << purelyRandomCR14 << endl; 
    cout << "Summation 8-bit: "<< collisionsRate[0] << endl; 
    cout << "Summation 14-bit: "<< collisionsRate[1] << endl;
    cout << "Products 8-bit: "<< collisionsRate[2] << endl; 
    cout << "Products 14-bit: "<< collisionsRate[3] << endl;
    cout << "XOR 8 bit: "<< collisionsRate[4] << endl;
    cout << "XOR 14 bit: "<< collisionsRate[5] << endl;


    int better = betterCollisionRate(collisionsRate, numberOfWords); 
    // Output the best collision rate. 
    cout << "The best collision rate is: " << collisionsRateName[better]; 

    // Closes the file 
    inputFile.close();

    return 0;
}