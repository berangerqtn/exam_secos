/**
 * Tasks definition
 */

#ifndef EXAM_TASKS
#define EXAM_TASKS

#include <types.h>



void user1();

void user2();

void sys_counter(uint32_t* addr_counter);

void init_tasks();
typedef struct user_task{
    void* eip;
    uint32_t esp_user;
    uint32_t esp_kernel;
    uint32_t ebp;
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t pgd_addr; 
    uint32_t eflags;    
    void *function_addr;
}__attribute__((packed)) utask_t ;

typedef struct task_list{
    utask_t* tasks;
    uint32_t current;
}__attribute__((packed)) utasktlist_t;

// task1 incrémente compteur
// task 2 appel system print compteur

#endif // EXAM_TASKS
