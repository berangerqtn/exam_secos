#include <exam_intr.h>
#include <exam_tasks.h>
#include <exam_seg.h>
#include <asm.h>

uint32_t counter;

void set_up_intr_kernel() {
  idt_reg_t idtr;
  get_idtr(idtr);

  int_desc_t *interface_noyau = &idtr.desc[0x80];
  int_desc(&idtr.desc[0x80],gdt_seg_sel(CODE_SEG_R0,0),(offset_t)intr_kernel_handler);
  interface_noyau->dpl = 3;
  interface_noyau->type = SEG_DESC_SYS_TRAP_GATE_32;
  //interface_noyau->offset_1 = (uint32_t)intr_kernel_handler & 0xffff;
  //interface_noyau->offset_2 = (uint32_t)intr_kernel_handler >> 2*8;
  //interface_noyau->selector=gdt_seg_sel(CODE_SEG_R0,0);
  //interface_noyau->p = 1;
}


__attribute__((naked)) void intr_kernel_handler() {
  uint32_t eax;
  asm volatile ("mov (%%eax), %0" : "=r"(eax));
  asm volatile("pusha");

  debug("Compteur : %d \n", eax);

  asm volatile("popa");
  asm volatile("iret");
}

extern utask_t* tasks;
extern utasktlist_t my_tasks;

void set_up_hardware_intr(){
  idt_reg_t idtr;
  get_idtr(idtr);

  int_desc_t *interface_noyau = &idtr.desc[32];
  int_desc(&idtr.desc[32],gdt_seg_sel(1,0),(offset_t)hardware_intr_handler);
  interface_noyau->dpl = 0;
  interface_noyau->type = SEG_DESC_SYS_TRAP_GATE_32;
  //interface_noyau->offset_1 = (uint32_t)hardware_intr_handler & 0xffff;
  //interface_noyau->offset_2 = (uint32_t)hardware_intr_handler >> 2*8;
  //interface_noyau->selector=gdt_seg_sel(1,0);
  //interface_noyau->p=1;
}

void hardware_intr_handler(){
  
  outb(PIC_EOI,PIC1);

  tss_t* tss=(tss_t*)TSS_ADDR;

  if (my_tasks.current==0){
    my_tasks.current=1;
  }

  else if ((my_tasks.current==1) | (my_tasks.current==2)){

    set_ds(gdt_seg_sel(DATA_SEG_R3,SEG_SEL_USR));
    set_es(gdt_seg_sel(DATA_SEG_R3,SEG_SEL_USR));
    set_fs(gdt_seg_sel(DATA_SEG_R3,SEG_SEL_USR));
    set_gs(gdt_seg_sel(DATA_SEG_R3,SEG_SEL_USR));

    // Saving actual context
    asm volatile("mov (%%eax), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].eax));
    asm volatile("mov (%%ebx), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].ebx));
    asm volatile("mov (%%ecx), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].ecx));
    asm volatile("mov (%%edx), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].edx));
    asm volatile("mov (%%esi), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].esi));
    asm volatile("mov (%%edi), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].edi));
    asm volatile("mov (%%esp), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].esp_kernel));
    asm volatile("mov (%%ebp), %0" : "=r"(my_tasks.tasks[my_tasks.current-1].ebp));
    asm volatile ("mov 4(%%ebp), %0":"=r"(my_tasks.tasks[my_tasks.current-1].eip));

    // Preparing switch to next task
    my_tasks.current=(my_tasks.current+2)%2 +1;


    asm volatile ("mov %0, %%esp"::"r"(my_tasks.tasks[my_tasks.current-1].esp_kernel));
    asm volatile ("mov %0, %%ebp"::"r"(my_tasks.tasks[my_tasks.current-1].ebp));
    asm volatile ("mov %0, %%eax"::"r"(my_tasks.tasks[my_tasks.current-1].eax));
    asm volatile ("mov %0, %%ebx"::"r"(my_tasks.tasks[my_tasks.current-1].ebx));
    asm volatile ("mov %0, %%ecx"::"r"(my_tasks.tasks[my_tasks.current-1].ecx));
    asm volatile ("mov %0, %%edx"::"r"(my_tasks.tasks[my_tasks.current-1].edx));
    asm volatile ("mov %0, %%esi"::"r"(my_tasks.tasks[my_tasks.current-1].esi));
    asm volatile ("mov %0, %%edi"::"r"(my_tasks.tasks[my_tasks.current-1].edi));
  }
  
  // Set tss for nex task
  tss->s0.esp = my_tasks.tasks[my_tasks.current-1].esp_kernel;
  set_cr3(my_tasks.tasks[my_tasks.current-1].pgd_addr);

  
  asm volatile("push %0" ::"i"(gdt_seg_sel(4, 3)));
  asm volatile("push %0"::"r"(my_tasks.tasks[my_tasks.current-1].esp_user));
  
  // Flags
  asm volatile("pushf\n");

  asm volatile("push %0" ::"i"(gdt_seg_sel(CODE_SEG_R3, 3)));
  asm volatile("push %%ebx" ::"b"((void*)my_tasks.tasks[my_tasks.current-1].eip));

  asm volatile("iret");

}