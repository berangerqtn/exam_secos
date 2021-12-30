/**
 * Pagination
 */

#ifndef EXAM_PAGING
#define EXAM_PAGING

#define KERNEL_PGD 0x20000
#define USER1_PGD 0x30000
#define USER2_PGD 0x40000

#include <pagemem.h>
#include <cr.h>
#include <info.h>
#include <debug.h>

void enable_paging();
void show_cr3();
void print_pgd(pde32_t*tab);
void print_pte(pte32_t *pte, uint32_t index);

void set_up_paging();

void generate_pgd(pde32_t* pgd, pte32_t* ptes, int lvl);

#endif // EXAM_PAGING
