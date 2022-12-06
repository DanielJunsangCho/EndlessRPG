#include <iostream>
#include <vector>
#include "mystruct.h"
#include "hashtable.h"
#include "queue.h"
#include "hero.h"
using namespace std;

double MOD_MULTIPLIER = 1.3;
int HP_MULTIPLIER = 4;
int PLAYER_TYPES = 3;


/**
 * Receives the needed information about the player
 * @returns a dynamic array of player level and player type
 */
int* player_intro() {
   string player_name;
   int player_type, player_lvl;
   int* player_info = new int[2];
   cout << "Hello, hero! What is your name?: ";
   cin >> player_name;
   cout << "Nice to meet you, " << player_name << "! Our land has long been taken over by monsters,"
   << " and I see that you are a capable fighter." << endl << "What fighter type are you?"
   << " Press (1) for wizard, (2) for archer, (3) for warrior: ";
   cin >> player_type;
   player_info[0] = player_type;
   while (player_type < 1 || player_type > PLAYER_TYPES) {
      cout << "Oh no! That is not a valid type. Please enter a different value: ";
      cin >> player_type;
      player_info[0] = player_type;
   }
   cout << "And what is your level?: ";
   cin >> player_lvl;
   player_info[1] = player_lvl;
   cout << "That is great to hear! You will be able to help us out a lot." << endl;
   return player_info;
}

// CITE: Day 31 Class - Hash Tables
// DESC: Aided in the building of my own hash table
/**
 * Calculates hash value based off of an enemy name
 * @param enemy_name: name of the enemy
 * @param size: size of the hash table
 * @returns the hash value
 */
int get_hash_value(string &enemy_name, int const &size) {
   int hash_value = 0;
   for (char &c : enemy_name) {
      hash_value += c;
   }
   hash_value = hash_value % size;
   return hash_value;
}


// CITE: Day 31 Class - Hash Tables
// DESC: Aided in the building of my own hash table
/**
 * Player inputs the names of the enemies they will fight
 * @returns an vector of enemy names
 */
vector<string> get_names() {
   string enemy_name;
   vector<string> enemy_names;
   cout << "What type of monsters will you be fighting today? Press (0) to finish: ";
   while (enemy_name != "0") {
      cin >> enemy_name;
      cout << endl;
      if (enemy_name != "0") {
         enemy_names.push_back(enemy_name);
         cout << "What else?: ";
      }
   }
   cout << "I wish you luck!" << endl << endl;
   return enemy_names;
}

/**
 * Makes the hash table with enemies
 * @param enemy_names: vector of enemy names
 * @param player_info: dynamic array of player information
 * @returns the hash table with enemy names
 */
HashTable enemy_maker(vector<string> enemy_names, int* const player_info) {
   int list_size = enemy_names.size();
   int table_size = list_size * MOD_MULTIPLIER;
   vector<vector<enemy_info>> waves(table_size);
   HashTable enemies(table_size, waves);
   for (int i = 0; i < list_size; i++) {
      int hash_value = get_hash_value(enemy_names[i], table_size);
      enemy_info enemy;
      enemy.name = enemy_names[i];
      enemy.hp = hash_value * player_info[1] / 2;
      enemy.atk = hash_value;
      enemies.insert(enemy, hash_value);
   }
   return enemies;
}

/**
 * Makes the queue that acts as a dungeon
 * @param player_lvl: player's level determines initial size of dungeon
 * @param enemies: enemies will be randomly selected to be put in dungeon
 * @returns the queue with enemies in it
 */
Queue make_dungeon(int const player_lvl, HashTable enemies) {
   Queue dungeon;
   for (int i = 0; i < player_lvl; i++) {
      int index = rand() % enemies.get_size();
      vector<enemy_info> names = enemies.get_names_at_index(index);
      int size = names.size();
      for (int j = 0; j < size; j++) {
         dungeon.enqueue(names[j]);
      }
   }
   return dungeon;
}

/**
 * Initializes Hero class and plays the game
 * @param player_info: dynamic array of player information
 * Q@param enemies: the hashtable indexed with enemies
 */
void play_game(int* const player_info, HashTable enemies) {
   int move = 0;
   int player_hp = player_info[0] * player_info[1] * HP_MULTIPLIER;
   int player_atk = player_info[0] * player_info[1];
   Hero player(player_hp, player_atk);
   bool player_move = true;
   Queue dungeon = make_dungeon(player_info[1], enemies);
   while (player.get_hp() > 0) {
      if (player_move == false) {
         dungeon = player.enemy_attack(dungeon);
         player_move = true;
      }
      else if (player_move == true) {
         cin.ignore();
         move++;
         if (player_info[0] == 1) {
            dungeon = player.wizard(dungeon, enemies, move);
         }
         else if (player_info[0] == 2) {
            dungeon = player.archer(dungeon, enemies, move);
         }
         else if (player_info[0] == 3) {
            dungeon = player.warrior(dungeon, enemies, move);
         }
         player_move = false;
      }
   }
   cout << "You have died!" << endl;
}

//Control operation of programs
int main() {
   int* player_info = player_intro();
   vector<string> enemy_names = get_names();
   HashTable enemies = enemy_maker(enemy_names, player_info);
   play_game(player_info, enemies);
}
