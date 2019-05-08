#include <stdio.h>
#include <sstream>
#include <string>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

int main()
{
  VideoCapture cap(0);
  if(!cap.isOpened())
    return -1;

  cv::Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_50);
  while (1) {
      cv::Mat image, imageCopy;
      cap>>image;
      image.copyTo(imageCopy);
      std::vector<int> ids;
      std::vector<std::vector<cv::Point2f> > corners;
      cv::aruco::detectMarkers(image, dictionary, corners, ids);
      // if at least one marker detected
      if (ids.size() > 0)
          cv::aruco::drawDetectedMarkers(imageCopy, corners, ids);
      cv::imshow("out", imageCopy);
      if(waitKey(30) >= 0) break;
  }
  return 0;
}
