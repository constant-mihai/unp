/***************************************** 

* File Name : byteorder.c

* Creation Date : 11-10-2018

* Last Modified :

* Created By : Mihai Constantin constant.mihai@googlemail.com

* License :

******************************************/

/**
 *  Purpose:
 *
 */


#include     "unp.h"
#define CPU_VENDOR_OS "Somestring"

int
main(int argc, char **argv)
{
    union {
        short   s;
        char    c[sizeof(short)];
    } un;

    un.s = 0x0102;
    printf("%s: ", CPU_VENDOR_OS);
    if (sizeof(short) == 2) {
        if (un.c[0] == 1 && un.c[1] == 2)
            printf("big-endian 0x%1x %#1x\n", un.c[0], un.c[1]);
        else if (un.c[0] == 2 && un.c[1] == 1)
            printf("little-endian 0x%02x %#04x\n", un.c[0], un.c[1]);
        else
            printf("unknown 0x%1x %#1x\n", un.c[0], un.c[1]);
    } else
        printf("sizeof(short) = %d\n", sizeof(short));


    uint32_t val = 0x01020304;
    char *str;
    str = &val;
    //uint32_t net_val = htonl(val);
    val = htonl(val);
    int i = 0;
    for ( ; i<4; i++) {
        printf(" 0x%02x", str[i]);
    }
    printf("\n");

    exit(0);
}
