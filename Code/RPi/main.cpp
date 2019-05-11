#include "opencv2/opencv.hpp"
#include <iostream>
#include <fstream>
#include <string>

#include "detection.h"
#include "transmission.h"

using namespace cv;
using namespace std;

int main(int, char**)
{
    Mat frame;
    vector<int> ids_markers;
    vector<vector<Point2f> > detected_corners;
    vector<Vec3d> angles;
    vector<Vec3d> positions;
    double time;

    VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    double fps_cam = cap.get(CAP_PROP_FPS);
    cap >> frame;
    cout<<"image W:"<<frame.cols<<" image H:"<<frame.rows<<" fps:"<<fps_cam<<endl;

    int file_number=0;//find a free file name
    string file_name_base="../output/out";
    stringstream file_name;
    file_name.str("");
    file_name<<"../output/out"<<file_number<<".avi";
    ifstream f(file_name.str());
    while(f.good())
    {
      f.close();
      file_number++;
      file_name.str("");
      file_name<<"../output/out"<<file_number<<".avi";
      f.open(file_name.str());
    }
    cout<<"File number "<<file_number<<endl;

    VideoWriter video(file_name.str(),VideoWriter::fourcc('M','J','P','G'),fps_cam, Size(frame.cols,frame.rows));

    file_name.str("");
    file_name<<"../output/out"<<file_number<<".csv";
    ofstream outputFile(file_name.str());
    outputFile<<"image W,"<<frame.cols<<" image H,"<<frame.rows<<" fps,"<<fps_cam<<endl;

    int run=1;
    transmitter t;
    char ret;
    stringstream to_transmit;

    Detector ddd;
    ddd.start();

    unsigned int i=0,output_id=0;
    auto start_time = chrono::high_resolution_clock::now();

    while(run)//main loop reading camera and feeding the aruco detection
    {

        cap >> frame; // get a new frame from camera
        ddd.send_image(frame,i);
        video.write(frame);
        ddd.get_pose(ids_markers, detected_corners, angles, positions,time,output_id);

        auto stop_time = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = stop_time - start_time;//get time from start

        to_transmit.str("");

        to_transmit<<elapsed.count()<<","<<i<<","<<output_id<<","<<time<<","<<ids_markers.size()<<endl;//log to file
        if (ids_markers.size()>0)
        {
          for(int j=0;j<ids_markers.size();j++)
          {
            to_transmit<<ids_markers[j]<<","<<angles[j][0]<<","<<angles[j][1]<<","<<angles[j][2]
            <<","<<positions[j][0]<<","<<positions[j][1]<<","<<positions[j][2]
            <<","<<detected_corners[j][0].x<<","<<detected_corners[j][0].y
            <<","<<detected_corners[j][1].y<<","<<detected_corners[j][1].y
            <<","<<detected_corners[j][2].x<<","<<detected_corners[j][2].y
            <<","<<detected_corners[j][3].x<<","<<detected_corners[j][3].y<<endl;
          }
        }
        to_transmit<<endl;
        outputFile<<to_transmit.str();

        ret=t.transmit_position(to_transmit.str().c_str());
        if(ret=='q')
        {
          run=0;
        }

        //imshow("debug",frame);
        //if(waitKey(30) >= 0) break;
        i++;
    }

    t.end();
    ddd.stop();
    cap.release();
    video.release();
    outputFile.close();

    return 0;
}
