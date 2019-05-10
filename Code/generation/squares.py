import cv2
import numpy as np

space=0.1#between 0 and 1

#name="output/01234.png"
#markers=["output/marker_0.png","output/marker_1.png","output/marker_2.png","output/marker_3.png","output/marker_4.png"]
name="output/56789.png"
markers=["output/marker_5.png","output/marker_6.png","output/marker_7.png","output/marker_8.png","output/marker_9.png"]

av=cv2.imread(markers[0])
d=cv2.imread(markers[1])
ar=cv2.imread(markers[2])
g=cv2.imread(markers[3])
dessus=cv2.imread(markers[4])

rows,cols = av.shape[:2]
pix_space=int(space*rows)


M = cv2.getRotationMatrix2D((cols/2,rows/2),180,1)
av = cv2.warpAffine(av,M,(cols,rows))

M = cv2.getRotationMatrix2D((cols/2,rows/2),90,1)
d = cv2.warpAffine(d,M,(cols,rows))

M = cv2.getRotationMatrix2D((cols/2,rows/2),-90,1)
g = cv2.warpAffine(g,M,(cols,rows))

output=np.ones((3*rows+2*pix_space,3*cols+2*pix_space,3))*255

output[rows+pix_space:2*rows+pix_space, 0:cols]=g
output[rows+pix_space:2*rows+pix_space, cols+pix_space:2*cols+pix_space]=dessus
output[rows+pix_space:2*rows+pix_space, 2*cols+2*pix_space:3*cols+2*pix_space]=d
output[0:rows, cols+pix_space:2*cols+pix_space]=av
output[2*rows+2*pix_space:3*rows+2*pix_space, cols+pix_space:2*cols+pix_space]=ar

cv2.imwrite(name,output)
