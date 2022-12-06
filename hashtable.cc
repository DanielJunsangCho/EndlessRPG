#include "hashtable.h"

/**
 * Constructs the hashtable with two arguments
 * @param size: size of the hashtable
 * @param null: empty vector of vector of enemies and their information
 */
HashTable::HashTable(int size, vector<vector<enemy_info>> null) {
    _size = size;
    _enemies = null;
}

/**
 * @returns the size of the hashtable
 */
int HashTable::get_size() const {
    return _size;
}

/**
 * Retrieves enemies at an index
 * @param index: certain enemies in hashtable
 * @returns vector of enemis (could be no enemies or multiple)
 */
vector<enemy_info> HashTable::get_names_at_index(int index) const {
    return _enemies.at(index);
}

/**
 * Inserts an enemy into the hashtable
 * @param enemy: the enemy and its information
 * @param hash_value: the index where the enemy is inserted
 */
void HashTable::insert(enemy_info enemy, int const hash_value) {
     _enemies[hash_value].push_back(enemy);
}
