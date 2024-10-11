#include <bits/stdc++.h>
using namespace std;

template <typename T> bool next_combination(const T first, const T last, int k) {
    const T subset = first + k;
    // empty container | k = 0 | k == n 
    if (first == last || first == subset || last == subset) {
        return false;
    }
    T src = subset;
    while (first != src) {
        src--;
        if (*src < *(last - 1)) {
            T dest = subset;
            while (*src >= *dest) {
                dest++;
            }
            iter_swap(src, dest);
            rotate(src + 1, dest + 1, last);
            rotate(subset, subset + (last - dest) - 1, last);
            return true;
        }
    }
    // restore
    rotate(first, subset, last);
    return false;
}

int main(){

    int t_start = time(NULL);
    int t_0 = time(NULL);
    int t_interval = 3600;

    vector<vector<vector<int>>> d_list(3,vector<vector<int>>(0,vector<int>(3)));
    for(int i = 0; i < 10; i++){
        for(int j = i; j < 10; j++){
            int k = i + j;
            //>
            if(k < 9){
                d_list[2].push_back({i, j, k+1});
            }
            //^
            else{
                d_list[0].push_back({i, j, k-10+1});
            }
            //-
            if(k < 10){
                d_list[0].push_back({i, j, k});
            }
            //<
            else{
                d_list[1].push_back({i, j, k-10});
            }
        }
    }
    
    int cnt = 0;
    cout << "///start:i=" << 5 << endl;
    do{
        bool b1 = true;
        map<int, int> list_a_1;
        map<int, int> list_b_1;
        for(int j = 0; j < 5; j++){
            for(int k = 0; k < 3; k++){
                if(k != 2) list_a_1[d_list[1][j][k]]++;
                else list_b_1[d_list[1][j][k]]++;
            }
        }
        for(int j = 0; j < 10; j++){
            if(list_a_1[j] > 2){
                b1 = false;
                break;
            }
            if(list_b_1[j] > 1){
                b1 = false;
                break;
            }
        }
        if(b1){
            do{
                bool b2 = true;
                map<int, int> list_a_2 = list_a_1;
                map<int, int> list_b_2 = list_b_1;
                for(int j = 0; j < 5; j++){
                    for(int k = 0; k < 3; k++){
                        if(k != 2) list_a_2[d_list[2][j][k]]++;
                        else list_b_2[d_list[2][j][k]]++;
                    }
                }
                for(int j = 0; j < 10; j++){
                    if(list_a_2[j] > 2){
                        b2 = false;
                        break;
                    }
                    if(list_b_2[j] > 1){
                        b2 = false;
                        break;
                    }
                }
                if(b2){
                    cnt++;
                    if(cnt%1000 == 0) {
                        int t_now = time(NULL);
                        cout << "///" << cnt << ",time:" << t_now-t_start << endl;
                    }
                    for(int j = 0; j < 5; j++){
                        cout << "(" << d_list[1][j][0] << "," << d_list[1][j][1] << "," << d_list[1][j][2] << "),";
                    }
                    for(int j = 0; j < 5; j++){
                        cout << "(" << d_list[2][j][0] << "," << d_list[2][j][1] << "," << d_list[2][j][2] << "),";
                    }
                    cout << endl;
                }
            }while(next_combination(d_list[2].begin(), d_list[2].end(), 5));
        }        
    }while(next_combination(d_list[1].begin(), d_list[1].end(), 5));

    //i : <>
    for(int i = 1; i <= 4; i++){
        cout << "///start:i=" << i << endl;
        do{
            bool b1 = true;
            map<int, int> list_a_1;
            map<int, int> list_b_1;
            for(int j = 0; j < i; j++){
                for(int k = 0; k < 3; k++){
                    if(k != 2) list_a_1[d_list[1][j][k]]++;
                    else list_b_1[d_list[1][j][k]]++;
                }
            }
            for(int j = 0; j < 10; j++){
                if(list_a_1[j] > 2){
                    b1 = false;
                    break;
                }
                if(list_b_1[j] > 1){
                    b1 = false;
                    break;
                }
            }
            if(b1){
                do{
                    bool b2 = true;
                    map<int, int> list_a_2 = list_a_1;
                    map<int, int> list_b_2 = list_b_1;
                    for(int j = 0; j < i; j++){
                        for(int k = 0; k < 3; k++){
                            if(k != 2) list_a_2[d_list[2][j][k]]++;
                            else list_b_2[d_list[2][j][k]]++;
                        }
                    }
                    for(int j = 0; j < 10; j++){
                        if(list_a_2[j] > 2){
                            b2 = false;
                            break;
                        }
                        if(list_b_2[j] > 1){
                            b2 = false;
                            break;
                        }
                    }
                    if(b2){
                        do{

                            bool b3 = true;
                            map<int, int> list_a_3 = list_a_2;
                            map<int, int> list_b_3 = list_b_2;
                            for(int j = 0; j < 10-2*i; j++){
                                for(int k = 0; k < 3; k++){
                                    if(k != 2) list_a_3[d_list[0][j][k]]++;
                                    else list_b_3[d_list[0][j][k]]++;
                                }
                            }
                            for(int j = 0; j < 10; j++){
                                if(list_a_3[j] > 2){
                                    b3 = false;
                                    break;
                                }
                                if(list_b_3[j] > 1){
                                    b3 = false;
                                    break;
                                }
                            }
                            if(b3){
                                for(int j = 0; j < i; j++){
                                    cout << "(" << d_list[1][j][0] << "," << d_list[1][j][1] << "," << d_list[1][j][2] << "),";
                                }
                                for(int j = 0; j < i; j++){
                                    cout << "(" << d_list[2][j][0] << "," << d_list[2][j][1] << "," << d_list[2][j][2] << "),";
                                }
                                for(int j = 0; j < 10-2*i; j++){
                                    cout << "(" << d_list[0][j][0] << "," << d_list[0][j][1] << "," << d_list[0][j][2] << "),";
                                }
                                cout << endl;
                                cnt++;
                                if(cnt%1000 == 0) {
                                    int t_now = time(NULL);
                                    cout << "///" << cnt << ",time:" << t_now-t_start << endl;
                                }
                            }
                        }while(next_combination(d_list[0].begin(), d_list[0].end(), 10-2*i));
                    }
                }while(next_combination(d_list[2].begin(), d_list[2].end(), i));
            }            
        }while(next_combination(d_list[1].begin(), d_list[1].end(), i));
    }

    int t_end = time(NULL);
    cout << "///" << t_end - t_start << "[s]" << endl;
}