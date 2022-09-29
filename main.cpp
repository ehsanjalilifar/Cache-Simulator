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
#include <cstdlib>

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
        int** lru; // An auxiliary 2D array for LRU implementation

        long long getTag(long long address) {
            // Shift the address to get the tag bits
            return (address >> (n_offset_bits + n_index_bits));
        }    

        long long getIndex(long long address) {
            return (address / blocksize) % n_sets;
        }

        void updateLRU(long long set_idx, int block_idx) {
            for(int i = 0; i < assoc; i++) {
                i == block_idx ? lru[set_idx][i] = 0 : lru[set_idx][i]++;
            }
        }

        int evict(long long set_idx) {
            int block_idx = 0;
            if(policy == 'l') { // LRU
                int max = 0;
                for(int i = 0; i < assoc; i++) {
                    if(lru[set_idx][i] > max) {
                        max = lru[set_idx][i];
                        block_idx = i; 
                    }
                }
            } else { // random
                block_idx = std::rand() % assoc;
            }
            validBitMap[set_idx][block_idx] = false;
            return block_idx;
        }

        void writeToCache(long long address) {
            long long set_idx = getIndex(address);
            long long tag = getTag(address);
            for(int block_idx = 0; block_idx < assoc; block_idx++) {
                if(!validBitMap[set_idx][block_idx]) { // write to the first empty block in the set
                    validBitMap[set_idx][block_idx] = true; // update the valid bit
                    cacheMem[set_idx][block_idx] = tag; // store the address in the cache
                    if(policy == 'l') updateLRU(set_idx, block_idx);
                    return;
                }
            }
            // All the blocks in the set are full
            // One block needs to be evicted first
            int block_idx = evict(set_idx);
            cacheMem[set_idx][block_idx] = tag;
            validBitMap[set_idx][block_idx] = true; // It might not be necessary
            if(policy == 'l') updateLRU(set_idx, block_idx);
            return;
        }

        bool isHit(long long address) {
            long long set_idx = getIndex(address);
            long long tag = getTag(address);
            for(int block_idx = 0; block_idx < assoc; block_idx++) {
                if(validBitMap[set_idx][block_idx] && tag == cacheMem[set_idx][block_idx]) {
                    // Got a hit -> update the lru
                    if(policy == 'l') updateLRU(set_idx, block_idx);
                    return true;
                }
            }
            // It's a miss
            writeToCache(address);
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
            this->lru = new int*[this->n_sets];
            for (int i = 0; i < this->n_sets; i++) {
                this->cacheMem[i] = new  long long[this->assoc];
                this->validBitMap[i] = new bool[this->assoc];
                this->lru[i] = new int[this->assoc];
            }

        }

        ~Cache() {
            // Needs to be implemented
        }

        void isInCache(long long address, char type) {
            if(!isHit(address)) { // update the cache on a miss
                type == 'r' ? r_miss++ : w_miss++;
            }
            type == 'r' ? r_count++ : w_count++;
        }

        void printStatus() {
            double miss_rate, r_miss_rate, w_miss_rate;
            miss_rate = (1.0 * (r_miss + w_miss)) / (r_count + w_count) * 100.0; // total miss rate
            r_miss_rate = (1.0 * r_miss) / r_count * 100.0; // read miss rate
            w_miss_rate = (1.0 * w_miss) / w_count * 100.0; // write miss rate

            std::cout << r_miss + w_miss << " " << miss_rate << "% " << r_miss << " " << r_miss_rate << "% " << w_miss << " " << w_miss_rate << "%" << std::endl;
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

    // ### Read from inut file
    // std::ifstream infile("401.bzip2-226B.trace.txt");
    
    // while(!infile.eof()) {
    //     infile >> operation >> std::hex >> address;
    //     // std::cout << operation << " " << address << std::endl;
    //     cacheSim.isInCache(address, operation);
    // }

    // infile.close();

    // Read from standard input
    while(std::cin >> operation >> std::hex >> address) {
        // std::cout << operation << " " << address << std::endl;
        cacheSim.isInCache(address, operation);
    }

    cacheSim.printStatus();    
    return 0;
}
