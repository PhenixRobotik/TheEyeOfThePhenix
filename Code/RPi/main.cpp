#include "opencv2/opencv.hpp"
#include <iostream>

#include "detection.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
    Mat frame;
    vector<int> ids_markers;
    vector<vector<Point2f> > detected_corners;
    vector<Vec3d> angles;
    vector<Vec3d> positions;

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

    Detector ddd;
    ddd.start();

    int i=0;
    while(1)//main loop reading camera and feeding the aruco detection
    {
        cap >> frame; // get a new frame from camera
        ddd.send_image(frame);
        video.write(frame);
        ddd.get_pose(ids_markers, detected_corners, angles, positions);
        if (ids_markers.size()>0)
        {
          cout<<ids_markers[0]<<endl;
        }
        imshow("debug",frame);
        if(waitKey(30) >= 0) break;
        //i++;
    }
    ddd.stop();
    cap.release();
    video.release();
    return 0;
}
