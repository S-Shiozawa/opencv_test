//ステレオキャプチャー
#include <iostream>
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <unistd.h>
#include <sys/time.h>
using namespace std;
using namespace cv;

int main(){
	int num=0;
	struct timeval s, t;
	cv::VideoCapture cap1(0);	//luvcview で引数確認
	cv::VideoCapture cap2(1);	//　"
	cv::namedWindow("Cam1",CV_WINDOW_AUTOSIZE);
	cv::namedWindow("Cam2",CV_WINDOW_AUTOSIZE);
   moveWindow("Cam1",700,0);
	moveWindow("Cam2",0,0);
	if (!cap1.isOpened())
	{
		cout << "can't open the camera" << endl;
		cout << "EnteKeyを押してください" << std::endl;
		cin.get();
		return -1;
	}
	if (!cap2.isOpened())
	{
		cout << "カメラが開けません" << endl;
		cout << "EnteKeyを押してください" << std::endl;
		cin.get();
		return -1;
	}
	cv::Size capture_size( 1280, 720);      	//1280x720(20hz)  1920x1080(10hz)


//	cap1.set( CV_CAP_PROP_FOURCC, CV_FOURCC('M','J','P','G') );
//	cap2.set( CV_CAP_PROP_FOURCC, CV_FOURCC('M','J','P','G') );
	cap1.set( CV_CAP_PROP_FPS, 30 );
	cap2.set( CV_CAP_PROP_FPS, 30 );
	cap1.set( CV_CAP_PROP_FRAME_WIDTH,  capture_size.width  );
	cap1.set( CV_CAP_PROP_FRAME_HEIGHT, capture_size.height );
	cap2.set( CV_CAP_PROP_FRAME_WIDTH,  capture_size.width  );
	cap2.set( CV_CAP_PROP_FRAME_HEIGHT, capture_size.height );

	char fname1[1024];
	char fname2[1024];
	gettimeofday(&s, NULL);   	//time
	int key;//=cv::waitKey(1);
	cv::Mat cam2image,color2;
	cv::Mat cam1image,color1;
	while (1)
	{

		while(1){    //シャッター方式時間遅れ解消//*/
			cap1 >> color1; // カメラ１(左側のカメラの画像？)
			cap2 >> color2; // カメラ２(右側のカメラの画像？)  //この動作にもっとも時間がかかっている。
			cv::cvtColor(color1,cam1image,CV_RGB2GRAY);
			cv::cvtColor(color2,cam2image,CV_RGB2GRAY);
			resize(cam1image, color1, Size(640, 360));
			resize(cam2image, color2, Size(640, 360));
			cv::imshow("Cam1",color1);
			cv::imshow("Cam2",color2);
	
			key = cv::waitKey(1);
	
			if (key == 's') break;
			if (key == 'q') return 0;
		}
			sprintf(fname1, "./new/I1_%06d.png", num);      //保存ファイル名に気をつける。後々めんどい。
			sprintf(fname2, "./new/I2_%06d.png", num);      //保存ファイル名に気をつける。後々めんどい。
			printf("%s   %s\n", fname1,fname2);
			cv::imwrite(fname1,color1);
			cv::imwrite(fname2,color2);
		//	sleep(1);					//usleep milion// 10Hz強が限界値っぽい
			num++;

		if (key == 'q') break; // ESCで終了
	}

	//time   
	gettimeofday(&t, NULL);
	//printf("%d ms\n", ((t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000));
	cout<< endl ;
	cout<< "num = "<< num << endl;
	cout <<(double)((t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000)/1000<<endl;
	printf("Capture speed  = %f Hz\n",(double)num/(((t.tv_sec - s.tv_sec) * 1000 + (t.tv_usec - s.tv_usec) / 1000)/1000));
	cout<< endl ;

	return 0;
}

