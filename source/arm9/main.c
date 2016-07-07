#include <stdio.h>
#include <string.h>
#include "types.h"
#include "mem_map.h"
#include "io.h"
#include "util.h"
#include "arm9/console.h"
#include "arm9/dev.h"
#include "arm9/fatfs/ff.h"
#include "arm9/fatfs/diskio.h"
#include "arm9/firm.h"
#include "hid.h"
#include "arm9/main.h"
#include "arm9/spiflash.h"
#include "pxi.h"

// PrintConsole for each screen
PrintConsole con_top, con_bottom;
u8 color;
// SD card FAT fs instance
FATFS sd_fs;
// same for all NAND fss
FATFS nand_twlnfs, nand_twlpfs, nand_fs;

bool	unit_is_new3ds;
u8		boot_env;

int main(void)
{
	hashCodeRoData();	// TODO: remove after debugging

	PXI_init();

	//Initialize console for both screen using the two different PrintConsole we have defined
	consoleInit(SCREEN_TOP, &con_top);
	consoleSetWindow(&con_top, 1, 1, con_top.windowWidth - 2, con_top.windowHeight - 2);
	consoleInit(SCREEN_LOW, &con_bottom);
	
	consoleSelect(&con_top);
	
	printf("\x1B[32mGood morning, hello!\e[0m\n\n");
	
	unit_detect();
	
	printf("Initializing devices...\n");
	
	devs_init();
	
	printf("Mounting filesystems...\n");
	
	mount_fs();
	
	consoleClear();
	
	enter_menu();

	unmount_fs();

	return 0;
}

void devs_init()
{
	bool res;
	const char *res_str[2] = {"\x1B[31mFailed!", "\x1B[32mOK!"};

	printf(" Initializing Wifi flash... ");
	printf("%s\e[0m\n", res_str[(res = dev_flash->init())]);
	
	if(!res) sleep_wait(0x8000000); // mmc or wififlash init fail
}

void devs_close()
{
	dev_sdcard->close();
	dev_decnand->close();
	dev_rawnand->close();
	dev_flash->close();
}

void mount_fs()
{
	FRESULT res;
	const char *res_str[2] = {"\x1B[31mFailed!", "\x1B[32mOK!"};

	printf("Mounting SD card FAT FS... ");
	res = f_mount(&sd_fs, "sdmc:", 1);
	if(res == FR_OK) printf("%s\e[0m\n", res_str[1]);
	else printf("%s ERROR 0x%d\e[0m\n", res_str[0], res);

	printf("Mounting twln FS... ");
	res = f_mount(&nand_twlnfs, "twln:", 1);
	if(res == FR_OK) printf("%s\e[0m\n", res_str[1]);
	else printf("%s ERROR 0x%d\e[0m\n", res_str[0], res);

	printf("Mounting twlp FS... ");
	res = f_mount(&nand_twlpfs, "twlp:", 1);
	if(res == FR_OK) printf("%s\e[0m\n", res_str[1]);
	else printf("%s ERROR 0x%d\e[0m\n", res_str[0], res);

	printf("Mounting CTR NAND FAT FS... ");
	res = f_mount(&nand_fs, "nand:", 1);
	if(res == FR_OK) printf("%s\e[0m\n", res_str[1]);
	else printf("%s ERROR 0x%d\e[0m\n", res_str[0], res);
	sleep_wait(0x8000000);
}

void unmount_fs()
{
	f_mount(NULL, "sdmc:", 1);
	f_mount(NULL, "twln:", 1);
	f_mount(NULL, "twlp:", 1);
	f_mount(NULL, "nand:", 1);
}

void unit_detect()
{
	printf("Detecting unit... ");
	
	if(REG_PDN_MPCORE_CLKCNT != 0)
		unit_is_new3ds = true;
		
	bool is_panda = CFG_UNITINFO != 0;
		
	printf("%s%s 3DS detected!\n", is_panda ? "Dev " : "",
									unit_is_new3ds ? "New" : "Original");
}

void boot_env_detect()
{
	boot_env = CFG_BOOTENV;
	if(boot_env > 3) boot_env = 2;
}

u8 rng_get_byte()
{
	u32 tmp = *((u32*)0x10011000); // PRNG reg
	for(u32 i = 8; i < 32; i += 8)
	{
		tmp ^= (u8)(tmp >> i);
	}
	return (u8)tmp;
}

static void loadFirmNand(void)
{
	memset((u8*)FCRAM_BASE, 0x00, 0x200);
	dev_decnand->read_sector(0x0005A980, 0x00002000, (u8*)FCRAM_BASE);
}

static bool loadFirmSd(const char *filePath)
{
	FIL file;
	UINT bytesRead = 0;
	bool res = true;


	if(f_open(&file, filePath, FA_READ) != FR_OK)
	{
		printf("Failed to open '%s'!\n", filePath);
		return false;
	}
	if(f_read(&file, (u8*)FIRM_LOAD_ADDR, FIRM_MAX_SIZE, &bytesRead) != FR_OK)
	{
		printf("Failed to read from file!\n");
		res = false;
	}
	f_close(&file);

	return res;
}
