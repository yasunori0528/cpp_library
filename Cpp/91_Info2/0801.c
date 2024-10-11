#include <stdio.h>

void arrayswap(int *vp, int *wp, int n);
void arrayswap(int *vp, int *wp, int n)
{
    int temp[n];
    for(int i = 0; i < n; i++){
        temp[i] = vp[i];
    }
    for(int i = 0; i < n; i++){
        vp[i] = wp[i];
    }
    for(int i = 0; i < n; i++){
        wp[i] = temp[i];
    }
}
int main(void){
    int a[5] = {1, 1, 2, 3, 5};
    int b[5] = {2, 3, 5, 7, 11};
    int i;

    printf("Before:\n");
    for (i = 0; i < 5; i++)
    {
        printf("a[%d]= %d, b[%d]=%d \n", i, a[i], i, b[i]);
    }

    arrayswap(a, b, 5); /* ポインタa, b と要素数5を渡す */

    printf("After:\n");
    for (i = 0; i < 5; i++)
    {
        printf("a[%d]= %d, b[%d]=%d \n", i, a[i], i, b[i]);
    }

    return 0;
}