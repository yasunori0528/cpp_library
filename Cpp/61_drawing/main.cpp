#include <opencv2/opencv.hpp>
#include <iostream>

int main(void)
{   
    //空の画像生成(500ピクセルの正方形の画像)
    cv::Mat image = cv::Mat::zeros(cv::Size(500,500), CV_8UC3);

    // cv::line(画像の変数, cv::Point(始点のx座標,始点のy座標),cv::Point(終点のx座標,終点のy座標), cv::Scalar(青,緑,赤),線の太さ,(連結の仕方));
    //始点(50,0),終点(400,50)に線の太さ2の４連結の直線を描画(赤)    
    cv::line(image, cv::Point(50,0),cv::Point(400,300), cv::Scalar(0,0,255),2,cv::LINE_4);
    //始点(50,50),終点(400,350)に線の太さ2の8連結の直線を描画(緑)
    cv::line(image, cv::Point(50,50),cv::Point(400,350), cv::Scalar(0,255,0),2,cv::LINE_8);

    //画像の表示
    cv::imshow("showing",image);

    //始点(50,100),終点(400,400)に線の太さ2のアンチエイリアスの直線を描画(青)
    cv::line(image, cv::Point(50,100),cv::Point(400,400), cv::Scalar(255,0,0),2,cv::LINE_AA);
   
    cv::waitKey(2000);
    //画像の表示
    cv::imshow("showing",image);
    cv::waitKey(0);
    
    return 0;
}