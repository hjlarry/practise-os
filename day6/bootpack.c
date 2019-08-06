#include "bootpack.h"
#include <stdio.h>

void HariMain(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
    char s[40], mcursor[256];
    int mx, my;

    init_gdtidt();
    init_palette();
    init_screen(binfo->vram, binfo->scrnx, binfo->scrny);
    putfonts8_asc(binfo->vram, binfo->scrnx, 10, 10, COL8_FFFF00, "ABC 123");
    putfonts8_asc(binfo->vram, binfo->scrnx, 20, 30, COL8_FFFF00, "hello world");
    putfonts8_asc(binfo->vram, binfo->scrnx, 30, 50, COL8_FFFF00, "test ~!@");
    sprintf(s, "scrnx=%d", binfo->scrnx);
    putfonts8_asc(binfo->vram, binfo->scrnx, 16, 84, COL8_FFFFFF, s);

    /* 显示鼠标 */
    mx = (binfo->scrnx - 16) / 2; /* 计算画面的中心坐标*/
    my = (binfo->scrny - 28 - 16) / 2;
    init_mouse_cursor8(mcursor, COL8_008484);
    putblock8_8(binfo->vram, binfo->scrnx, 16, 16, mx, my, mcursor, 16);

    for (;;)
    {
        io_hlt();
    }
}
