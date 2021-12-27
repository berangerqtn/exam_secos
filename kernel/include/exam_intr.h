/**
 * Interruptions handling
 */

#ifndef EXAM_INTR
#define EXAM_INTR

#include <intr.h>
#include <debug.h>
#include <cr.h>
#include <io.h>
#include <pic.h>

void set_up_intr_kernel();

void intr_kernel_handler();

void set_up_hardware_intr();

void hardware_intr_handler();

#endif // EXAM_INTR

