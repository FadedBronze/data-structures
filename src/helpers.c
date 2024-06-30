#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//quicksort

void print_list(int* list, int start, int end) {
  for (int i = start+1; i < end+1; i++) {
    printf("%i ",list[i]);
  }
  printf("\n");
}

void swap(int* a, int* b) {
  int temp = *a; 
  *a = *b;
  *b = temp;
}

void quick_sort(int* array, int start, int end) {
  int center = (end - start) / 2 + start;

  printf("before\n");
  print_list(array, start, end);

  if (end - start == 1) {
    return;
  }

  if (end - start == 2) {
     if (array[end] < array[start+1]) { 
       swap(&array[end], &array[start+1]);
     }

     return;
  }

  if (array[center] > array[end]) {
    swap(&array[center], &array[end]);
  }

  if (array[start+1] > array[end]) {
    swap(&array[start+1], &array[end]);
  }

  if (array[start+1] > array[center]) {
    swap(&array[start+1], &array[center]);
  }

  //if (end - start == 3) return;

  swap(&array[end], &array[center]);

  int pivot = array[end];
  printf("piv %i\n", pivot);
  
  int i = end - 1;
  int j = start + 1;  

  while (j < i) {
    while (start < i && array[i] >= pivot) {
      i--;   
    }

    while (j < end && array[j] < pivot) {
      j++;  
    }

    if (j < i) {
      swap(&array[i], &array[j]);
    }  
  }

  swap(&array[j], &array[end]);

  printf("aftair\n");
  print_list(array, start, end);
  
  quick_sort(array, start, j);
  quick_sort(array, j, end);
}

//ring buffer list

RingBuffer* create_ring_buffer() {
  int max_nodes = 8;
  RingBuffer* ring_buffer = malloc(sizeof(RingBuffer));
  RingBufferNode* nodes = malloc(sizeof(RingBufferNode) * max_nodes);

  RingBuffer buffer;
  buffer._start = 0;
  buffer._end = 0;
  buffer._max_nodes = 8;
  buffer._buffer = nodes;

  *ring_buffer = buffer;

  return ring_buffer;
}

int get_length_ring_buffer(RingBuffer* ring_buffer) {
  if (ring_buffer->_start > ring_buffer->_end) {
    return ring_buffer->_max_nodes - ring_buffer->_start + ring_buffer->_end;
  } else {    
    return ring_buffer->_end - ring_buffer->_start;
  }
}

const RingBufferNode* get_nth_ring_buffer(RingBuffer* ring_buffer, int nth) {
  const int idx = (ring_buffer->_start + nth) % ring_buffer->_max_nodes;
  if (idx >= get_length_ring_buffer(ring_buffer)) {
    fprintf(stderr, "out of bounds\n");
    return NULL;
  } 
  RingBufferNode* node_ref = &ring_buffer->_buffer[idx];
  return node_ref;
}

RingBufferNode* _get_nth(RingBuffer* ring_buffer, int nth) { 
  const int idx = (ring_buffer->_start + nth) % ring_buffer->_max_nodes;
  RingBufferNode* node_ref = &ring_buffer->_buffer[idx];
  return node_ref;
}

void enqueue_ring_buffer(RingBuffer* ring_buffer, const RingBufferNode* node) {
  const int length = get_length_ring_buffer(ring_buffer); 
  
  *_get_nth(ring_buffer, length) = *node;

  ring_buffer->_end += 1; 
  
  if (length + 1 == ring_buffer->_max_nodes) {
    const int max_nodes = ring_buffer->_max_nodes;
    const int start = ring_buffer->_start; 
    const int end = ring_buffer->_end; 

    RingBufferNode* new_buffer = malloc(sizeof(RingBufferNode) * max_nodes * 2);

    printf("reallocation\n");

    if (start < end) {
      memcpy(new_buffer, &ring_buffer->_buffer[start], sizeof(RingBufferNode) * end); 

      ring_buffer->_end -= ring_buffer->_start;
      ring_buffer->_start = 0;
    } else {
      const int end_difference = (max_nodes - start);

      memcpy(new_buffer, &ring_buffer->_buffer[start], sizeof(RingBufferNode) * end_difference); 
      memcpy(&new_buffer[end_difference], &ring_buffer->_buffer[0], sizeof(RingBufferNode) * end); 
   
      ring_buffer->_end = end_difference + end;
      ring_buffer->_start = 0;
    }

    ring_buffer->_max_nodes *= 2;
    ring_buffer->_buffer = new_buffer;
  }

  ring_buffer->_end %= ring_buffer->_max_nodes;
}

const RingBufferNode* dequeue_ring_buffer(RingBuffer* ring_buffer) {
  if (get_length_ring_buffer(ring_buffer) == 0) {
    fprintf(stderr, "none left\n"); 
    return NULL;
  }

  RingBufferNode* node = _get_nth(ring_buffer, 0);
  ring_buffer->_start += 1;
  
  ring_buffer->_start %= ring_buffer->_max_nodes;

  return node;
}

void print_ring_buffer(RingBuffer* ring_buffer, PrintStructFunction fn) {
  const int length = get_length_ring_buffer(ring_buffer);
  
  printf("Properties:\n");
  printf("  _start: %i\n", ring_buffer->_start); 
  printf("  _end: %i\n", ring_buffer->_end); 
  printf("  _max_nodes: %i\n", ring_buffer->_max_nodes); 

  printf("\nNodes (%i): \n", length);
  for (int i = 0; i < length; i++) {
    RingBufferNode node = *_get_nth(ring_buffer, i);

    if (fn == NULL) {
      printf("ref: %p\n", node.ref); 
    } else {
      printf("  "); 
      fn(node.ref);
    }
  }
}

// Priority Queue

PriorityQueue* create_priority_queue() {
  int max_nodes = 8;

  PriorityQueueNode* nodes = malloc(max_nodes * sizeof(PriorityQueueNode));
  PriorityQueue* queue = malloc(max_nodes * sizeof(PriorityQueueNode));

  queue->_nodes = nodes;
  queue->_max_nodes = max_nodes;
  queue->length = 0;

  return queue;
};

void destroy_priority_queue(PriorityQueue* priority_queue) {
  free(priority_queue->_nodes);
  free(priority_queue);
}

void swap_nodes(PriorityQueueNode* a, PriorityQueueNode* b) {
  PriorityQueueNode temp = *a; 
  *a = *b;
  *b = temp;
}

void insert_recurse(PriorityQueue* priority_queue, int idx) {
  if (idx == 0) {
    return;
  };

  int parent_idx = (idx - 1) / 2;
  PriorityQueueNode* parent = &priority_queue->_nodes[parent_idx];
  PriorityQueueNode* this = &priority_queue->_nodes[idx];

  if (this->weight > parent->weight) {
    return; 
  }

  swap_nodes(parent, this);
  insert_recurse(priority_queue, parent_idx);
}

void insert_priority_queue(PriorityQueue* priority_queue, const PriorityQueueNode* node) {
  priority_queue->_nodes[priority_queue->length] = *node;
  priority_queue->length += 1;

  insert_recurse(priority_queue, priority_queue->length-1);
};

void left_pad(const char* str, char* dest, int str_length, int dest_length) {
  int diff = dest_length - str_length; 
  memcpy(&dest[diff], str, str_length);
  memset(dest, ' ', diff); 
}

int magic(int num_size) {
  return (int)((ceil(log10(num_size))+1)*sizeof(char));
}

void print_priority_queue(PriorityQueue* priority_queue, PrintStructFunction fn) {
  printf("Properties:\n"); 
  printf("  _max_nodes: %i\n", priority_queue->_max_nodes);

  printf("\nNodes (%i):\n", priority_queue->length); 
  
  for (int i = 0; i < priority_queue->length; i++) {
    const PriorityQueueNode* node = &priority_queue->_nodes[i];
    printf("  weight: %i\n", node->weight);
    
    if (fn == NULL) {
      printf("  reference: %i\n", node->weight);
    } else {
      fn(node->ref);
    }
  }

  int last = 0;

  printf("\nTree:\n");
  for (int i = 1; i < priority_queue->length; i += i) {
    for (int j = last-1; j < i-1; j++) {
      const int node_weight = priority_queue->_nodes[j].weight;

      char print_node[16];
      char padded_node[16];
      
      sprintf(print_node, "(%d)", node_weight);
      
      left_pad(print_node, padded_node, magic(node_weight), 8);
   
      printf("%s ", padded_node);
    }
    printf("\n");
    last = i;
  } 
}

const PriorityQueueNode* pop_priority_queue(PriorityQueue* priority_queue);
const PriorityQueueNode* peek_priority_queue(PriorityQueue* priority_queue);
