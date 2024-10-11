#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){   
    int MAX_X = 10000;
    int Hight = 720;
    int Width = 720;
    int Head = 100;

    int N, M; cin >> N >> M;
    vector<int> X(N);
    vector<int> Y(N);
    for(int i = 0; i < N; i++){
        cin >> X[i] >> Y[i];
        X[i] = X[i]*Hight/MAX_X;
        Y[i] = Y[i]*Width/MAX_X;
    }

    Mat image = Mat::zeros(Size(Width, Hight+Head), CV_8UC3);
    rectangle(image, Point(0,0), Point(Hight-1, Width-1+Head), Scalar(255,255,255), -1);

    for(int i = 0; i < N; i++){
        int x = X[i];
        int y = Y[i];
        rectangle(image, Point(x,y+Head), Point(x+10,y+10+Head), Scalar(0,0,0), -1);
    }
    vector<vector<int>> temp(M,vector<int>(N+1));
    vector<double> D(M);
    for(int i = 0; i < M; i++){
        for(int j = 0; j <= N; j++){
            cin >> temp[i][j];
            temp[i][j]--;
        }
        cin >> D[i];
    }

    imshow("showing", image);
    waitKey(0);

    for(int i = 0; i < M; i++){
        Mat image2  = Mat::zeros(Size(Hight, Width), CV_8UC3);
        image.copyTo(image2);
        for(int j = 0; j < N; j++){ 
            line(image2, Point(X[temp[i][j]]+5,Y[temp[i][j]]+5+Head), Point(X[temp[i][j+1]]+5,Y[temp[i][j+1]]+5+Head), Scalar(255,0,0), 1, LINE_AA);
        }
        //putText(image2, to_string(i), Point(100,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0), 1);
        putText(image2, "d = " + to_string((int)D[i]), Point(0,50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0), 2);
        imshow("showing", image2);
        waitKey(60000/M);
    }
    waitKey(0);
    return 0;
}