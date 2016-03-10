#pragma once



/* ARM9 MEM */
#define A9_RAM_BASE       (0x08000000)
#define A9_HEAP_START     (0x08060000)
#define A9_HEAP_END       (0x080C0000)
#define	A9_STUB_ENTRY     (0x080FFE00)

/* VRAM */
#define VRAM_BASE         (0x18000000)
#define VRAM_SIZE         (0x00600000)
#define VRAM_BANK0        (0x18000000)
#define VRAM_BANK1        (0x18300000)

/* AXIWRAM */
#define CORE_SYNC_ID      (0x1FFFFFF8)
#define CORE_SYNC_PARAM   (0x1FFFFFFC)
#define A11_STUB_ENTRY    (0x1FFFFE00)

/* FCRAM */
#define FCRAM_BASE        (0x20000000)
#define FCRAM_SIZE        (0x08000000) // this is larger for New3DS, but we don't care.
#define FCRAM_HEAP_START  (FCRAM_BASE + 0x1000000)
#define FCRAM_HEAP_END    (FCRAM_HEAP_START + 0x1000000)
