//
//  main.cpp
//  CacheSimulator
//
//  Created by Ehsan Jalilifar on 9/27/22.
//

#include <iostream>
#define KB 1024

int main(int argc, const char * argv[]) {
    
    int nk = (int) *argv[1]; // The capacity of the cache in kilobytes
    int assoc = (int) *argv[2]; // The associativity of the cache
    int blocksize = (int) *argv[3]; // The size of a single cache block in bytes
    char repl = *argv[4]; // The replacement policy; 'l' means LRU, 'r' means random.
    
    int n_sets = nk * KB / assoc / blocksize;
    
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    
    std::cout << "number of sets = " << n_sets << std::endl;
    
    // Define a 2-D array to store the addresses in the cach
    unsigned long long ** cache = new unsigned long long*[n_sets];
    for (int i = 0; i < n_sets; i++) {
        cache[i] = new unsigned long long[assoc];
    }
    
//    char type;
//    unsigned long long address;
//    std::cin >> type >> address;
    
    return 0;
}
