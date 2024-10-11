#include <stdio.h>
#include <math.h>

int main(void)
{
    double a,b,t,p;
    a = 1;
    b = 1.0/sqrt(2.0);
    t = 1.0/4.0;
    p = 1;
    double pi = (a+b)*(a+b)/(4.0*t);
    printf("%22.20f\n",pi);
    for(int i = 0; i < 10; i++){
        double pre_a, pre_b, pre_t, pre_p;
        pre_a = a;
        pre_b = b;
        pre_t = t;
        pre_p = p;
        a = (pre_a+pre_b)/2.0;
        b = sqrt(pre_a*pre_b);
        t = pre_t-pre_p*(pre_a-a)*(pre_a-a);
        p = 2.0*pre_p;
        pi = (a+b)*(a+b)/(4.0*t);
        printf("%22.20f\n",pi);
    }
}