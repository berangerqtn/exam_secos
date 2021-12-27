#include <debug.h>
#include <exam_seg.h>
#include <info.h>

seg_desc_t create_segment(uint64_t limit, uint64_t base, uint64_t type,
                          uint64_t s, uint64_t dpl, uint64_t p, uint64_t avl,
                          uint64_t l, uint64_t d, uint64_t g) {
  seg_desc_t new_seg;
  new_seg.limit_1 = limit;
  new_seg.limit_2 = (limit >> 2 * 8);
  new_seg.base_1 = base;
  new_seg.base_2 = (base >> 2 * 8);
  new_seg.base_3 = (base >> 4 * 8);
  new_seg.type = type;
  new_seg.s = s;
  new_seg.dpl = dpl;
  new_seg.p = p;
  new_seg.avl = avl;
  new_seg.l = l;
  new_seg.d = d;
  new_seg.g = g;

  return new_seg;
}

void init_segmentation() {
  gdt_reg_t gdtr;
  seg_desc_t *table = (seg_desc_t *)0x10000;

  for (uint32_t i = 0; i < sizeof(seg_desc_t); i++) {
    *((uint8_t *)table + i) = 0;
  }

  // CODE XR RING 0
  table[1] =
      create_segment(0xFFFFF, 0x0, SEG_DESC_CODE_XR, 1, 0, 1, 0, 0, 1, 1);
  // DATA RW RING 0
  table[2] =
      create_segment(0xFFFFF, 0x0, SEG_DESC_DATA_RW, 1, 0, 1, 0, 0, 1, 1);
  // CODE XR RING 3
  table[3] =
      create_segment(0xFFFFF, 0x0, SEG_DESC_CODE_XR, 1, 3, 1, 0, 0, 1, 1);
  // DATA RW RING 3
  table[4] =
      create_segment(0xFFFFF, 0x0, SEG_DESC_DATA_RW, 1, 3, 1, 0, 0, 1, 1);
  table[5] = create_segment(sizeof(tss_t)-1, 0x0, SEG_DESC_SYS_TSS_AVL_32, 0, 0, 0b1, 0,
                            0, 0, 0);

  gdtr.desc = table;
  gdtr.limit = 6 * sizeof(seg_desc_t) - 1;
  set_gdtr(gdtr);
  printf("GDTR CREATED\n");

  set_ds(gdt_seg_sel(2, 0));
  set_es(gdt_seg_sel(2, 0));
  set_ss(gdt_seg_sel(2, 0));
  set_fs(gdt_seg_sel(2, 0));
  set_gs(gdt_seg_sel(2, 0));
  set_cs(gdt_seg_sel(1, 0));

  printf("Segment selectors set\n");
}

void print_gdtr() {
  gdt_reg_t gdtr;
  get_gdtr(gdtr);

  seg_desc_t *begin = (seg_desc_t *)gdtr.desc;
  int i = 0;

  printf("LIMIT : %d %d\n", gdtr.limit, i);
  while (begin <= (seg_desc_t *)gdtr.desc + gdtr.limit / sizeof(seg_desc_t)) {
    uint32_t addr =
        (begin->base_1) | (begin->base_2 << 16) | (begin->base_3 << 24);
    uint32_t lim = (begin->limit_1) | (begin->limit_2 << 16);

    if (begin->g) {
      lim += 1;
      lim *= 4096;
      lim -= 1;
    }
    if (begin->p) {
      printf(
          "Segment %d : Adresse : [0x%x - 0x%x] : Type de descripteur : %d\n\n",
          i, addr, lim, begin->type);
    }

    begin++;
    i++;
  }
}
