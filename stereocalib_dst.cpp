//2:L:I2    1:R:I1
/*コメント

（matlabとopencvのパラメータが異なる）
	objとimgpoinを代入し直したうえで
		1.FIXでR、T代入
		2.r,tt代入

→matlabと比較
*/
#include "opencv2/core/core.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/contrib/contrib.hpp"
#include <cv.h>
#include <stdio.h>

#define CHESS_SIZE (68.0)       /* パターン1マスの1辺サイズ[mm] */

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    int numBoards = 22;
    int board_w = 7;
    int board_h = 10;
    int i;
     Size board_sz = Size(board_w, board_h);
    int board_n = board_w*board_h;
    CvFileStorage *fsL, *fsR;
    CvFileNode *param;
    vector<vector<Point3f> > object_points;
    vector<vector<Point2f> > imagePoints1, imagePoints2;
    vector<Point2f> corners1, corners2;

    Mat img1[numBoards], img2[numBoards], gray1[numBoards], gray2[numBoards],cap1,cap2;

    vector<Point3f> obj;
    for (int j=0; j<board_n; j++)
    {
        obj.push_back(Point3f(j/board_w*0.068, j%board_w*0.068, 0.0f));
    }


for (i = 0; i < numBoards; i++) {
    char buf1[32],buf2[32];
    sprintf (buf1, "steca11/I1_%06d.png", i);     //////////画像フォルダ指定。
    sprintf (buf2, "steca11/I2_%06d.png", i);     //////////画像フォルダ指定。
    img1[i] = cvLoadImage (buf1, CV_LOAD_IMAGE_GRAYSCALE);
    img2[i] = cvLoadImage (buf2, CV_LOAD_IMAGE_GRAYSCALE);
  }

    int success = 0, k = 0;
    bool found1 = false, found2 = false;
i=0;
    while (i < numBoards)
    {

gray1[i]=img1[i];
gray2[i]=img2[i];


       found1 = findChessboardCorners(img1[i], board_sz, corners1, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);
        found2 = findChessboardCorners(img2[i], board_sz, corners2, CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FILTER_QUADS);

        if (found1)
        {
            cornerSubPix(gray1[i], corners1, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(gray1[i], board_sz, corners1, found1);
        }
printf("%d\n",i);

        if (found2)
        {
            cornerSubPix(gray2[i], corners2, Size(11, 11), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 30, 0.1));
            drawChessboardCorners(gray2[i], board_sz, corners2, found2);
        }
        
        imshow("image1", gray1[i]);
        imshow("image2", gray2[i]);

       k = waitKey(10);
        if (found1 && found2)
        {
            k = waitKey(0);
        }
        if (k == 27)   //Esc
        {
            break;
        }
        if (k == ' ' && found1 !=0 && found2 != 0)
        {
            imagePoints1.push_back(corners1);
            imagePoints2.push_back(corners2);
            object_points.push_back(obj);
            printf ("Corners stored\n");
            success++;
	   
            if (success >= numBoards)
            {
                break;
            }
        }
i++;
    }

    destroyAllWindows();
  //// (2)パラメータファイルの読み込み
    printf("Starting Calibration\n");
    Mat CM1 ;//= Mat(3, 3, CV_64FC1);
    Mat CM2 ;//= Mat(3, 3, CV_64FC1);
    Mat D1, D2;
    Mat R, T, E, F; 
    Mat objectpo,imgpo1,imgpo2,point_counts;
    Mat rotion,torsan,rotion2;
//R
  fsR = cvOpenFileStorage ("cameraA.xml", 0, CV_STORAGE_READ);
  param = cvGetFileNodeByName (fsR, NULL, "intrinsic");
  CM1 = (CvMat *) cvRead (fsR, param);
  param = cvGetFileNodeByName (fsR, NULL, "distortion");
  D1 = (CvMat *) cvRead (fsR, param);
/*  param = cvGetFileNodeByName (fsR, NULL, "rotation");
  rotion = (CvMat *) cvRead (fsR, param);
  param = cvGetFileNodeByName (fsR, NULL, "translation");
  torsan = (CvMat *) cvRead (fsR, param);
  param = cvGetFileNodeByName (fsR, NULL, "image_points");
  imgpo1=(CvMat *) cvRead (fsR, param);
*/
//both
  param = cvGetFileNodeByName (fsR, NULL, "object_points");
  objectpo=(CvMat *) cvRead (fsR, param);
  param = cvGetFileNodeByName (fsR, NULL, "point_counts"); 
  point_counts=(CvMat *) cvRead (fsR, param);
  cvReleaseFileStorage (&fsR);
 
//L
  fsL = cvOpenFileStorage ("cameraB.xml", 0, CV_STORAGE_READ);
  param = cvGetFileNodeByName (fsL, NULL, "intrinsic");
  CM2 = (CvMat *) cvRead (fsL, param);
  param = cvGetFileNodeByName (fsL, NULL, "distortion");
  D2 = (CvMat *) cvRead (fsL, param);
  param = cvGetFileNodeByName (fsL, NULL, "image_points");
  imgpo2=(CvMat *) cvRead (fsL, param);
  cvReleaseFileStorage (&fsL);

cv::Mat r,tt;
/*rotion.convertTo(r, CV_64F);
torsan.convertTo(tt, CV_64F);
imgpo1.convertTo(imgpo1, CV_64F);
imgpo2.convertTo(imgpo2, CV_64F);
point_counts.convertTo(point_counts, CV_64F);
*/



cout<<"\n\naa\n\n\n"<<endl;

//キャリブレーション  
  stereoCalibrate(object_points ,imagePoints1,imagePoints2,//imgpo1, imgpo2,object_points 
                    CM1, D1, CM2, D2, img1[0].size(), R, T, E, F,
                    cvTermCriteria(CV_TERMCRIT_ITER+CV_TERMCRIT_EPS, 100, 1e-5), 
                   /* CV_CALIB_SAME_FOCAL_LENGTH | */CV_CALIB_ZERO_TANGENT_DIST);//  CV_CALIB_FIX_INTRINSIC);//    


    FileStorage fs1("mystereocalib.yml", FileStorage::WRITE);
    fs1 << "CM1" << CM1; 
    fs1 << "CM2" << CM2;          
    fs1 << "D1" << D1;
    fs1 << "D2" << D2;
    fs1<< "object_points" <<object_points ;
    fs1<< "imagePoints1" << imagePoints1;
 //   fs1 << "R" << rotion; 
    fs1 << "T" << T;
    fs1 << "E" << E;
    fs1 << "F" << F;

/*
    cout<<rotion.at<float>(2,2)<<endl; 
    cout<<rotion.at<float>(1,3)<<endl;   
    cout<<rotion<<endl;
*/
    printf("Done Calibration\n");
    printf("Starting Rectification\n");
    Mat R1, R2, P1, P2, Q;
    stereoRectify(CM1, D1, CM2, D2, img1[0].size(), R, T, R1, R2, P1, P2, Q,CV_CALIB_ZERO_DISPARITY,0);             //有効ピクセル調節。１全体、0有効ピクセル、-1はデフォルト設定


    fs1 << "R1" << R1;
    fs1 << "R2" << R2;
    fs1 << "P1" << P1;
    fs1 << "P2" << P2;
    fs1 << "Q" << Q;

    printf("Done Rectification\n");
    printf("Applying Undistort\n");

    Mat map1x, map1y, map2x, map2y;
    Mat imgU1, imgU2;

    initUndistortRectifyMap(CM1, D1, R1, P1, img1[0].size(), CV_32FC1, map1x, map1y);
    initUndistortRectifyMap(CM2, D2, R2, P2, img2[0].size(), CV_32FC1, map2x, map2y);

    printf("Undistort complete\n");
	i=0;

int num =0;
char I1[100],I2[100];
Mat im1,im2;
char name1[100],name2[100];

    Mat image1, image2;

    while(1)
    {    

///*
sprintf(name1,"./30/I1_%06d.png",num);				//フォルダ名
sprintf(name2,"./30/I2_%06d.png",num);

    im1 = cvLoadImage (name1, CV_LOAD_IMAGE_GRAYSCALE);
    im2 = cvLoadImage (name2, CV_LOAD_IMAGE_GRAYSCALE);
    remap(im1, imgU1, map1x, map1y, INTER_LINEAR, BORDER_CONSTANT, Scalar());
    remap(im2, imgU2, map2x, map2y, INTER_LINEAR, BORDER_CONSTANT, Scalar());


sprintf(I1,"./dst_img/30/I1_%06d.png",num);
sprintf(I2,"./dst_img/30/I2_%06d.png",num);
        imwrite(I1, imgU1);
        imwrite(I2, imgU2);
num++;

if(num==2141){cout << "正常終了"<<endl;break;}				//総数注意
}

    return(0);
}
