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

#define KERNEL_PGD 0x20000
#define USER1_PGD 0x30000
#define USER2_PGD 0x40000

void set_up_intr_kernel();

void intr_kernel_handler();

void set_up_hardware_intr();

void hardware_intr_handler();

#endif // EXAM_INTR

