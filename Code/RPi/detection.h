#pragma once

#include <stdio.h>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

#include <thread>
#include <mutex>

#include <chrono>
#include <unistd.h>

#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

using namespace std;
using namespace cv;

#define DICT aruco::DICT_4X4_50
#define MARKER_SIDE 62.5//in mm to get mm at the output
#define SLEEP_TIME 10000//in useconds, time slept if no new image before checking again

class Detector
{
  private:
    Mat cameraMatrix;
    Mat distCoeffs;
    int readCameraParameters();

    Ptr<cv::aruco::Dictionary> dictionary;

    thread loop_thread;
    mutex write_mutex;
    mutex read_mutex;
    int run;
    int isnew;

    Mat img_orig;
    unsigned int input_frame_id;
    unsigned int output_frame_id;

    vector<int> ids;
    vector<vector<Point2f> > corners;
    vector<Vec3d> rvecs, tvecs;
    void loop();
    double loop_time;

  public:
    Detector();
    void start();
    void stop();
    void send_image(Mat &img,unsigned int frame_id);
    void get_pose(vector<int> &ids_markers,vector<vector<Point2f> > &detected_corners,vector<Vec3d> &angles,vector<Vec3d> &positions,
       double &time,unsigned int &frame_id);
};
