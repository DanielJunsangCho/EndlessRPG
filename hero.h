#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <vector>
#include "mystruct.h"
#include "hashtable.h"
#include "queue.h"
using namespace std;

/**
 * Creates the hero and uses its type to play the game
 */
class Hero {
private:
   int _hero_hp;
   int _hero_atk;
   int _enemies_killed;
public:
   Hero(int hero_hp, int hero_atk);
   int get_hp() const;
   void ranged_char_stats(vector<enemy_info> enemies_in_range, int const move, int const index);
   void warrior_stats(enemy_info enemy, int const move) const;
   Queue wizard(Queue &dungeon, HashTable enemies, int const move);
   Queue archer(Queue &dungeon, HashTable enemies, int const move);
   Queue warrior(Queue &dungeon, HashTable enemies, int const move);
   enemy_info enemy_make(HashTable enemies);
   Queue enemy_attack(Queue &dungeon);
};
#endif
