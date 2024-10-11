#include <bits/stdc++.h>
using namespace std;

bool Game = true;
int N, M, startCnt, Cnt;
vector<string> Question;
vector<string> Answer;
vector<int> Frequency;
vector<int> SumFrequency;
vector<int> Uncheck;

vector<int> cntCorrect;
vector<int> cntIncorrect;
vector<int> correntStreak;

int defaultFrequency = 1048576;
int difficulty = 5;

void refleshSumFrequency(){
    for(int i = 0; i < N; i++){
        SumFrequency[i+1] = SumFrequency[i] + Frequency[i];
    }
}

void addQuestion(){
    int r = rand()%M;
    int i = Uncheck[r];

    Frequency[i] = defaultFrequency;
    refleshSumFrequency();

    swap(Uncheck[r], Uncheck[M-1]);
    Uncheck.pop_back();
    M--;
    cout << "New Question Added!" << endl;
}

void setQuestion(){
    if(SumFrequency[N-1] < defaultFrequency*(N-M+1)/1024 && M > 0) addQuestion();
    int r = rand()%SumFrequency[N-1];
    int i = upper_bound(SumFrequency.begin(), SumFrequency.end(), r) - SumFrequency.begin() -1;
    cout << Question[i] << "?" << endl;

    string a;
    cin >> a;
    if(a == "end"){
        Game = false;
        return;
    }
    else if(Answer[i] == a){
        cout << "Correct!" << endl;
        Frequency[i] = (Frequency[i]+1)/2;
        cntCorrect[i]++;
        correntStreak[i] = max(correntStreak[i],0)+1;
    }
    else{
        cout << "Incorrect! Answer : " << Answer[i] << endl;
        Frequency[i] = defaultFrequency;
        cntIncorrect[i]++;
        correntStreak[i] = min(correntStreak[i],0)-1;
    }
    refleshSumFrequency();
    Cnt++;
    if((Cnt-startCnt)%100 == 0) cout << Cnt-startCnt << "Questions solved!" << endl;
}

void input(){
    cin >> N >> Cnt;
    startCnt = Cnt;
    Question.resize(N);
    Answer.resize(N);
    Frequency.resize(N);
    SumFrequency.resize(N+1,0);
    cntCorrect.resize(N,0);
    cntIncorrect.resize(N,0);
    correntStreak.resize(N,0);
    for(int i = 0; i < N; i++){
        string q, a;
        int f, x, y, z;
        cin >> q >> a >> f;
        cin >> x >> y >> z;
        Question[i] = q;
        Answer[i] = a;
        Frequency[i] = f;
        SumFrequency[i+1] = SumFrequency[i]+f;
        cntCorrect[i] = x;
        cntIncorrect[i] = y;
        correntStreak[i] = z;
        if(f == 0) Uncheck.push_back(i);
    }
    M = Uncheck.size();

    for(int i = 0; i < 100; i++){
        cout << endl;
    }
}

void output(){
    cout << N << " " << Cnt << endl;
    for(int i = 0; i < N; i++){
        cout << Question[i] << " " << Answer[i] << " " << Frequency[i] << " ";
        cout << cntCorrect[i] << " " << cntIncorrect[i] << " " << correntStreak[i] << endl;
    }
    cout << "\n" << M << "/" << N << endl;
}

int main(){
    srand(time(NULL));
    input();
    while(Game) setQuestion();
    output();
}