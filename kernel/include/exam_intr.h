/**
 * Interruptions handling
 */

#ifndef EXAM_INTR
#define EXAM_INTR

#include <intr.h>
#include <debug.h>

void set_up_intr_noyau();

void intr_kernel_handler(uint32_t* user);

void set_up_hardware_intr();

void hardware_intr_handler();

#endif // EXAM_INTR
