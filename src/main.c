#include "helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void print_string(const void* ref) {
  char* msg = (char*)ref;
  printf("%s\n", msg);
}

int main() {
//  int nums[10] = { 0, 1, 5, 8, 8, 4, 2, 5, 3, 1 };
//
//  srand(time(NULL));
//
//  for (int i = 0; i < 10; i++) {
//    double num = (double)rand();
//    double max_double = RAND_MAX;
//    nums[i] = num/max_double * 10;
//  }
//
//  printf("pre\n");
//  for (int i = 0; i < 10; i++) {
//    printf("%i ", nums[i]);
//  } 
//  printf("\n");
//
//  quick_sort(nums, -1, 9);
//
//  printf("reulst\n");
//  for (int i = 0; i < 10; i++) {
//    printf("%i ", nums[i]);
//    printf("\n");
//  } 

  const char* msg = "hello node\n";
 
  PriorityQueue* ring_buffer = create_ring_buffer();
  QueueNode node;
  node.weight = 10;
  node.ref = (void*)msg;

  srand(time(NULL)); 

  for (int i = 0; i < 200; i++) {
    int num = rand();
    
    enqueue_ring_buffer(ring_buffer, node);
    node.weight = num;

    if (i % 5 == 0) {   
      dequeue_ring_buffer(ring_buffer);
    }

    print_ring_buffer(ring_buffer, print_string);
  } 
}
