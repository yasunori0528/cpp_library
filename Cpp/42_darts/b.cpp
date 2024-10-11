#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

random_device seed_gen;
mt19937 engine(seed_gen());
normal_distribution<> rand_normal(0.0, 1.0);

int main(){
    cout << fixed << setprecision(6);
    int N = 1000000000;
    double s = 0;
    for(int i = 0; i < N; i++){
        double x = rand_normal(engine);
        double y = rand_normal(engine);
        s += sqrt(x * x + y * y);
    }
    s /= N;
    cout << s << endl;
}