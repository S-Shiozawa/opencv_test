//fps を計測

#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <unistd.h>
using namespace std;

int main()
{
cv::VideoCapture cap(0);
if (!cap.isOpened())
{
cout << "カメラが開けません" << endl;
cout << "EnteKeyを押してください" << std::endl;
cin.get();
return -1;
}
// カメラの解像度の設定はお使いのカメラに合わせて変更してください
cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
cap.set(CV_CAP_PROP_FRAME_HEIGHT,480);
cap.set(CV_CAP_PROP_FPS, 30);
int64 sum=0, count=0, tick=0, pretick=0;
double t, freq = cv::getTickFrequency();
double fps=0;
cv::namedWindow("カメラ１", CV_WINDOW_AUTOSIZE);
cv::Mat cam1image;
while (1)
{
cv::Mat cam1image;
cap >> cam1image;
tick = cv::getTickCount();
if (pretick > 0){
sum += tick - pretick;
count++;
}
pretick = tick;
if( sum > 0 ) fps = freq / (double)(sum / count);
cv::putText(cam1image, cv::format("FPS %f", fps), cv::Point(0, 30), cv::FONT_HERSHEY_SIMPLEX, 1.2, cv::Scalar(0, 0, 200), 2, CV_AA);
cv::imshow("カメラ１", cam1image);
int key = cv::waitKey(1);
if (key == 0x1b) break; // ESCで終了
}
return 0;
}

