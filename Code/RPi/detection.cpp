#include "detection.h"


Detector::Detector(double dt)
{
  pause_time=dt;
  readCameraParameters();
  dictionary = aruco::getPredefinedDictionary(DICT);
}

int Detector::readCameraParameters()
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

void Detector::start()
{
  cout<<"Starting Detector"<<endl;
  run=1;
  loop_thread=thread(&Detector::loop,this);
}

void Detector::stop()
{
  cout<<"Stoping Detector"<<endl;
  run=0;
  loop_thread.join();
}

void Detector::send_image(Mat &img)
{
  img_orig=img;
}

void Detector::loop()
{
  while(run)
  {
    imshow("debug2",img_orig);
    usleep(pause_time*1e+6);
  }
  return;
}
