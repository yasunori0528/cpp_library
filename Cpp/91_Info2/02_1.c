#include <stdio.h>
#include <math.h>

void hanoi(int n, int s, int g){
    char s_c = 'A'+s;
    char g_c = 'A'+g;
    int v = 3-s-g;
    if(n > 1){
        hanoi(n-1, s, v);
    }
    printf("%d,%c,%c\n",n,s_c,g_c);
    if(n > 1){
        hanoi(n-1, v, g);
    }
}

int main(void)
{
    int n;
    scanf("%d",&n);
    hanoi(n,0,1);
}