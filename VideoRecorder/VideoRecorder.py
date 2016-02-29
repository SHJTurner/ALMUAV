import numpy as np
import cv2

# Load an color image in grayscale
cam = cv2.VideoCapture(0)
ret_val = cam.set(3,1280)
ret_val = cam.set(4,720)
writer = cv2.VideoWriter('videoOut.mp4',1196444237,30,(1280,720))

while True:
	ret_val, img = cam.read()
	cv2.imshow('image',img)
	writer.write(img);
	if cv2.waitKey(1) == 27:
		break
writer.release()
cv2.destroyAllWindows()

