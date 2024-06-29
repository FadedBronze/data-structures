#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>

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
  PriorityQueue* memory = malloc(sizeof(PriorityQueue) + sizeof(QueueNode) * max_nodes);

  PriorityQueue queue;
  queue._start = 0;
  queue._end = 0;
  queue._max_nodes = 8;

  *memory = queue;

  return memory;
}

int get_length_priority_queue(PriorityQueue* priority_queue) {
  const int calc = priority_queue->_end - priority_queue->_start;
  return calc;
}

QueueNode* get_nth(PriorityQueue* priority_queue, int nth) { 
  return (QueueNode*)priority_queue + sizeof(PriorityQueue) + nth * sizeof(QueueNode);
}

void enqueue_priority_queue(PriorityQueue* priority_queue, QueueNode node) {
  *get_nth(priority_queue, priority_queue->_end) = node;
  priority_queue->_end += 1;
}

QueueNode* dequeue_priority_queue(PriorityQueue* priority_queue) {
  QueueNode* queue_node = get_nth(priority_queue, 0);
  priority_queue->_start += 1;
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
    QueueNode queue_node = *get_nth(priority_queue, i);
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
