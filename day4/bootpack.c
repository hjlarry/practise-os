void io_hlt(void);
void write_mem8(int addr, int data);

void HariMain(void)
{
    int i;
    char *p; /* 变量p用于BYTE型地址 */
    for(i=0xa0000;i<=0xaffff;i++){
        // write_mem8(i, 15); /* MOV BYTE [i],15 */ 白屏
        // write_mem8(i, i&0x0f); 条纹
        p = i; /* 带入地址，和write_mem8(i, i&0x0f)等效 */
        *p = i&0x0f;
    }
    for (;;){
        io_hlt();
    }
}