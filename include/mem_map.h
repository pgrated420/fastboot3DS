#pragma once



#ifdef ARM9
/* ITCM */
#define ITCM_BASE            (0x00000000)
#define ITCM_KERNEL_MIRROR   (0x01FF8000)
#define ITCM_BOOT9_MIRROR    (0x07FF8000)
#define ITCM_SIZE            (0x00008000) // 32 KB
#endif


#ifdef ARM11
/* ARM11 bootrom */
#define BOOT11_BASE          (0x00000000)
#define BOOT11_MIRROR1       (0x00010000)
#define BOOT11_SIZE          (0x00010000) // 64 KB
#endif


#ifdef ARM9
/* ARM9 RAM */
#define A9_RAM_BASE          (0x08000000)
#define A9_RAM_N3DS_EXT_BASE (A9_RAM_BASE + 0x100000)
#define A9_RAM_SIZE          (0x00100000) // 1 MB
#define A9_RAM_N3DS_EXT_SIZE (0x00080000) // 512 KB
#endif


/* IO mem */
#define IO_MEM_BASE          (0x10000000)
#define IO_MEM_ARM9_ONLY     (IO_MEM_BASE)
#define IO_MEM_ARM9_ARM11    (IO_MEM_BASE + 0x100000)
#define IO_MEM_ARM11_ONLY    (IO_MEM_BASE + 0x200000)


#ifdef ARM11
/* ARM11 MPCore private region */
#define MPCORE_PRIV_REG_BASE (0x17E00000)
#define MPCORE_PRIV_REG_SIZE (0x00002000) // 8 KB


/* L2C-310 Level 2 Cache Controller */
#define L2_CACHE_CONTR_BASE  (0x17E10000)
#define L2_CACHE_CONTR_SIZE  (0x00001000) // 4 KB
#endif


/* VRAM */
#define VRAM_BASE            (0x18000000)
#define VRAM_SIZE            (0x00600000)
#define VRAM_BANK0           (VRAM_BASE)
#define VRAM_BANK1           (VRAM_BASE + 0x300000)


/* DSP mem */
#define DSP_MEM_BASE         (0x1FF00000)
#define DSP_MEM_SIZE         (0x00080000) // 512 KB


/* AXIWRAM */
#define AXIWRAM_BASE         (0x1FF80000)
#define AXIWRAM_SIZE         (0x00080000) // 512 KB


/* FCRAM */
#define FCRAM_BASE           (0x20000000)
#define FCRAM_N3DS_EXT_BASE  (FCRAM_BASE + 0x8000000)
#define FCRAM_SIZE           (0x08000000) // 128 MB
#define FCRAM_N3DS_EXT_SIZE  (FCRAM_SIZE)


#ifdef ARM9
/* DTCM */
#define DTCM_BASE            (0xFFF00000)
#define DTCM_SIZE            (0x00004000) // 16 KB


/* ARM9 bootrom */
#define BOOT9_BASE           (0xFFFF0000)
#define BOOT9_SIZE           (0x00010000) // 64 KB
#endif


#ifdef ARM11
/* ARM11 bootrom */
#define BOOT11_MIRROR2       (0xFFFF0000)
#endif



/* Custom mappings */
#ifdef ARM9
#define	A9_STUB_ENTRY        (A9_RAM_BASE + A9_RAM_SIZE - 0x200)
#define A9_HEAP_SIZE         (0x96000) // 600 KB
#define A9_STACK_START       (DTCM_BASE)
#define A9_STACK_END         (DTCM_BASE + DTCM_SIZE)
#endif


#ifdef ARM11
#define A11_STUB_ENTRY       (AXIWRAM_BASE + AXIWRAM_SIZE - 0x200)
#define A11_STACK_START      (A11_STUB_ENTRY - 0x3FE00) // Half of AXIWRAM
#define A11_STACK_END        (A11_STUB_ENTRY)
#endif
