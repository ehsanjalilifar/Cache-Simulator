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
        long long** cacheMem; // Stores addresses in the cache as a 2D array
        bool** validBitMap; // A 2D bitmap for the Valid bit
        long long r_miss;
        long long w_miss;
        long long r_count;
        long long w_count;
        
        long long getTag(long long address) {
            // Shift the address to get the tag bits
            return (address >> (n_offset_bits + n_index_bits));
        }    

        long long getIndex(long long address) {
            return (address / blocksize) % n_sets;
        }

        bool isHit(long long address) {
            long long set_idx = getIndex(address);
            long long tag = getTag(address);
            for(int i = 0; i < assoc; i++) {
                if(validBitMap[set_idx][i] && tag == cacheMem[set_idx][i]) return true;
            }
            return false;
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
            this->r_miss = 0;
            this->w_miss = 0;

            // Define a 2-D array to store the addresses in the cach
            this->cacheMem = new  long long*[this->n_sets];
            this->validBitMap = new bool*[this->n_sets]; // defines the valid bit
            for (int i = 0; i < this->n_sets; i++) {
                this->cacheMem[i] = new  long long[this->assoc];
                this->validBitMap[i] = new bool[this->assoc];
            }

        }

        void insert(long long address, char type) {
            if(!isHit(address)) { // update the cache on a miss
                type == 'r' ? r_miss++ : w_miss++;
            }
            type == 'r' ? r_count++ : w_count++;
        }

        
};

int main(int argc, const char * argv[]) {
    
    int nk = std::atoi(argv[1]); // The capacity of the cache in kilobytes
    int assoc = std::atoi(argv[2]); // The associativity of the cache
    int blocksize = std::atoi(argv[3]); // The size of a single cache block in bytes
    char repl = *argv[4]; // The replacement policy; 'l' means LRU, 'r' means random.

    Cache cacheSim = Cache(nk, assoc, blocksize, repl);
    
    char operation;
    long long address;

    std::ifstream infile("input.txt");
    while(!infile.eof()) {
        infile >> operation >> std::hex >> address;
        std::cout << operation << " " << address << std::endl;
    }
    infile.close();
    
    // Cache miss rate calculations
    long long r_miss, w_miss, n_read, n_write;
    r_miss = w_miss = n_read = n_write = 0;

    double miss_rate, r_miss_rate, w_miss_rate;
    miss_rate = (double) (r_miss + w_miss) / (n_read + n_write); // total miss rate
    r_miss_rate = (double) r_miss / n_read; // read miss rate
    w_miss_rate = (double) w_miss / n_read; // write miss rate

    std::cout << r_miss + w_miss << " " << miss_rate << " " << r_miss << " " << r_miss_rate << " " << w_miss << " " << w_miss_rate << std::endl;
    
//    std::cin >> type >> address;
    
    return 0;
}
