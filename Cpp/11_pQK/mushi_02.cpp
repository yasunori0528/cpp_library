#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    for(int i0 = 0; i0 < 10; i0++){
        for(int i1 = 0; i1 < 10; i1++){
            for(int i3 = 0; i3 < 10; i3++){
                for(int i4 = 0; i4 < 10; i4++){
                    int x = 1000*i0+20*10+i1;
                    int y = 1000*i3+22*10+i4;
                    int z = x*y;
                    if(z/100%10000 == n){
                        cout << x << "*" << y << "=" << z << endl;
                    }
                }
            }
        }
    }
}
