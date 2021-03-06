import numpy as np
import cv2
import glob

# termination criteria
criteria = (cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER, 30, 0.001)

# prepare object points, like (0,0,0), (1,0,0), (2,0,0) ....,(6,5,0)
objp = np.zeros((6*4,3), np.float32)
objp[:,:2] = np.mgrid[0:6,0:4].T.reshape(-1,2)

# Arrays to store object points and image points from all the images.
objpoints = [] # 3d point in real world space
imgpoints = [] # 2d points in image plane.

images = glob.glob('output/*.jpg')

for fname in images:
    img = cv2.resize(cv2.imread(fname),(640,480))
    gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)

    # Find the chess board corners
    ret, corners = cv2.findChessboardCorners(gray, (6,4),None)

    # If found, add object points, image points (after refining them)
    if ret == True:
        objpoints.append(objp)

        corners2 = cv2.cornerSubPix(gray,corners,(11,11),(-1,-1),criteria)
        imgpoints.append(corners2)

        # Draw and display the corners
        print(fname)
        img = cv2.drawChessboardCorners(img, (6,4), corners2,ret)
        cv2.imshow('img',cv2.resize(img,(640,480)))
        cv2.waitKey(500)

cv2.destroyAllWindows()
ret, mtx, dist, rvecs, tvecs = cv2.calibrateCamera(objpoints, imgpoints, gray.shape[::-1],None,None)
f=open("output/calibration.txt","w")
f.write("Camera_matrix\n")
mtx=mtx.flatten()
for c in mtx:
    f.write(str(c))
    f.write("\n")
f.write("distortions\n")
dist=dist.flatten()
for c in dist:
    f.write(str(c))
    f.write("\n")
f.close()
