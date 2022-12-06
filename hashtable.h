#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <vector>
#include "mystruct.h"
using namespace std;

// CITE: Day 31 Class - Hash Tables
// DESC: Aided in the building of my own hash table
/**
 *Creates the hashtable that holds enemy information
 */
class HashTable {
private:
    int _size;
    vector<vector<enemy_info>> _enemies;
public:
    HashTable(int size, vector<vector<enemy_info>> null);
    int get_size() const;
    vector<enemy_info> get_names_at_index(int index) const;
    void insert(enemy_info enemy, int const hash_value);
};
#endif
