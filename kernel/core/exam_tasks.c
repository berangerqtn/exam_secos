#include <exam_tasks.h> 
#include <exam_paging.h>

// Variables globales à mettre dans la mémoire partagée.
uint32_t* ADDR_COUNTER = (uint32_t*)0x8888;
uint32_t mut_counter;

void sys_counter(uint32_t* addr_counter){
    asm volatile ("mov %0, %%eax" :: "r"(addr_counter));
    asm volatile ("int $0x80");
}

void sys_counter_incr(uint32_t* addr_counter){
    (*addr_counter)++;
}

utask_t tasks[2];

void init_task(){
    tasks[0].pgd_addr=USER1_PGD;
    tasks[1].pgd_addr=USER2_PGD;
}

__attribute__((section(".user1"))) void user1(){
    *ADDR_COUNTER=0;
    while (true)
    {
        if(mut_counter==0){
            mut_counter=1;
            sys_counter_incr(ADDR_COUNTER);
            mut_counter=0;
        }
    } 
}

__attribute__((section(".user2"))) void user2(){
    while (true)
    {
        if (mut_counter==0)
        {
            mut_counter=1;
            sys_counter(ADDR_COUNTER);
            mut_counter=0;
        }   
    }
}


