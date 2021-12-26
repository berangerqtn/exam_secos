/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#include <exam_seg.h>
#include <exam_paging.h>
#include <exam_tasks.h>
#include <exam_intr.h>

extern info_t *info;

void tp()
{
  // Segmentation set up.
  init_segmentation();
  print_gdtr(); 
}
