#include "data_structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

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

RingBuffer* create_ring_buffer(int node_size) {
  int max_nodes = 8;
  RingBuffer* ring_buffer = malloc(sizeof(RingBuffer));
  char* nodes = malloc(node_size * max_nodes);

  RingBuffer buffer;
  buffer._start = 0;
  buffer._end = 0;
  buffer._max_nodes = 8;
  buffer._buffer = nodes;
  buffer._node_size = node_size;
 
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

const Byte* get_nth_ring_buffer(RingBuffer* ring_buffer, int nth) {
  const int idx = (ring_buffer->_start + nth) % ring_buffer->_max_nodes;
  if (idx >= get_length_ring_buffer(ring_buffer)) {
    fprintf(stderr, "out of bounds\n");
    return NULL;
  } 
  return (Byte*)&ring_buffer->_buffer + idx * ring_buffer->_node_size;
}

Byte* _get_nth(RingBuffer* ring_buffer, int nth) {
  const int idx = (ring_buffer->_start + nth) % ring_buffer->_max_nodes;
  return (Byte*)ring_buffer->_buffer + idx * ring_buffer->_node_size;
}

void enqueue_ring_buffer(RingBuffer* ring_buffer, const Byte* node) {
  const int length = get_length_ring_buffer(ring_buffer); 
 
  printf("hi %i\n", length);
  memcpy(_get_nth(ring_buffer, length), node, ring_buffer->_node_size);
  printf("hi2\n");

  ring_buffer->_end += 1; 
  
  if (length + 1 == ring_buffer->_max_nodes) {
    const int max_nodes = ring_buffer->_max_nodes;
    const int start = ring_buffer->_start; 
    const int end = ring_buffer->_end; 

    Byte* new_buffer = malloc(ring_buffer->_node_size * max_nodes * 2);

    printf("reallocation\n");

    if (start < end) {
      memcpy(new_buffer, ring_buffer->_buffer + start * ring_buffer->_node_size, ring_buffer->_node_size * (end - start)); 

      ring_buffer->_end -= ring_buffer->_start;
      ring_buffer->_start = 0;
    } else {
      const int end_difference = (max_nodes - start);

      memcpy(new_buffer, ring_buffer->_buffer + start * ring_buffer->_node_size, ring_buffer->_node_size * end_difference); 
      memcpy(new_buffer + end_difference * ring_buffer->_node_size, ring_buffer->_buffer, ring_buffer->_node_size * end); 
   
      ring_buffer->_end = end_difference + end;
      ring_buffer->_start = 0;
    }

    ring_buffer->_max_nodes *= 2;
    ring_buffer->_buffer = new_buffer;
  }

  ring_buffer->_end %= ring_buffer->_max_nodes;
}

const Byte* dequeue_ring_buffer(RingBuffer* ring_buffer) {
  if (get_length_ring_buffer(ring_buffer) == 0) {
    fprintf(stderr, "none left\n"); 
    return NULL;
  }

  Byte* node = _get_nth(ring_buffer, 0);
  ring_buffer->_start += 1;
  
  ring_buffer->_start %= ring_buffer->_max_nodes;

  return node;
}

void print_ring_buffer(RingBuffer* ring_buffer, PrintStructFunction fn) {
  const int length = get_length_ring_buffer(ring_buffer);
  
  printf("Properties:\n");
  printf("  _node_size: %i\n", ring_buffer->_node_size); 
  printf("  _start: %i\n", ring_buffer->_start); 
  printf("  _end: %i\n", ring_buffer->_end); 
  printf("  _max_nodes: %i\n", ring_buffer->_max_nodes); 

  printf("\nNodes (%i): \n", length);
  for (int i = 0; i < length; i++) {
    Byte* node = _get_nth(ring_buffer, i);

    if (fn == NULL) {
      printf("ref: %p\n", node); 
    } else {
      printf("  "); 
      fn(node);
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
  
  if (this->weight < parent->weight) {
    return; 
  }

  swap_nodes(parent, this);
  insert_recurse(priority_queue, parent_idx);
}

void insert_priority_queue(PriorityQueue* priority_queue, const PriorityQueueNode* node) {
  priority_queue->_nodes[priority_queue->length] = *node;
  priority_queue->length += 1;
  
  if (priority_queue->length == priority_queue->_max_nodes) {
    PriorityQueueNode* new_queue_nodes = malloc(priority_queue->_max_nodes * 2 * sizeof(PriorityQueueNode));
   
    memcpy(new_queue_nodes, priority_queue->_nodes, priority_queue->_max_nodes * sizeof(PriorityQueueNode));

    priority_queue->_nodes = new_queue_nodes;
    priority_queue->_max_nodes *= 2;
  }

  insert_recurse(priority_queue, priority_queue->length-1);
};

void left_pad(const char* str, char* dest, int str_length, int dest_length) {
  int diff = dest_length - str_length; 

  memcpy(&dest[diff], str, str_length * sizeof(char));

  memset(dest, ' ', diff); 

  dest[dest_length-1] = 0;
}

int magic(int num) {
  if (num == 0 || num == 1) return 2;
  return ceil(log10(num))+1;
}

int max(int a, int b) {
  if (a > b) return a;
  return b;
}

int min(int a, int b) {
  if (a < b) return a;
  return b;
}

void print_priority_queue(PriorityQueue* priority_queue, PrintStructFunction fn) {
  printf("Properties:\n"); 
  printf("  _max_nodes: %i\n", priority_queue->_max_nodes);

  printf("\nNodes (%i):\n", priority_queue->length); 
  
  for (int i = 0; i < priority_queue->length; i++) {
    const PriorityQueueNode* node = &priority_queue->_nodes[i];
    printf("  weight: %i\n", node->weight);
    
    if (fn == NULL) {
      printf("  reference: %p\n", node->ref);
    } else {
      fn(node->ref);
    }
  }

  if (priority_queue->length == 0) return;

  int bottom_nodes = ceil(log2(priority_queue->length))+1;
  int max_node_width = magic(priority_queue->_nodes[0].weight);

  printf("%d \n", max_node_width);
  
  int i = 1;

  printf("Tree (%d depth): \n", bottom_nodes);

  while (i <= priority_queue->length) {
    int last = i;
    i *= 2;
    i = min(i, priority_queue->length+1);

    for (int j = last - 1; j < i - 1; j++) {
      int node_value = priority_queue->_nodes[j].weight;

      char node_str[16];
      sprintf(node_str, "%d", node_value); 
      
      char padded_str[16];

      left_pad(node_str, padded_str, magic(node_value), max_node_width);
      
      printf("%s ", padded_str);
    }

    printf("\n");
  }
}

#define smaller_than_left (current_node->weight < left_node->weight)
#define smaller_than_right (current_node->weight < right_node->weight)
#define left_smaller (left_node->weight < right_node->weight)

void pop_priority_queue_recurse(PriorityQueue* priority_queue, int node) {
  if (node >= priority_queue->length) return; 

  PriorityQueueNode* current_node = &priority_queue->_nodes[node];

  const int left_idx = node * 2 + 1;
  PriorityQueueNode* left_node = &priority_queue->_nodes[left_idx];
  
  const int right_idx = node * 2 + 2;
  PriorityQueueNode* right_node = &priority_queue->_nodes[right_idx];

  const bool left_null = left_idx >= priority_queue->length;
  const bool right_null = right_idx >= priority_queue->length; 

  if (!left_null && smaller_than_left && (!left_smaller || !smaller_than_right)) {
    swap_nodes(left_node, current_node); 
    pop_priority_queue_recurse(priority_queue, left_idx);
  } else if (!right_null && smaller_than_right && (left_smaller || !smaller_than_left)) {
    swap_nodes(right_node, current_node); 
    pop_priority_queue_recurse(priority_queue, right_idx);
  }
}

#undef smaller_than_right
#undef greater_than_left
#undef left_smaller

PriorityQueueNode pop_priority_queue(PriorityQueue* priority_queue) {
  if (priority_queue->length == 0) {
    PriorityQueueNode empty = {};
    return empty;
  }

  const PriorityQueueNode root = priority_queue->_nodes[0];
  priority_queue->_nodes[0] = priority_queue->_nodes[priority_queue->length-1];
  priority_queue->length -= 1; 
  pop_priority_queue_recurse(priority_queue, 0);
  return root;
};

const PriorityQueueNode* peek_priority_queue(PriorityQueue* priority_queue) {
  return &priority_queue->_nodes[priority_queue->length-1];
}

//
