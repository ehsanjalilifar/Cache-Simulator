//
//  main.cpp
//  CacheSimulator
//
//  Created by Ehsan Jalilifar on 9/27/22.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
// #include <fstream>
#define KB 1024

int main(int argc, const char * argv[]) {
    
    int nk = std::atoi(argv[1]); // The capacity of the cache in kilobytes
    int assoc = std::atoi(argv[2]); // The associativity of the cache
    int blocksize = std::atoi(argv[3]); // The size of a single cache block in bytes
    char repl = *argv[4]; // The replacement policy; 'l' means LRU, 'r' means random.

    int n_sets = nk * KB / assoc / blocksize;
    
    std::cout << "number of sets = " << n_sets << std::endl;
    

    // Define a 2-D array to store the addresses in the cach
    unsigned long long** cache = new unsigned long long*[n_sets];
    bool** valid = new bool*[n_sets]; // defines the valid bit
    for (int i = 0; i < n_sets; i++) {
        cache[i] = new unsigned long long[assoc];
        valid[i] = new bool[assoc];
    }

    char operation;
    unsigned long long address;
    std::string myText;

    std::ifstream infile("input.txt");
    std::cout << infile.is_open() << std::endl;
    while(!infile.eof()) {
        infile >> operation >> std::hex >> address;
        std::cout << operation << " " << address << std::endl;
    }
    infile.close();
    
    // Cache miss rate calculations
    unsigned long long r_miss, w_miss, n_read, n_write;
    r_miss = w_miss = n_read = n_write = 0;

    double miss_rate, r_miss_rate, w_miss_rate;
    miss_rate = (double) (r_miss + w_miss) / (n_read + n_write); // total miss rate
    r_miss_rate = (double) r_miss / n_read; // read miss rate
    w_miss_rate = (double) w_miss / n_read; // write miss rate

    std::cout << r_miss + w_miss << " " << miss_rate << " " << r_miss << " " << r_miss_rate << " " << w_miss << " " << w_miss_rate << std::endl;
    
//    std::cin >> type >> address;
    
    return 0;
}
