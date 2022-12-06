#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <vector>
#include "mystruct.h"
using namespace std;

struct Node {
   enemy_info data;
   Node* next;
};

/**
 *Creates the queue that acts as a dungeon
 */
class Queue {
private:
   Node* _head;
   Node* _tail;
   int size;

public:
   Queue();
   bool empty();
   void print();
   int get_size() const;
   void enqueue(const enemy_info new_key);
   void dequeue();
   enemy_info& get_enemy_at_index(const int &index);
};
#endif
