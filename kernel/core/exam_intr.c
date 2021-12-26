#include <exam_intr.h>

void set_up_intr_noyau() {
  idt_reg_t idtr;
  get_idtr(idtr);

  int_desc_t *interface_noyau = &idtr.desc[0x80];
  interface_noyau->offset_1 = (uint32_t)intr_kernel_handler & 0xffff;
  interface_noyau->offset_2 = (uint32_t)intr_kernel_handler >> 2*8;
  interface_noyau->dpl = 3;
}


__attribute__((naked)) void intr_kernel_handler(uint32_t*user) {
  uint32_t eip;
  asm volatile("mov (%%esp), %0" : "=r"(eip));  // On récupère la valeur d'eip
  asm volatile("pusha");
  /**
   * To code
   **/
  
  debug("On debug : %d \n", user);

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

}

void hardware_intr_handler(){
  uint32_t eip;
  asm volatile("mov (%%esp), %0" : "=r"(eip));  // On récupère la valeur d'eip
  asm volatile("pusha");
  /**
   * To code
   **/
  
  debug("On debug : %d \n");

  asm volatile("popa");
  asm volatile("iret");

}