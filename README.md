# TheEyeOfThePhenix
Prototype de balise à base de caméra sur RaspberriPi destiné à être fixé sur le mat central de la table de jeu  

Utilise opencv (version 4.1.0, prendre la plus récente: https://opencv.org/releases/)  
pensez à activez ccache avant la compilation  
```
$ git clone https://github.com/opencv/opencv.git && cd opencv && git checkout 4.1.0 && cd .. && git clone https://github.com/opencv/opencv_contrib.git && cd opencv_contrib && git checkout 4.1.0 && cd .. && mkdir build_opencv && cd build_opencv
$ cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D OPENCV_EXTRA_MODULES_PATH=../opencv_contrib/modules -D ENABLE_NEON=ON -D ENABLE_VFPV3=ON -D BUILD_TESTS=OFF -D OPENCV_ENABLE_NONFREE=ON -D INSTALL_PYTHON_EXAMPLES=OFF -D BUILD_EXAMPLES=OFF ../opencv
$ nano /etc/dphys-swapfile #penser à remettre à 100 après la compilation
$ CONF_SWAPSIZE=2048
$ /etc/init.d/dphys-swapfile stop
$ /etc/init.d/dphys-swapfile start
$ make -j5 #à aujuster, peut prendre jusqu'à 6h00
$ sudo make install
#uniquement en cas de problème, à ajuster la version de python3
$ sudo ln -s /usr/local/lib/python3.7/site-packages/cv2/python-3.7/cv2.cpython-37m-x86_64-linux-gnu.so /lib/python3.7/site-packages/cv2.so
```
puis tester:
```
python3
import cv2
```
ou compiler un code de test  
pour tester la caméra:
```
raspistill -vf -hf -o cam.jpg
```
Pour ouvrir la caméra du raspberry normalement:
```
modprobe bcm2835-v4l2
```
La détection des robots est inspirée de cette page:  
https://docs.opencv.org/4.1.0/d5/dae/tutorial_aruco_detection.html  

Pour démarrer automatiquement au démarrage éditer le /etc/rc.local:  
```
modprobe bcm2835-v4l2
nohup /home/pi/RPi/build/Eye &
```
