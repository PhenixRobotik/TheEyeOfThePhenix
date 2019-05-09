#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;

int main(int, char**)
{
    Mat frame;
    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    cap >> frame;

    VideoWriter video("../output/outcpp.avi",VideoWriter::fourcc('M','J','P','G'),20, Size(frame.cols,frame.rows));

    int i=0;
    while(i<20)
    {
        cap >> frame; // get a new frame from camera
        video.write(frame);

        i++;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    cap.release();
    video.release();
    return 0;
}
