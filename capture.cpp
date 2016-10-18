//モノラルでのキャプチャー
//newって言うフォルダを作ってそこにぶち込む

#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <unistd.h>
#include <sys/time.h>

using namespace std;

 

int main(int argc, char* argv[])
{
struct timeval s, t;


  cv::VideoCapture capture(0);
  cv::Size capture_size( 640, 480);      	//1280x720(20hz)  1920x1080(10hz) 1344 376
  capture.set( CV_CAP_PROP_FRAME_WIDTH,  capture_size.width  );
 capture.set( CV_CAP_PROP_FRAME_HEIGHT, capture_size.height );
//  capture.set( CV_CAP_PROP_FPS, 30 );
//  capture.set( CV_CAP_PROP_AUTO_EXPOSURE, 0 );
//  capture.set( CV_CAP_PROP_EXPOSURE, 100 );
  

  cv::Mat frame,color,kido1,kido2,kido3,kido4;
//char windowNameCapture[]="Capture";

cv::namedWindow("Capture",CV_WINDOW_AUTOSIZE);
int num = 0;
char fname[1024];
int shuter=2;

gettimeofday(&s, NULL);   	//time

//ステ処理
capture>>kido1;
capture>>kido2;
capture>>kido3;
capture>>kido4;
//

	while(1){
//	  cin >> shuter;
	  capture >> color;
          cv::cvtColor(color,frame,CV_RGB2GRAY);
	  cv::imshow( "Capture", frame );	//ウィンドウ表示させようがさせまいがfpsは落ちない//7/15むしろ表示した方が速い
	  cv::resize(frame,frame,cv::Size(),0.5,0.5);
	  cv::threshold(frame, frame, 200, 255, cv::THRESH_BINARY|cv::THRESH_OTSU);  //cvtcolor で一旦取り込んでからBynary化
	printf("aaaaaa\n\n");
	//	if(num%10000==0){
	sprintf(fname, "./new/I1_%09d.png", num);      //保存ファイル名に気をつける。後々めんどい。
	printf("%s\n", fname);
	cv::imwrite(fname,frame);
	//}
	//usleep(200000);					//usleep milion//
	num++;
	//cv::waitKey(0);
	char ch =cv::waitKey(1);            //シャッター方式０　その他1
	   if ( ch == 'q' ){ break;}
	}


cv::destroyAllWindows();   
//time   
gettimeofday(&t, NULL);
//printf("%d ms\n", ((t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000));
cout<< endl ;
printf("Capture speed  = %f Hz\n",(double)num/(((t.tv_sec - s.tv_sec) * 1000 + (double)(t.tv_usec - s.tv_usec) / 1000)/1000));
cout<< endl ;
return 0;

}
