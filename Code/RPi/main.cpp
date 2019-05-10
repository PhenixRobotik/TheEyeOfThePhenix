#include "opencv2/opencv.hpp"
#include <iostream>

#include "detection.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
    Mat frame;
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    double fps_cam = cap.get(CAP_PROP_FPS);
    cap >> frame;
    cout<<"image W:";
    cout<<frame.cols;
    cout<<" image H:";
    cout<<frame.rows;
    cout<<" fps:";
    cout<<fps_cam<<endl;
    VideoWriter video("../output/out.avi",VideoWriter::fourcc('M','J','P','G'),fps_cam, Size(frame.cols,frame.rows));

    Detector ddd(1);
    ddd.send_image(frame);
    ddd.start();

    int i=0;
    while(1)//main loop reading camera and feeding the aruco detection
    {
        cap >> frame; // get a new frame from camera
        ddd.send_image(frame);
        video.write(frame);
        imshow("debug",frame);
        if(waitKey(30) >= 0) break;
        //i++;
    }
    ddd.stop();
    cap.release();
    video.release();
    return 0;
}
