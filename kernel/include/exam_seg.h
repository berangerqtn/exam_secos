///
/// Include lié à la segmentation de notre OS
///

#ifndef EXAM_SEG
#define EXAM_SEG

#include <segmem.h>
#include <string.h>

#define CODE_SEG_R0 1
#define DATA_SEG_R0 2
#define CODE_SEG_R3 3 
#define DATA_SEG_R3 4
#define TSS_SEG 5

#define TSS_ADDR 0x340000

seg_desc_t create_segment(uint32_t limit, uint32_t base, uint32_t type,
                          uint32_t s, uint32_t dpl, uint32_t p, uint32_t avl,
                          uint32_t l, uint32_t d, uint32_t g);

void init_segmentation();
 
void print_gdtr();

#endif  // EXAM_SEG
