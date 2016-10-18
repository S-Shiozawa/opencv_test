//ステレオキャプチャー
#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <unistd.h>
#include <sys/time.h>
#include <thread>
using namespace std;


cv::VideoCapture cap1(0);	//luvcview で引数確認
cv::VideoCapture cap2(1);	//　
cv::Size capture_size( 1280, 720);      	

void* thread1(); //スレッド１
void* thread2(); //スレッド２

cv::Mat cam2image,color2;
cv::Mat cam1image,color1;

char fname1[1024];
char fname2[1024];
int key;//=cv::waitKey(1);

void setting(){
	cap1.set( CV_CAP_PROP_FRAME_WIDTH,  capture_size.width  );
	cap1.set( CV_CAP_PROP_FRAME_HEIGHT, capture_size.height );
}

setting();


int main(){
cv::namedWindow("Cam1",CV_WINDOW_AUTOSIZE);
cv::namedWindow("Cam2",CV_WINDOW_AUTOSIZE);
int num=0;
struct timeval s,t;


if (!cap1.isOpened()){
	cout << "can't open the camera" << endl;
	cout << "EnteKeyを押してください" << std::endl;
	cin.get();
	return -1;
}
if (!cap2.isOpened()){
	cout << "カメラが開けません" << endl;
	cout << "EnteKeyを押してください" << std::endl;
	cin.get();
	return -1;
}


gettimeofday(&s, NULL);   	//time

//thread tid1(thread1); 
thread tid2(thread2); // スレッド識別変数

//tid1.join();
tid2.join();


//time   
gettimeofday(&t, NULL);
//printf("%d ms\n", ((t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000));
cout<< endl ;
cout<< "num = "<< num << endl;
printf("Capture speed  = %f Hz\n",(double)num/(((t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000)/1000));
cout<< endl ;

return 0;
}


void* thread1(){
using namespace cv;
int nu=0;
for(int i=0 ;i<5;i++){

	cap1 >> color1; // カメラ１(左側のカメラの画像？)
	cvtColor(color1,cam1image,CV_RGB2GRAY);
	resize(cam1image, color1, Size(640, 360));
	imshow("Cam1",color1);
	sprintf(fname1, "./new/I1_%06d.png", nu);      //保存ファイル名に気をつける。後々めんどい。
	imwrite(fname1,cam1image);
	printf("%s\n", fname1);
	key = cv::waitKey(1);
	if (key == 'q') break; // ESCで終了
	nu++;
   }
}

void* thread2(){
using namespace cv;
int nu=0;
for(int i=0 ;i<5;i++){
	cap2.set( CV_CAP_PROP_FRAME_WIDTH,  capture_size.width  );
	cap2.set( CV_CAP_PROP_FRAME_HEIGHT, capture_size.height );
	cap2 >> color2; // カメラ２(右側のカメラの画像？)}
	cvtColor(color2,cam2image,CV_RGB2GRAY);
	resize(cam2image, color2, Size(640, 360));
	imshow("Cam2",color2);
	sprintf(fname2, "./new/I2_%06d.png", nu);      //保存ファイル名に気をつける。後々めんどい。
	imwrite(fname2,cam2image);
	printf("%s\n", fname1);
	key = cv::waitKey(1);
	if (key == 'q') break; // ESCで終了
	nu++;
   }
}





