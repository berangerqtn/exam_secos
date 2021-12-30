/* GPLv2 (c) Airbus */
#include <debug.h>
#include <info.h>
#include <asm.h>
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


  uint32_t var = 12;
  set_up_intr_kernel();
  set_up_hardware_intr();
  sys_counter(&var);
  set_up_paging();  
  force_interrupts_on();
  
  while(true){  

  }

  // Paging set up.
  //set_up_paging();
  //enable_paging();

}
