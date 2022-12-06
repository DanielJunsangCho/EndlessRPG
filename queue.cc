#include "queue.h"

/**
 * Constructs an empty queue with no arguments
 */
Queue::Queue() {
   _head = nullptr;
   _tail = nullptr;
   size = 0;
}

/**
 * Checks if the dungeon is empty
 * @returns true if empty, false if not
 */
bool Queue::empty() {
   if (_head == nullptr) {
      return true;
   }
   return false;
}

/**
 * Prints the order of enemies in the dungeon
 */
void Queue::print() {
     if (empty()) {
         cout << "There are no monsters awaiting you!" << endl;
         return;
     }
     cout << "Monsters in the dungeon: ";
     Node* current = _head;
     while (current != nullptr) {
         cout << current->data.name << " ";
         current = current->next;
     }
     cout << endl;
}

/**
 * @returns the size of the dungeon
 */
int Queue::get_size() const{
   return size;
}

/**
 * Adds an enemy to the end of dungeon
 * @param new_key: new enemy to be enqueued
 */
void Queue::enqueue(const enemy_info new_key) {
   if (_head == nullptr) {
      Node* temp = new Node{new_key, nullptr};
      _head = temp;
      _tail = temp;
      size++;
   }
   else {
      Node* temp = new Node{new_key, nullptr};
      _tail->next = temp;
      _tail = _tail->next;
      size++;
   }
}

/**
 * Removes enemy from dungeon after they die
 */
void Queue::dequeue() {
   if (size == 1) {
      _head = nullptr;
      _tail = nullptr;
      size--;
   }
   else {
      _head = _head->next;
      size--;
   }
}

/**
 * Retrieves enemy at certain point in dungeon
 * @param index: location of the enemy
 * @returns the enemy at the index
 */
enemy_info& Queue::get_enemy_at_index(const int &index) {
   Node* current = _head;
   for (int i = 0; i < index; i++) {
      current = current->next;
   }
   return current->data;
}
