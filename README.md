# HashTable in C++

## Objective
The objective of this project is to explore various hash functions, evaluate their collision resistance, and then utilize the most effective function to construct a custom hash table class.

## Part 1: Hash Functions
Implementation
Implement the following hash functions:

### Hash Function 1: Character Summation
Convert characters in the input array to integers.
Sum the values and return the appropriate number of bits.
### Hash Function 2: Character Products
Convert characters in the input array to integers.
Multiply the values and return the appropriate number of bits.
### Hash Function 3: Chunked XORs
Split the character array into segments of the specified number of bits.
Return the combined exclusive OR (XOR) of those values.

### Testing
Compute 8-bit and 14-bit hashes for every word in the Unix word list.
Compare collision rates to the expected collision rate of a purely random hash.

Unix Word List Source:

Unix-style systems: /usr/share/dict/words or /usr/dict/words.
Download: Unix Word List
Hint: Utilize appropriate data structures to simplify conversions.

## Part 2: Building the Hash Table
Implementation
Utilize the most performant hash function identified from Part 1 to construct a hash table class. This class should map from a string to a templated class field.



