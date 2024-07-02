#include "src/data_structures.h"
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

//  const char* msg = "hello node\n";
// 
//  RingBuffer* ring_buffer = create_ring_buffer();
//  RingBufferNode node;
//  node.ref = (void*)msg;
//
//  srand(time(NULL)); 
//    int num = rand();
//
//  for (int i = 0; i < 200; i++) {
//    
//    enqueue_ring_buffer(ring_buffer, &node);
//
//    if (i % 5 == 0) {   
//      dequeue_ring_buffer(ring_buffer);
//    }
//
//    print_ring_buffer(ring_buffer, print_string);
//  }

  srand(time(NULL));

  const char* msg = "hello node\n";

  PriorityQueue* priority_queue = create_priority_queue();
  PriorityQueueNode node;
  node.weight = 10;
  node.ref = &msg;

  int weights[15] = {
    65.439211, 45.240230, 73.679106, 32.724546, 57.011320, 79.407455, 12.671959, 
    8.007067, 29.711250, 40.309439, 14.375607, 96.259111, 67.360604, 68.047627, 51.185252 
  };
  
  for (int i = 0; i < 15; i++) {
    double num = (double)rand();
    double max_double = RAND_MAX;
    double random_num = num/max_double * 100;
    node.weight = random_num;

    printf("%f ", random_num);

    insert_priority_queue(priority_queue, &node);
    print_priority_queue(priority_queue, NULL);
  }  

  printf("\n");

  for (int i = 0; i < 5; i++) {
    pop_priority_queue(priority_queue);
    print_priority_queue(priority_queue, NULL);
  }
}
