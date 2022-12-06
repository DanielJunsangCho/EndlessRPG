#include "hero.h"

/**
 * Constructs the "hero" with two arguments
 * @param hero_hp: the hero's hp
 * @param hero_atk: the hero's attack
 */
Hero::Hero(int hero_hp, int hero_atk) {
   _hero_hp = hero_hp;
   _hero_atk = hero_atk;
   _enemies_killed = 0;
}

/**
 * @returns the hero's health
 */
int Hero::get_hp() const{
   return _hero_hp;
}

/**
 * Prints the stats for wizard and archer
 * @param enemies_in_range: the enemies that the hero is fighting
 * @param move: number move that the hero is on
 * @param index: determines if the hero is a wizard or archer
 */
void Hero::ranged_char_stats(vector<enemy_info> enemies_in_range, const int move, const int index) {
   for (int i = 0; i < index; i++) {
      enemy_info enemy = enemies_in_range[i];
      cout << "Enemy hp: " << enemy.name << ", " << enemy.hp << endl;
   }
   cout << endl;
}

/**
 * Prints the stats for warrior
 * @param enemy: the enemy that the hero is fighting
 * @param move: number move that the hero is on
 */
void Hero::warrior_stats(enemy_info enemy, int const move) const {
   cout << "Enemy hp: " << enemy.name << ", " << enemy.hp << endl << endl;
}

/**
 * Fights three topmost enemies in queue for one move
 * @param dungeon: attacks the three topmost enemies in queue
 * @param enemies: used for adding enemy into dungeon if one dies
 * @param move: number move that the hero is on
 * @returns the dungeon after hero attacks enemies
 */
Queue Hero::wizard(Queue &dungeon, HashTable enemies, const int move) {
   cout << "=== Move " << move << " ===" << endl;
   dungeon.print();
   cout << "Enemies killed: " << _enemies_killed << endl;
   cout << "Hero hp: " << _hero_hp << endl;
   vector<enemy_info> enemies_in_range;
   for (int i = 0; i < 3; i++) {
      enemy_info& enemy = dungeon.get_enemy_at_index(i);
      enemies_in_range.push_back(enemy);
   }
   ranged_char_stats(enemies_in_range, move, 3);
   for (int i = 0; i < 3; i++) {
      enemy_info &enemy = dungeon.get_enemy_at_index(i);
      enemy.hp -= _hero_atk;
      enemies_in_range[i] = enemy;
   }
   cout << "You attack!" << endl << endl;
   ranged_char_stats(enemies_in_range, move, 3);
   for (int i = 0; i < 3; i++) {
      enemy_info enemy = enemies_in_range[i];
      if (enemy.hp <= 0) {
         dungeon.dequeue();
         enemy_info new_enemy = enemy_make(enemies);
         dungeon.enqueue(new_enemy);
         _enemies_killed++;
      }
   }
   return dungeon;
}

/**
 * Fights two topmost enemies in queue for one move
 * @param dungeon: attacks the two topmost enemies in queue
 * @param enemies: used for adding enemy into dungeon if one dies
 * @param move: number move that the hero is on
 * @returns the dungeon after hero attacks enemies
 */
Queue Hero::archer(Queue &dungeon, HashTable enemies, const int move) {
   cout << "=== Move " << move << " ===" << endl;
   dungeon.print();
   cout << "Enemies killed: " << _enemies_killed << endl;
   cout << "Hero hp: " << _hero_hp << endl;
   vector<enemy_info> enemies_in_range;
   for (int i = 0; i < 2; i++) {
      enemy_info& enemy = dungeon.get_enemy_at_index(i);
      enemies_in_range.push_back(enemy);
   }
   ranged_char_stats(enemies_in_range, move, 2);
   for (int i = 0; i < 2; i++) {
      enemy_info &enemy = dungeon.get_enemy_at_index(i);
      enemy.hp -= _hero_atk;
      enemies_in_range[i] = enemy;
   }
   cout << "You attack!" << endl << endl;
   ranged_char_stats(enemies_in_range, move, 2);
   for (int i = 0; i < 2; i++) {
      enemy_info enemy = enemies_in_range[i];
      if (enemy.hp <= 0) {
         dungeon.dequeue();
         enemy_info new_enemy = enemy_make(enemies);
         dungeon.enqueue(new_enemy);
         _enemies_killed++;
      }
   }
   return dungeon;
}

/**
 * Fights topmost enemy in queue for one move
 * @param dungeon: attacks the topmost enemy in queue
 * @param enemies: used for adding enemy into dungeon if one dies
 * @param move: number move that the hero is on
 * @returns the dungeon after hero attacks enemy
 */
Queue Hero::warrior(Queue &dungeon, HashTable enemies, const int move) {
   cout << "=== Move " << move << " ===" << endl;
   dungeon.print();
   cout << "Enemies killed: " << _enemies_killed << endl;
   cout << "Hero hp: " << _hero_hp << endl;
   enemy_info &enemy = dungeon.get_enemy_at_index(0);
   warrior_stats(enemy, move);
   enemy.hp -= _hero_atk;
   if (enemy.hp <= 0) {
      dungeon.dequeue();
      enemy_info new_enemy = enemy_make(enemies);
      dungeon.enqueue(new_enemy);
      _enemies_killed++;
   }
   cout << "You attack!" << endl << endl;
   warrior_stats(enemy, move);
   return dungeon;
}

/**
 * Makes a new enemy after one dies
 * @param enemies: hashtable used for adding enemy into dungeon if one dies
 * @returns the new enemy or an empty slot if no enemy is in certain index
 */
enemy_info Hero::enemy_make(HashTable enemies) {
   int index = rand() % enemies.get_size();
   vector<enemy_info> names = enemies.get_names_at_index(index);
   int size = names.size();
   if (size == 0) {
      enemy_info enemy;
      enemy.name = "empty";
      enemy.hp = 0;
      enemy.atk = 0;
      return enemy;
   }
   return names[rand() % size];
}

/**
 * Used when enemy attacks hero
 * @param dungeon: used to access topmost enemy
 * @returns the dungeon after enemy attacks hero
 */
Queue Hero::enemy_attack(Queue &dungeon) {
   enemy_info& enemy = dungeon.get_enemy_at_index(0);
   _hero_hp -= enemy.atk;
   return dungeon;
}
