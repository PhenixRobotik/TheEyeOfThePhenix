#include <stdio.h>
#include <sstream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

//less symbols, less confusion, smaller faster to recognize, DICT_6X6_250 for test.png, DICT_4X4_50
#define DICT aruco::DICT_4X4_50//must be the same as in generation

int main(int argc, char** argv )
{
  Mat image, imageCopy;
  Ptr<cv::aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(DICT);

  image=imread("../input/test.png");
  image.copyTo(imageCopy);
  vector<int> ids;
  vector<std::vector<cv::Point2f> > corners;
  aruco::detectMarkers(image, dictionary, corners, ids);
  // if at least one marker detected
  if (ids.size() > 0)
    aruco::drawDetectedMarkers(imageCopy, corners, ids);

  imshow("out", imageCopy);
  waitKey(0);

  return 0;
}
