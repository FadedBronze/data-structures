#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

//priority queue list

PriorityQueue* create_priority_queue() {
  int max_nodes = 8;
  PriorityQueue* priority_queue = malloc(sizeof(PriorityQueue));
  QueueNode* queue_nodes = malloc(sizeof(QueueNode) * max_nodes);

  PriorityQueue queue;
  queue._start = 0;
  queue._end = 0;
  queue._max_nodes = 8;
  queue._queue = queue_nodes;

  *priority_queue = queue;

  return priority_queue;
}

int get_length_priority_queue(PriorityQueue* priority_queue) {
  if (priority_queue->_start > priority_queue->_end) {
    return priority_queue->_max_nodes - priority_queue->_start + priority_queue->_end;
  } else {    
    return priority_queue->_end - priority_queue->_start;
  }
}


QueueNode* get_nth(PriorityQueue* priority_queue, int nth) { 
  const int idx = (priority_queue->_start + nth) % priority_queue->_max_nodes;
  if (idx >= get_length_priority_queue(priority_queue)) {
    fprintf(stderr, "out of bounds\n");
    return NULL;
  } 
  QueueNode* node_ref = &priority_queue->_queue[idx];
  return node_ref;
}

QueueNode* _get_nth(PriorityQueue* priority_queue, int nth) { 
  const int idx = (priority_queue->_start + nth) % priority_queue->_max_nodes;
  QueueNode* node_ref = &priority_queue->_queue[idx];
  return node_ref;
}

void enqueue_priority_queue(PriorityQueue* priority_queue, QueueNode node) {
  const int length = get_length_priority_queue(priority_queue); 
  
  *_get_nth(priority_queue, length) = node;

  priority_queue->_end += 1; 
  
  if (length + 1 == priority_queue->_max_nodes) {
    const int max_nodes = priority_queue->_max_nodes;
    const int start = priority_queue->_start; 
    const int end = priority_queue->_end; 

    QueueNode* new_queue = malloc(sizeof(QueueNode) * max_nodes * 2);

    printf("reallocation\n");

    if (start < end) {
      memcpy(new_queue, &priority_queue->_queue[start], sizeof(QueueNode) * end); 

      priority_queue->_end -= priority_queue->_start;
      priority_queue->_start = 0;
    } else {
      const int end_difference = (max_nodes - start);

      memcpy(new_queue, &priority_queue->_queue[start], sizeof(QueueNode) * end_difference); 
      memcpy(&new_queue[end_difference], &priority_queue->_queue[0], sizeof(QueueNode) * end); 
   
      priority_queue->_end = end_difference + end;
      priority_queue->_start = 0;
    }

    priority_queue->_max_nodes *= 2;
    priority_queue->_queue = new_queue;
  }

  priority_queue->_end %= priority_queue->_max_nodes;
}

QueueNode* dequeue_priority_queue(PriorityQueue* priority_queue) {
  if (get_length_priority_queue(priority_queue) == 0) {
    fprintf(stderr, "none left\n"); 
    return NULL;
  }

  QueueNode* queue_node = _get_nth(priority_queue, 0);
  priority_queue->_start += 1;
  
  priority_queue->_start %= priority_queue->_max_nodes;

  return queue_node;
}

void insert_priority_queue(PriorityQueue* priority_queue, QueueNode node) {
  
}

void print_priority_queue(PriorityQueue* priority_queue, PrintStructFunction fn) {
  const int length = get_length_priority_queue(priority_queue);
  
  printf("Properties:\n");
  printf("  _start: %i\n", priority_queue->_start); 
  printf("  _end: %i\n", priority_queue->_end); 
  printf("  _max_nodes: %i\n", priority_queue->_max_nodes); 

  printf("\nNodes (%i): \n", length);
  for (int i = 0; i < length; i++) {
    QueueNode queue_node = *_get_nth(priority_queue, i);
    printf("  weight: %i\n", queue_node.weight); 

    if (fn == NULL) {
      printf("ref: %p\n", queue_node.ref); 
    } else {
      printf("  "); 
      fn(queue_node.ref);
    }
  }
}

//ArrayList
