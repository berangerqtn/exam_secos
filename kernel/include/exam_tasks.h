/**
 * Tasks definition
 */

#ifndef EXAM_TASKS
#define EXAM_TASKS

#include <types.h>
typedef struct user_task{
    
    
}__attribute__((packed)) utask_t ;

void task1();

void task2();

void sys_counter(uint32_t* addr_counter);

// task1 incrémente compteur
// task 2 appel system print compteur

#endif // EXAM_TASKS
