#include <exam_paging.h>

void enable_paging(){
  uint32_t cr0 =  get_cr0(); 
  set_cr0(cr0|CR0_PG);
}

void print_pgd(pde32_t *tab){
  for (uint32_t i=1023;i<PDE32_PER_PD;i++){
    printf("Entry n%d, Addr : %x, LVL : %d\n",i, tab[i].addr<<12, tab[i].lvl);
    print_pte((pte32_t *)(tab[i].addr<<12), i);
  }
}

void print_pte(pte32_t *pte, uint32_t index){
  for (uint32_t i=0; i<PTE32_PER_PT;i++){
    printf("ID %d : AddrPhy : %x, AddrVirt : %x, LVL : %d\n", i, pte[i].addr<<12, (i | (index<<10)) << 12, pte[i].lvl);
  }
}

void show_cr3()
{
  cr3_reg_t cr3 = {.raw = get_cr3()};
  debug("CR3 = %p\n", cr3.raw);
}

void set_up_paging(){

  pde32_t* pgd_kernel = (pde32_t*)0x20000;
  pte32_t* kernel_ptbs = (pte32_t*)0x400000;

  pde32_t* pgd_u1 = (pde32_t*)0x30000;
  pte32_t* user1_ptbs = (pte32_t*)0x800000;

  pde32_t* pgd_u2 = (pde32_t*)0x40000;
  pte32_t* user2_ptbs = (pte32_t*)0x1200000;

  generate_pgd(pgd_kernel, kernel_ptbs , PG_KRN);
  generate_pgd(pgd_u1,user1_ptbs,PG_USR);
  generate_pgd(pgd_u2,user2_ptbs,PG_USR);

  pg_set_entry(&user1_ptbs[1023*1024 + 1021], PG_KRN|PG_RW, 1021 + (1023<<10));
  pg_set_entry(&user2_ptbs[1023*1024 + 1023], PG_KRN|PG_RW, 1023 + (1023<<10));
    
  //print_pgd(pgd_kernel);
  //print_pgd(pgd_u1);
  //print_pgd(pgd_u2);

  set_cr3(pgd_kernel);

}

void generate_pgd(pde32_t* pgd, pte32_t* ptes, int lvl){

  for (uint32_t j=0;j<1024;j++){
    for (uint32_t i=0;i<1024;i++){
      pg_set_entry(&ptes[i + j*1024], lvl|PG_RW, i+(j<<10));
    }
    memset((void*)&pgd[j], 0, PAGE_SIZE);
    pg_set_entry(&pgd[j], lvl|PG_RW, page_nr(&ptes[j*1024]));
  }

}