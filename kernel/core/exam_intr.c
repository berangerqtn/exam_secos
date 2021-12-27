#include <exam_intr.h>

void set_up_intr_kernel() {
  idt_reg_t idtr;
  get_idtr(idtr);

  int_desc_t *interface_noyau = &idtr.desc[0x80];
  interface_noyau->offset_1 = (uint32_t)intr_kernel_handler & 0xffff;
  interface_noyau->offset_2 = (uint32_t)intr_kernel_handler >> 2*8;
  interface_noyau->dpl = 3;
  interface_noyau->selector=gdt_seg_sel(1,0);
  interface_noyau->type = SEG_DESC_SYS_TRAP_GATE_32;
  interface_noyau->p = 1;
}


__attribute__((naked)) void intr_kernel_handler() {
  uint32_t eax;
  asm volatile ("mov (%%eax), %0" : "=r"(eax));
  // asm volatile("mov (%%esp), %0" : "=r"(eip));  // On récupère la valeur d'eip
  asm volatile("pusha");

  debug("Compteur : %d \n", eax);

  asm volatile("popa");
  asm volatile("iret");
}

void set_up_hardware_intr(){
  idt_reg_t idtr;
  get_idtr(idtr);

  int_desc_t *interface_noyau = &idtr.desc[32];
  interface_noyau->offset_1 = (uint32_t)hardware_intr_handler & 0xffff;
  interface_noyau->offset_2 = (uint32_t)hardware_intr_handler >> 2*8;
  interface_noyau->dpl = 0;
  interface_noyau->selector=gdt_seg_sel(1,0);
  interface_noyau->type = SEG_DESC_SYS_TRAP_GATE_32;
  interface_noyau->p=1;
  //int_desc(&idtr.desc[32],gdt_seg_sel(1,0),(offset_t)hardware_intr_handler);
}

__attribute__((naked)) void hardware_intr_handler(){
  asm volatile("pusha");
  asm volatile("push %ebp");
  asm volatile("mov %esp, %ebp");
  
  debug("On debug\n");
  outb(PIC_EOI,PIC1);
  
  asm volatile("leave");
  asm volatile("popa");
  asm volatile("iret");

}