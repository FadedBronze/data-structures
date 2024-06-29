#pragma once

typedef struct QueueNode {
  const void* ref;
  int weight;
} QueueNode;

typedef struct PriorityQueue {
  int _start;
  int _end;
  int _max_nodes;
  QueueNode* _queue;
} PriorityQueue;

PriorityQueue* create_priority_queue();

QueueNode* dequeue_priority_queue(PriorityQueue* priority_queue);

void enqueue_priority_queue(PriorityQueue* priority_queue, QueueNode node);

int get_length_priority_queue(PriorityQueue* priority_queue);

void quick_sort(int* array, int start, int end);

typedef void (*PrintStructFunction) (const void* ref);

void print_priority_queue(PriorityQueue* priority_queue, PrintStructFunction fn);
