#include <exam_paging.h>

void enable_paging(){
  uint32_t cr0 =  get_cr0(); 
  set_cr0(cr0|CR0_PG);
}

void print_pgd(pde32_t *tab){
  for (uint32_t i=0;i<PDE32_PER_PD;i++){
    printf("Entry n%d, Addr : %x, DPL : %d\n",i, tab[i].addr<<12, tab[i].lvl);
    print_pte((pte32_t *)(tab[i].addr<<12), i);
  }
}

void print_pte(pte32_t *pte, uint32_t index){
  for (uint32_t i=0; i<PTE32_PER_PT;i++){
    printf("ID %d : AddrPhy : %x, AddrVirt : %x, DPL : %d\n", i, pte[i].addr<<12, (i | (index<<10)) << 12, pte[i].lvl);
  }
}

void show_cr3()
{
  cr3_reg_t cr3 = {.raw = get_cr3()};
  debug("CR3 = %p\n", cr3.raw);
}

void set_up_paging(){
    

}
