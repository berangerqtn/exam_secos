#include <exam_paging.h>

void enable_paging(){
  uint32_t cr0 =  get_cr0(); 
  set_cr0(cr0|CR0_PG);
}

void show_cr3()
{
  cr3_reg_t cr3 = {.raw = get_cr3()};
  debug("CR3 = %p\n", cr3.raw);
}

void init_paging(){
  int i;
  pde32_t *pgd = (pde32_t*)0x600000;
  pte32_t *ptb = (pte32_t*)0x601000;
}
