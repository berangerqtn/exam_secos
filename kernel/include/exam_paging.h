/**
 * Pagination
 */

#ifndef EXAM_PAGING
#define EXAM_PAGING

#include <pagemem.h>
#include <cr.h>
#include <info.h>
#include <debug.h>

void enable_paging();
void show_cr3();
void print_pgd(pde32_t*tab);
void print_pte(pte32_t *pte, uint32_t index);

void set_up_paging();


#endif // EXAM_PAGING
