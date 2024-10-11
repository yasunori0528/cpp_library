#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    int i, j, temp;
    double x[10];

    for(i = 0; i < 10; i++){
        scanf("%lf", &x[i]);
    }

    for(i = 9; i >= 0; i--){
        for(j = 0; j < i; j++){
            //(x[j],x[j+1])
            if(x[j] < x[j+1]){
                temp = x[j];
                x[j] = x[j+1];
                x[j+1] = temp;
            }
        }
    }

    for(i = 0; i < 10; i++){
        printf("%lf ", x[i]);
    }
    printf("\n");
}