# TheEyeOfThePhenix
Prototype de balise à base de caméra sur RaspberriPi destiné à être fixé sur le mat central de la table de jeu  

Utilise opencv (version 4.1.0, prendre la plus récente: https://opencv.org/releases/)  
pensez à activez ccache avant la compilation  
```
$ git clone https://github.com/opencv/opencv.git
$ cd opencv && git checkout 4.1.0 && cd ..
$ git clone https://github.com/opencv/opencv_contrib.git #optionnel
$ cd opencv_contrib && git checkout 4.1.0 && cd ..
$ mkdir build_opencv && cd build_opencv
$ cmake -DOPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules ../opencv
$ make -j5 #a aujuster
$ sudo make install
#ajuster la version de python3
$ sudo ln -s /usr/local/lib/python3.7/site-packages/cv2/python-3.7/cv2.cpython-37m-x86_64-linux-gnu.so /lib/python3.7/site-packages/cv2.so
```
puis tester:
```
python3
import cv2
```
