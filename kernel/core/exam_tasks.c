#include <exam_tasks.h> 
#include <exam_paging.h>
#include <asm.h>

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

utask_t* tasks;
utasktlist_t my_tasks;

__attribute__((section(".user1"))) void user1(){
    *ADDR_COUNTER=0;
    while (true)
    {
        if(mut_counter==0){
            *ADDR_COUNTER+=1;
            mut_counter=1;
        }
    } 
}

__attribute__((section(".user2"))) void user2(){
    while (true)
    {
        force_interrupts_on();
        if (mut_counter==1)
        {
            sys_counter(ADDR_COUNTER);
            mut_counter=0;
        }
    }
}

void init_tasks(){

    tasks[0].pgd_addr=USER1_PGD;
    tasks[0].function_addr = user1;
    tasks[0].eip = tasks[0].function_addr;
    tasks[0].esp_kernel = 0xffffdfff;
    tasks[0].esp_user = 0xffffcfff;

    tasks[1].pgd_addr=USER2_PGD;
    tasks[1].function_addr = user2;
    tasks[1].eip = tasks[1].function_addr;
    tasks[1].esp_kernel = 0xffffffff;
    tasks[1].esp_user = 0xffffefff;

    my_tasks.tasks=tasks;
    
    my_tasks.current=0;
}