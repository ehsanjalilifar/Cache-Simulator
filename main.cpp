//
//  main.cpp
//  CacheSimulator
//
//  Created by Ehsan Jalilifar on 9/27/22.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
// #include <fstream>
#define KB 1024

class Cache {
    private:
        int capacity;
        int assoc;
        int blocksize;
        char policy;
        int n_sets;
        int n_offset_bits;
        int n_index_bits;
        unsigned long long** cacheMem; // Stores addresses in the cache as a 2D array
        bool** validBitMap; // A 2D bitmap for the Valid bit
        
        unsigned long long getTag(unsigned long long address) {
            // Shift the address to get the tag bits
            return (address >> (n_offset_bits + n_index_bits));
        }   

        unsigned long long getIndex(unsigned long long address) {
            // Remove the Offset 
            unsigned long long tmp = address >> n_offset_bits;
            // Remove the index bits (address space is 64 bits)
            tmp = tmp << (64 - n_index_bits);
            // remove the right zeros and return
            tmp = tmp >> (n_offset_bits + n_index_bits);
            return (tmp);
        } 

    public:
        Cache(int nk, int assoc, int blocksize, char repl) {
            this->capacity = nk;
            this->assoc = assoc;
            this->blocksize = blocksize;
            this->policy = repl;
            this->n_sets = this->capacity * KB / this->assoc / this->blocksize;
            this->n_offset_bits = (int) std::log2(this->blocksize);
            this->n_index_bits = (int) std::log2(this->assoc);

            // Define a 2-D array to store the addresses in the cach
            this->cacheMem = new unsigned long long*[this->n_sets];
            this->validBitMap = new bool*[this->n_sets]; // defines the valid bit
            for (int i = 0; i < this->n_sets; i++) {
                this->cacheMem[i] = new unsigned long long[this->assoc];
                this->validBitMap[i] = new bool[this->assoc];
            }

        }

        bool checkMiss(unsigned long long address) {

            return true;
        }
};

int main(int argc, const char * argv[]) {
    
    int nk = std::atoi(argv[1]); // The capacity of the cache in kilobytes
    int assoc = std::atoi(argv[2]); // The associativity of the cache
    int blocksize = std::atoi(argv[3]); // The size of a single cache block in bytes
    char repl = *argv[4]; // The replacement policy; 'l' means LRU, 'r' means random.

    Cache cacheSim = Cache(nk, assoc, blocksize, repl);
    
    char operation;
    unsigned long long address;

    std::ifstream infile("input.txt");
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
