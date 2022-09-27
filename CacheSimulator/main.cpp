//
//  main.cpp
//  CacheSimulator
//
//  Created by Ehsan Jalilifar on 9/27/22.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    
    int nk = (int) *argv[1]; // The capacity of the cache in kilobytes
    int assoc = (int) *argv[2]; // The associativity of the cache
    int blocksize = (int) *argv[3]; // The size of a single cache block in bytes
    char repl = *argv[4]; // The replacement policy; 'l' means LRU, 'r' means random.
    
    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    std::cout << "Hello, World!\n";
    
//    char type;
//    unsigned long long address;
//    std::cin >> type >> address;
    
    return 0;
}
