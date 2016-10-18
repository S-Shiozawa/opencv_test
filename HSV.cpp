//cameracalibration.cpp	から出てくるxmlファイルを使って歪み補正した画像を保存
//歪み除去したいフォルダ名を引数にとる
//

#include <cv.h>
#include <highgui.h>
#include <string.h>
int
main (int argc, char *argv[])
{ int num=0;
  IplImage *src_img, *dst_img;
  CvMat *intrinsic, *distortion; 
  CvFileStorage *fs;
  CvFileNode *param;
  

char imstr[100];
char imfol[100];

if(argv[1]==NULL){printf("変換したいフォルダを指定してください\n");return -1;}

  // (1)補正対象となる画像の読み込み
while(1){
strcpy(imfol,argv[1]);
sprintf(imstr,"/image2_%d.jpg",num);     //読み込み画像ファイル名注意！
strcat(imfol,imstr);


  if (argc < 2 || (src_img = cvLoadImage (imfol, CV_LOAD_IMAGE_ANYCOLOR)) == 0)//白黒化して取り込み（LIBVISO用に）
	{printf("終了\n");   
	return -1;}
//初期化
 dst_img = cvCloneImage (src_img);
cvCvtColor(src_img,dst_img,CV_BGR2HSV);



	char fname[1024];
sprintf(fname, "./hsv%s",imstr); 	//dst_imgフォルダに新しい保存用フォルダを作る必要がある。     
//sprintf(fname, "I1_HSV.png");
	printf("%s\n", fname);
	cvSaveImage(fname,dst_img,NULL);   

  cvReleaseImage (&src_img);
  cvReleaseImage (&dst_img);

num++;

}

  return 0;
}

