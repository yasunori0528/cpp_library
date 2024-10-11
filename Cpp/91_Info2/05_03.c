#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
    double x,y;
    int i;
    srand((unsigned)time(NULL));

    double n = 1000;
    double m = 0;
    for (i=1; i<=n; i+=1)
    {
        x=rand()/(RAND_MAX+1.0);
        y=rand()/(RAND_MAX+1.0);
        if(x*x+y*y <= 1)
        {
            m++;
        }
    }
    
    double pi = 4.0*m/n;

    printf("pi=%22.20f\n", pi);

    return 0;
}
