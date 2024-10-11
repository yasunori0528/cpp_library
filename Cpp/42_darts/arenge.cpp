#include <bits/stdc++.h>
using namespace std;
template <typename T> using min_priority_queue = priority_queue<T,vector<T>,greater<T>>;

random_device seed_gen;
mt19937 engine(seed_gen());
normal_distribution<> rand_normal(0.0, 1.0);

int64_t get_time(){
    struct::timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec * int64_t(1'000'000'000) + t.tv_nsec;
}

void out_time(int64_t &t_start){
    int64_t t_now = get_time();
    cout << (t_now - t_start)/1e9 << "[s]" << endl;
}

template <typename T>
bool chmin(T &a, const T& b) {
    if (a > b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;  // aをbで更新
        return true;
    }
    return false;
}

const vector<int> number = {
    20, 5, 12, 9, 14,
    11, 8, 16, 7, 19,
    3, 17, 2, 15, 10,
    6, 13, 4, 18, 1
};

const int max_score = 60;
const double max_distance = 256;
const vector<double> rudius = {0, 8.5, 22, 106, 126, 178, 198, max_distance};
const vector<int> point_coefficeint = {2, 3, 1, 3, 1, 2, 0};

const int n_angle = 20;
const int n_distance = 7;

const bool fat_bull = true;

int out_rule;
int resolution_angle;
int resolution_distance;
int n_rand;
double range;
int n_dart;

vector<vector<int>> point;
vector<vector<vector<vector<double>>>> prob;

vector<vector<tuple<double, int, int>>> dp;

void input(){
    cin >> out_rule >> resolution_angle >> resolution_distance >> n_rand >> range >> n_dart;
}

string SDT = "OSDT";
string pii_to_string(int n, int d){
    if(d == 0) return "BULL";
    if(d == 1 && fat_bull) return "BULL";
    if(d == 1) return "25";
    string s = to_string(number[n]);
    char t = SDT[point_coefficeint[d]];
    string rtn = t + s;
    return rtn;
}

void calc_point(){
    point.resize(n_angle, vector<int>(n_distance, 0));
    for(int i = 0; i < n_angle; i++){
        for(int j = 0; j < n_distance; j++){
            if(j == 0) point[i][j] = 50;
            else if(j == 1){
                if(fat_bull) point[i][j] = 50;
                else point[i][j] = 25;
            }
            else point[i][j] = number[i] * point_coefficeint[j];
        }
    }
}

void calc_prob_sub_right_20(){
    for(int i = 0; i <= resolution_angle; i++){
        for(int j = 0; j < resolution_distance; j++){
            double phi = M_PI / n_angle / resolution_angle * i;
            double r = max_distance / resolution_distance * j;

            double x = r * cos(phi);
            double y = r * sin(phi);

            for(int k = 0; k < n_rand; k++){
                double dx = rand_normal(engine) * range;
                double dy = rand_normal(engine) * range;

                double x_hit = x + dx;
                double y_hit = y + dy;
                double phi_hit;
                double r_hit = sqrt(x_hit * x_hit + y_hit * y_hit);
                if(r_hit == 0) phi_hit = 0;
                else phi_hit = atan(y_hit / x_hit);

                if(x_hit < 0) phi_hit += M_PI;

                int angle_hit = floor(phi_hit * n_angle / (M_PI * 2));
                if(angle_hit < 0) angle_hit += n_angle;
                //cout << x_hit << " " << y_hit << " " << phi_hit << " " << angle_hit << endl;
                assert(0 <= angle_hit && angle_hit < n_angle);

                int distance_hit = upper_bound(rudius.begin(), rudius.end(), r_hit) - rudius.begin() - 1;
                if(distance_hit == n_distance) distance_hit--;

                prob[i][j][angle_hit][distance_hit] += 1.0;
            }

            for(auto &k : prob[i][j]) for(auto &l : k) l /= n_rand;

            double p = 0;
            for(auto &k : prob[i][j]) for(auto &l : k) p += l;
            if(p > 1.001) cout << "A " << i << " " << j << endl;
        }
    }
}

void calc_prob_sub_left_20(){
    for(int i = 1; i < resolution_angle; i++){
        for(int j = 0; j < resolution_distance; j++){
            for(int k = 0; k < n_angle; k++){
                for(int l = 0; l < n_distance; l++){
                    prob[2 * resolution_angle - i][j][(n_angle - k) % n_angle][l] = prob[i][j][k][l];
                }
            }
            double p = 0;
            for(auto &k : prob[2 * resolution_angle - i][j]) for(auto &l : k) p += l;
            if(p > 1.001) cout << "B " << i << " " << j << endl;
        }
    }
}

void calc_prob_sub_other_number(){
    for(int i = 2 * resolution_angle; i < 2 * n_angle * resolution_angle; i++){
        for(int j = 0; j < resolution_distance; j++){
            for(int k = 0; k < n_angle; k++){
                for(int l = 0; l < n_distance; l++){
                    prob[i][j][k][l] = prob[i - 2 * resolution_angle][j][(k - 1 + n_angle) % n_angle][l];
                }
            }
            double p = 0;
            for(auto &k : prob[i][j]) for(auto &l : k) p += l;
            if(p > 1.001) cout << "C " << i << " " << j << endl;
        }
    }
}

void calc_prob(){
    prob.resize(2 * n_angle * resolution_angle, vector(resolution_distance, vector(n_angle, vector(n_distance, 0.0))));

    calc_prob_sub_right_20();
    calc_prob_sub_left_20();
    calc_prob_sub_other_number();

    /*for(int i = 0; i < 2 * n_angle * resolution_angle; i++){
        for(int j = 0; j < resolution_distance; j++){
            double p = 0;
            for(int k = 0; k < n_angle; k++){
                for(int l = 0; l < n_distance; l++){
                    cout << prob[i][j][k][l] << " ";
                    p += prob[i][j][k][l];
                }
                cout << endl;
            }
            cout << i << " " << j << " " << p << endl;
        }
    }*/
}

void calc_dp(){
    dp.resize(n_dart + 1, vector(n_dart * max_score + 1, make_tuple(0.0, 0, 0)));
    for(int i = 0; i <= n_dart; i++) dp[i][0] = {1, 0, 0};
    for(int i = 1; i <= n_dart; i++){
        for(int j = 1; j <= i * max_score; j++){
            //cout << "i: " <<  i << ", j: " << j << endl;
            tuple<double, int, int> best_throw = {0, 0, 0};
            for(int k = 0; k < 2 * n_angle * resolution_angle; k++){
                for(int l = 0; l < resolution_distance; l++){
                    double p = 0;
                    for(int m = 0; m < n_angle; m++){
                        for(int n = 0; n < n_distance; n++){
                            double p_mn = prob[k][l][m][n];
                            int s_mn = point[m][n];
                            
                            bool bust = false;
                            if(j - s_mn < 0) bust = true;
                            if(j - s_mn == 0){
                                if(out_rule == 2){
                                    if(point_coefficeint[n] != 2) bust = true;
                                }
                                if(out_rule == 3){
                                    if(point_coefficeint[n] < 2) bust = true;
                                }
                            }
                            if(j - s_mn == 1){
                                if(out_rule >= 2) bust = true;
                            }

                            if(bust) p += get<0>(dp[(i - 1) / 3 * 3][j]) * p_mn;
                            else p += get<0>(dp[i - 1][j - s_mn]) * p_mn;
                        }
                    }
                    chmax(best_throw, make_tuple(p, k, l));
                    //cout << p << " " << k << " " << l << endl;
                }
            }
            dp[i][j] = best_throw;
        }
    }
}

void output(){
    for(int i = 1; i <= n_dart; i++){
        cout << "i: " << i << endl;
        for(int j = 1; j <= i * max_score; j++){
            auto[p, k, l] = dp[i][j];
            if(p < 1e-9) continue;

            map<string, double> mp;
            for(int m = 0; m < n_angle; m++){
                for(int n = 0; n < n_distance; n++){
                    double p_mn = prob[k][l][m][n];
                    if(p_mn >= 0.001){
                        mp[pii_to_string(m, n)] += p_mn;
                    }
                }
            }

            vector<pair<double,string>> v;
            for(auto [s, p] : mp) v.push_back({p, s});
            sort(v.begin(), v.end());
            reverse(v.begin(), v.end());

            //if(v[0].second != "BULL") continue;

            cout << "j: " << j << " " << p << endl;
            for(auto [p, s] : v){
                if(s[0] == 'O') continue;
                cout << s << " " << p << endl;
            }
        }
    }
}

int main(){
    cout << fixed << setprecision(6);
    int64_t t_start = get_time();
    input();
    calc_point();
    out_time(t_start);
    calc_prob();
    out_time(t_start);
    calc_dp();
    out_time(t_start);
    output();
    out_time(t_start);
}
