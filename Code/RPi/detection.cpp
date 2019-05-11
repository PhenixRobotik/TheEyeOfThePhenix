#include "detection.h"


Detector::Detector()
{
  readCameraParameters();
  dictionary = aruco::getPredefinedDictionary(DICT);
  isnew=0;
  output_frame_id=0;
  loop_time=0;
}

int Detector::readCameraParameters()
{
  cameraMatrix=Mat_<double>(3,3);
  distCoeffs =Mat_<double>(5,1);
  string line;
  ifstream calibfile;

  calibfile.open ("../calibration.txt");//TODO: add error code if wrong file
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

void Detector::send_image(Mat &img,unsigned int frame_id)
{
  write_mutex.lock();
  isnew=1;
  img.copyTo(img_orig);//image stored in img_orig
  input_frame_id=frame_id;
  write_mutex.unlock();
}

void Detector::loop()
{
  Mat img;
  vector<int> ids_int;
  vector<vector<Point2f> > corners_int;
  vector<Vec3d> rvecs_int, tvecs_int;
  unsigned int frame_id;

  while(run)
  {
    if (isnew==1)
    {
      auto start = std::chrono::high_resolution_clock::now();

      write_mutex.lock();
      isnew=0;
      img_orig.copyTo(img);//working on img and not img_orig
      frame_id=input_frame_id;
      write_mutex.unlock();

      aruco::detectMarkers(img, dictionary, corners_int, ids_int);
      aruco::estimatePoseSingleMarkers(corners_int, MARKER_SIDE, cameraMatrix, distCoeffs, rvecs_int, tvecs_int);
      auto stop = std::chrono::high_resolution_clock::now();
      chrono::duration<double> elapsed = stop - start;

      read_mutex.lock();
      ids=ids_int;
      corners=corners_int;
      rvecs=rvecs_int;
      tvecs=tvecs_int;
      loop_time=elapsed.count();
      output_frame_id=frame_id;
      read_mutex.unlock();
    }
    else
    {
      usleep(SLEEP_TIME);//sleep in useconds
    }
  }
  return;
}

void Detector::get_pose(vector<int> &ids_markers,vector<vector<Point2f> > &detected_corners,vector<Vec3d> &angles,vector<Vec3d> &positions,
                        double &time,unsigned int &frame_id)
{
  read_mutex.lock();
  ids_markers=ids;
  detected_corners=corners;
  angles=rvecs;
  positions=tvecs;
  time=loop_time;
  frame_id=output_frame_id;
  read_mutex.unlock();
  return;
}
