#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

#define DICT aruco::DICT_4X4_50
#define MARKER_SIDE 53//in mm to get mm at the output

int readCameraParameters(Mat &cameraMatrix,Mat &distCoeffs )
{
  cameraMatrix=Mat_<double>(3,3);
  distCoeffs =Mat_<double>(5,1);
  string line;
  ifstream calibfile;

  calibfile.open ("../calibration.txt");
  getline(calibfile,line);//text
  for(int i=0;i<3;i++)
  {
    for(int j=0;j<3;j++)
    {
      getline(calibfile,line);//first coeff
      cameraMatrix.at<double>(i,j)=stod(line);
    }
  }
  getline(calibfile,line);//text
  for(int i=0;i<5;i++)
  {
    getline(calibfile,line);//first coeff
    distCoeffs.at<double>(i,0)=stod(line);
  }

  calibfile.close();
  return 1;
}

int main()
{
  Mat cameraMatrix,distCoeffs;

  readCameraParameters(cameraMatrix, distCoeffs);

  VideoCapture cap(0);
  if(!cap.isOpened())
    return -1;

  Ptr<cv::aruco::Dictionary> dictionary = cv::aruco::getPredefinedDictionary(DICT);
  while (1) {
      Mat image, imageCopy;
      cap>>image;
      image.copyTo(imageCopy);
      vector<int> ids;
      vector<vector<Point2f> > corners;
      aruco::detectMarkers(image, dictionary, corners, ids);
      // if at least one marker detected
      if (ids.size() > 0)
      {
          aruco::drawDetectedMarkers(imageCopy, corners, ids);

          vector<cv::Vec3d> rvecs, tvecs;
          aruco::estimatePoseSingleMarkers(corners, MARKER_SIDE, cameraMatrix, distCoeffs, rvecs, tvecs);
          // draw axis for each marker
          for(int i=0; i<ids.size(); i++)
          {
              cout<<ids[i]<<endl;
              cout<<tvecs[i]<<endl;
              cout<<rvecs[i]<<endl;
              cout<<endl;
              aruco::drawAxis(imageCopy, cameraMatrix, distCoeffs, rvecs[i], tvecs[i], 1.5*MARKER_SIDE);
          }
          cout<<endl;
      }
      imshow("out", imageCopy);
      if(waitKey(30) >= 0) break;
  }
  return 0;
}
