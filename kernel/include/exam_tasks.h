/**
 * Tasks definition
 */

#ifndef EXAM_TASKS
#define EXAM_TASKS

#include <types.h>
typedef struct user_task{
    uint32_t eip;
    uint32_t esp_user;
    uint32_t esp_kernel;
    uint32_t pgd_addr;     
}__attribute__((packed)) utask_t ;

void init_task();

void task1();

void task2();

void sys_counter(uint32_t* addr_counter);

// task1 incrémente compteur
// task 2 appel system print compteur

#endif // EXAM_TASKS
