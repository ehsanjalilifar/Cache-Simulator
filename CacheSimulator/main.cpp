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
    
    unsigned long long r_miss, w_miss, n_read, n_write;
    r_miss = w_miss = n_read = n_write = 0;
    
    // Miss calculations
    double miss_rate, r_miss_rate, w_miss_rate;
    miss_rate = (double) (r_miss + w_miss) / (n_read + n_write); // total miss rate
    r_miss_rate = (double) r_miss / n_read; // read miss rate
    w_miss_rate = (double) w_miss / n_read; // write miss rate
    
    std::cout << r_miss + w_miss << " " << miss_rate << " " << r_miss << " " << r_miss_rate << " " << w_miss << " " << w_miss_rate << std::endl;
    
//    char type;
//    unsigned long long address;
//    std::cin >> type >> address;
    
    return 0;
}
