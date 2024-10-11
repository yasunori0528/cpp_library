#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double sum(double *vp, int n){
    double rtn = 0;
    for(int i = 0; i < n; i++){
        rtn += vp[i];
    }
    return rtn;
}
double average(double *vp, int n){
    return sum(vp,n)/n;
}
double var(double *vp, int n){
    double rtn = 0;
    double ave_v = average(vp, n);
    for(int i = 0; i < n; i++){
        double d = vp[i]-ave_v;
        rtn += d*d;
    }
    rtn /= n;
    return rtn;
}
double cov(double *vp, double *wp, int n){
    double rtn = 0;
    double ave_v = average(vp, n);
    double ave_w = average(wp, n);
    for(int i = 0; i < n; i++){
        rtn += (vp[i]-ave_v)*(wp[i]-ave_w);
    }
    rtn /= n;
    return rtn;
}
double correl(double *vp, double *wp, int n){
    double rtn = cov(vp,wp,n)/sqrt(var(vp,n)*var(wp,n));
    return rtn;
}

int main(void){
    double population[47] = {
        529,126,124,232,98,109,186,288,195,195,733,626,1382,918,225,105,114,77,82,206,200,366,754,179,141,259,881,548,134,94,56,68,190,282,137,74,96,135,71,511,82,134,176,114,108,161,145
    };
    double area[47] = {
        834.24,96.46,152.75,72.82,116.38,93.23,137.84,60.97,64.08,63.62,37.98,51.58,21.94,24.16,125.84,42.48,41.86,41.91,44.65,135.62,106.21,77.77,51.73,57.74,40.17,46.12,19.05,84.01,36.91,47.25,35.07,67.08,71.14,84.8,61.13,41.47,18.77,56.76,71.04,49.87,24.41,41.31,74.1,63.41,77.35,91.87,22.81
    };
    
    printf("Average of poplation: %f\n", average(population,47));
    printf("Variance of poplation: %f\n", var(population,47));
    printf("Average of area: %f\n",average(area,47));
    printf("Variance of area: %f\n",var(area,47));
    printf("Correlation confficient of poplatin & area: %f\n",correl(population,area,47));
}