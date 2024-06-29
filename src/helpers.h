#pragma once

typedef struct Node {
  const void* ref;
  int weight;
} QueueNode;

typedef struct RingBuffer {
  int _start;
  int _end;
  int _max_nodes;
  QueueNode* _queue;
} PriorityQueue;

PriorityQueue* create_ring_buffer();

void enqueue_ring_buffer(PriorityQueue* priority_queue, QueueNode node);

QueueNode* dequeue_ring_buffer(PriorityQueue* priority_queue);

QueueNode* get_nth_ring_buffer(PriorityQueue* priority_queue, int nth);

int get_length_ring_buffer(PriorityQueue* priority_queue);

typedef void (*PrintStructFunction) (const void* ref);

void print_ring_buffer(PriorityQueue* priority_queue, PrintStructFunction fn);

void quick_sort(int* array, int start, int end);
