#include "hashing.hpp"

// Hash 1
int h1(string s, int arrSize) { 
    long long int hash = 0; 
    for (int i = 0; i < s.size(); i++) { 
        hash = (hash + ((int)s[i])); 
        hash = hash % arrSize; 
    } 
    return hash; 
} 
  
// Hash 2 
int h2(string s, int arrSize) { 
    long long int hash = 1; 
    for (int i = 0; i < s.size(); i++) { 
        hash = hash + pow(19, i) * s[i]; 
        hash = hash % arrSize; 
    }

    return hash % arrSize; 
} 
  
// Hash 3 
int h3(string s, int arrSize) { 
    long long int hash = 7; 

    for (int i = 0; i < s.size(); i++) { 
        hash = (hash * 31 + s[i]) % arrSize; 
    } 

    return hash % arrSize; 
} 
  
// Hash 4 
int h4(string s, int arrSize) { 
    long long int hash = 3; 
    int p = 7; 
    for (int i = 0; i < s.size(); i++) { 
        hash += hash * 7 + s[0] * pow(p, i); 
        hash = hash % arrSize; 
    } 

    return hash; 
} 
