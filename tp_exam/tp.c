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

  //Test syscall for printing
  uint32_t var = 12;
  set_up_intr_kernel();
  set_up_hardware_intr();
  sys_counter(&var);

  //Segmentation setup
  set_up_paging();

  init_tasks();

  enable_paging();
    
  force_interrupts_on();
  
  while(true){
  }

}
