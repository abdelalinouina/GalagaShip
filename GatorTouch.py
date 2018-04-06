# organize imports
import cv2
import imutils
import numpy as np
import os
import time
import serial

backGround_X = None
backGround_Y = None

#**************************************************
#Finding the running average of the backGround
#--------------------------------------------------
def running_average(img, weight):
	global backGround
	if backGround is None:
		backGround= img.copy().astype("float")
		return
	cv2.accumulateWeighted(img, backGround, weight)
	
#**************************************************
# Main Function
#--------------------------------------------------

if __name__ == "__main__":



	ser = serial.Serial(
              
	port='/dev/ttyS0',
        baudrate = 9600,
        parity=serial.PARITY_NONE,
        stopbits=serial.STOPBITS_ONE,
        bytesize=serial.EIGHTBITS
        #timeout=1
        )




	weight_X = 0.5
	weight_Y = 0.5
	threshold_x = 50
	threshold_y = 50
	framesNumber_X = 0
	framesNumber_Y = 0


	
	camera_X = cv2.VideoCapture(0)
	camera_Y = cv2.VideoCapture(1)
	Index = 0 
	while(True) :
		
		(ret_X, frame_X) = camera_X.read()
		(ret_y, frame_Y) = camera_Y.read()

		frame_X = imutils.resize(frame_X, width=320)
		frame_Y = imutils.resize(frame_Y, width=320)

		frame_X = cv2.flip(frame_X, 1)
		frame_Y = cv2.flip(frame_Y, 1)


		clone_X = frame_X.copy()
		clone_Y = frame_Y.copy()

		gray_X = cv2.cvtColor(frame_X , cv2.COLOR_BGR2GRAY)
		gray_Y = cv2.cvtColor(frame_Y , cv2.COLOR_BGR2GRAY)


		gray_X = cv2.GaussianBlur(gray_X, (7, 7), 0)
		gray_Y = cv2.GaussianBlur(gray_Y, (7, 7), 0)

#----------------------------------------------------------------------------------

		if framesNumber_X < 30:
			#running_average(gray_X, weight_X)

			if backGround_X is None:
					backGround_X= gray_X.copy().astype("float")
			else:
					cv2.accumulateWeighted(gray_X, backGround_X, weight_X)


		else:
			diff_X = cv2.absdiff(backGround_X.astype("uint8"), gray_X )
			thresholded_X = cv2.threshold(diff_X,threshold_x,255,cv2.THRESH_BINARY)[1]

          
			cv2.imshow("Thesholded_X", thresholded_X)
		 # increment the number of frames
		framesNumber_X += 1

#----------------------------------------------------------------------------------

		if framesNumber_Y < 30:
			#running_average(gray_Y, weight_Y)

			if backGround_Y is None:
					backGround_Y= gray_Y.copy().astype("float")
			else:
					cv2.accumulateWeighted(gray_Y, backGround_Y, weight_Y)

		else:
			diff_Y = cv2.absdiff(backGround_Y.astype("uint8"), gray_Y )
			thresholded_Y = cv2.threshold(diff_Y,threshold_y,255,cv2.THRESH_BINARY)[1]

          
			cv2.imshow("Thesholded_Y", thresholded_Y)
		 # increment the number of frames
		framesNumber_Y += 1

#----------------------------------------------------------------------------------

        # display the frame with segmented hand
		cv2.imshow("X", clone_X)
		cv2.imshow("Y", clone_Y)

        # observe the keypress by the user
		keypress = cv2.waitKey(1) & 0xFF

        # if the user pressed "q", then stop looping
		if keypress == ord("q"):
			break


		total =0
		#Index = 0                
		#for i in range(0, 239):
		                #for j in range(0, 1):
		                        #if thresh[i][j] == 255:
		                         #       total = total+1  
		                #Index = Index + i
		if total != 0 :
		             Index = Index/total
            
        
		        #print ("The total of white pixels is %d "%total)  
		        #print ("The coordinate is %d "%Index )
      
		        #cv2.rectangle(imgOriginal , (300,int(Index)-4),(320,int(Index)+4),(0,0,255),5)
		#cv2.imshow("imgOriginal", imgOriginal)         # show windows	
		#Index = 8 (Index * 64)/240
		Index = Index+1;
		byte = chr(int(Index))
		ser.flush()
		ser.write(byte.encode('utf-8'))
		os.system('clear')
		print(Index) 
		#time.sleep(0.01)
		#cv2.imshow("cropped", mask )


# free up memory
camera_X.release()
cv2.destroyAllWindows()

		