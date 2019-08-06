#include "bootpack.h"
#include <stdio.h>

extern struct FIFO8 keyfifo;

void HariMain(void)
{
    struct BOOTINFO *binfo = (struct BOOTINFO *)ADR_BOOTINFO;
    char s[40], mcursor[256], keybuf[32];
    int mx, my, i;

    init_gdtidt();
    init_pic();
    io_sti(); /* IDT/PIC的初始化已经完成，于是开放CPU的中断 */

    io_out8(PIC0_IMR, 0xf9); /* 开放PIC1和键盘中断(11111001) */
    io_out8(PIC1_IMR, 0xef); /* 开放鼠标中断(11101111) */

    fifo8_init(&keyfifo, 32, keybuf);
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
        io_cli();
        if (fifo8_status(&keyfifo) == 0)
        {
            io_stihlt();
        }
        else
        {
            i = fifo8_get(&keyfifo);
            io_sti();
            sprintf(s, "%02X", i);
            boxfill8(binfo->vram, binfo->scrnx, COL8_008484, 0, 16, 15, 31);
            putfonts8_asc(binfo->vram, binfo->scrnx, 0, 16, COL8_FFFFFF, s);
        }
    }
}
