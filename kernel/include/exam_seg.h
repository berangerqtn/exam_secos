///
/// Include lié à la segmentation de notre OS
///

#ifndef EXAM_SEG
#define EXAM_SEG

#include <segmem.h>
#include <string.h>

seg_desc_t create_segment(uint64_t limit, uint64_t base, uint64_t type,
                          uint64_t s, uint64_t dpl, uint64_t p, uint64_t avl,
                          uint64_t l, uint64_t d, uint64_t g);

void init_segmentation();
 
void print_gdtr();

#endif  // EXAM_SEG
