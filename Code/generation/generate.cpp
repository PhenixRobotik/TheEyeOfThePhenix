#include <stdio.h>
#include <sstream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

//less symbols, less confusion, smaller faster to recognize, DICT_6X6_250
#define DICT aruco::DICT_4X4_50//please refer to documentation
#define N_MARKERS 50 //number of markers
#define OUT_SIZE 200 //output size squarre in pixels

int main(int argc, char** argv )
{
  stringstream file_name;
  Mat markerImage;
  Ptr<aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(DICT);

  cout<<"Please make sure the output directory exists"<<endl;
  for(int i=0;i<N_MARKERS;i++)
  {
    aruco::drawMarker(dictionary, i, OUT_SIZE, markerImage, 1);
    file_name.str("");
    file_name << "../output/marker_" << i << ".png";
    imwrite(file_name.str(),markerImage);
  }
  cout<<"Wrote the markers"<<endl;

  return 0;
}
