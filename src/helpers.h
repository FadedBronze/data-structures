#pragma once

//ring buffer

typedef struct RingBufferNode {
  const void* ref;
} RingBufferNode;

typedef struct RingBuffer {
  int _start;
  int _end;
  int _max_nodes;
  RingBufferNode* _buffer;
} RingBuffer;

RingBuffer* create_ring_buffer();

void enqueue_ring_buffer(RingBuffer* ring_buffer, const RingBufferNode* node);

const RingBufferNode* dequeue_ring_buffer(RingBuffer* ring_buffer);

const RingBufferNode* get_nth_ring_buffer(RingBuffer* ring_buffer, int nth);

int get_length_ring_buffer(RingBuffer* ring_buffer);

typedef void (*PrintStructFunction) (const void* ref);

void print_ring_buffer(RingBuffer* ring_buffer, PrintStructFunction fn);

//priority queue

typedef struct PriorityQueueNode {
  int weight; 
  const void* ref;
} PriorityQueueNode;

typedef struct PriorityQueue {
  PriorityQueueNode* _nodes;
  int length;
  int _max_nodes;
} PriorityQueue;

PriorityQueue* create_priority_queue();
void destroy_priority_queue(PriorityQueue* priority_queue);

void insert_priority_queue(PriorityQueue* priority_queue, const PriorityQueueNode* node);
const PriorityQueueNode* pop_priority_queue(PriorityQueue* priority_queue);

const PriorityQueueNode* peek_priority_queue(PriorityQueue* priority_queue);

void print_priority_queue(PriorityQueue* priority_queue, PrintStructFunction fn);

//quick sort

void quick_sort(int* array, int start, int end);
