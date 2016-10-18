#include "opencv2/core/core.hpp"
//#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <iostream>
#include <stdio.h>

using std::string;
using std::cout;
using std::endl;

using namespace cv;

static void help(char** av)
{
  cout << "\nThis creates a yaml or xml list of files from the command line args\n"
      "usage:\n./" << av[0] << " imagelist.xml *.png\n"
      << "Try using different extensions.(e.g. yaml yml xml xml.gz etc...)\n"
      << "This will serialize this list of images or whatever with opencv's FileStorage framework" << endl;
}

int main(int ac, char** av)
{
  int numboards = 26;
  char imfolL[100],imfolR[100];
  char imstrL[100],imstrR[100];
  char folname[100];
FileStorage fs; 
/* if (ac < 3)
  {
    help(av);
    return 1;
  }
*/
  strcpy(folname,av[1]);
  string outputname = folname;

for(int num=0;num<numboards;num++){
  strcpy(imfolL,av[1]);
  sprintf(imstrL,"/I2_%06d.png",num);     //読み込み画像ファイル名注意！
  strcat(imfolL,imstrL);

  Mat m = imread(outputname); //check if the output is an image - prevent overwrites!
  if(!m.empty()){
    std::cerr << "fail! Please specify an output file, don't want to overwrite you images!" << endl;
    help(av);
    return 1;
  }

  FileStorage fs(outputname, FileStorage::WRITE);
  fs << "images" << "[";
    fs << imfolL;
  }
  fs << "]";


  return 0;
}
