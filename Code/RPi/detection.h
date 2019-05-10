#pragma once

#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include <thread>

#include <unistd.h>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

#define DICT aruco::DICT_4X4_50
#define MARKER_SIDE 62.5//in mm to get mm at the output

class Detector
{
  private:
    Mat cameraMatrix;
    Mat distCoeffs;
    int readCameraParameters();

    Ptr<cv::aruco::Dictionary> dictionary;

    thread loop_thread;
    double pause_time;
    int run;

    Mat img_orig;

    void loop();

  public:
    Detector(double dt);
    void start();
    void stop();
    void send_image(Mat &img);
};
