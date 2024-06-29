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
 
  PriorityQueue* priority_queue = create_priority_queue();
  QueueNode node;
  node.weight = 10;
  node.ref = (void*)msg;


  srand(time(NULL));

  while (1) {
    int num = rand();
    
    enqueue_priority_queue(priority_queue, node);
    node.weight = num;
  
    dequeue_priority_queue(priority_queue);

    print_priority_queue(priority_queue, print_string);
  } 
}
