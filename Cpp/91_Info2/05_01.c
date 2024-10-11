#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    int y;
    int i;
    scanf("%d", &y);
    if(y%400 == 0) i = 1;
    else if(y%100 == 0) i = 0;
    else if(y%4 == 0) i = 1;
    else i = 0;

    if(i) printf("西暦%d年は閏年です。\n",y);
    else printf("西暦%d年は平年です。\n",y);
}