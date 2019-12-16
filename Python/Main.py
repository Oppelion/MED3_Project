from Client import*
from image_Processor import*
from data_Collection import*

dividend = 4                                                                       # Makes data smaller before sending through network
counter = 0                                                                        # Data counter
IP = imageProcessor()                                                              # Instantiate imageProcessor object.
IP.create_blob_detector()                                                          # Instantiate BLOB detector object
DC = data_Collection()                                                             # Instantiate data collection object
Client = client()                                                                  # Instantiate client object.
cap = cv2.VideoCapture(0)                                                          # Begin video capture.
outMain = cv2.VideoWriter('outPutMain.avi', 0, 24.0, (640,480))                    # Creates a video file called outPutMain.avi with the dimensions of 640 x 480 pixels
outBlob = cv2.VideoWriter('outPutBlob.avi', 0, 24.0, (640,480))                    # Creates a video file called outPutBlob.avi with the dimensions of 640 x 480 pixels
Record = False

while True:                                                                        # Infinite loop to run the program.
    ret, frame = cap.read()                                                        # Read from the camera capture.

    IP.set_frame(frame)                                                            # Set the frame and apply blur.
    IP.mask = IP.create_mask(IP.frame)                                             # Create binary mask with blobs.
    IP.frame = IP.reduce_noise(IP.mask)                                            # Reduce noise in the mask.
    IP.frame = IP.detect_blobs(IP.frame)                                           # Detect blobs in the mask.
    IP.locate_hands(IP.frame)                                                      # Locate which blobs are hands.
    if len(IP.pts) == 2:                                                           # Checks if there are exactly two blobs.
        IP.distance = IP.distance_hands()                                          # Finds distance between hands.
        if IP.distance_init == 0.0:                                                # Checks if initial distance has been found
            if cv2.waitKey(1) & 0xFF == ord('l'):                                  # Checks if L is pressed.
                IP.distance_init = IP.calibrate() / dividend                       # Calibrate and adjust value of distance.
                Client.SendInfo(int(IP.distance_init), 0, 0)                       # Send distance_init to the server.
                data_init_distance = IP.distance_init * dividend                   # Reverts distance_init for printing in dataCollection
                DC.data_distance_init.append(data_init_distance)                   # Adds the distance_init to the array in dataCollection
                DC.data_converted_distance_init.append(IP.distance_init)           # Adds the converted distance_init to the array in dataCollection
                DC.data_counter.append(counter)                                    # Adds the counter_init to the array in dataCollection

    IP.speed_right_hand = IP.speed()                                               # Calculate speed of right hand.

    IP.frame = cv2.drawKeypoints(IP.mask, IP.frame, np.array([]), (0, 0, 255),
                                 cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)       # Draw key points on the blobs.

    stringPos = int(IP.guitar_string_pos)                                          # Sets position of Guitar String
    cv2.rectangle(frame, (0, stringPos - 10), (640, stringPos + 10), (150, 150, 150), 5)
    if IP.distance < ((IP.distance_init * 4) * 1.2):                               # If the distance is within the maximum, make the line black
        frame = cv2.line(frame, (IP.pos_left_hand[0], IP.pos_left_hand[1]), (IP.pos_right_hand[0], IP.pos_right_hand[1]), 0, thickness=5)
    else:                                                                          # Otherwise, make the line Red.
        frame = cv2.line(frame, (IP.pos_left_hand[0], IP.pos_left_hand[1]), (IP.pos_right_hand[0], IP.pos_right_hand[1]), (0, 0, 255), thickness=5)

    frame = cv2.flip(frame, 1)                                                     # Mirror Image
    IP.frame = cv2.flip(IP.frame, 1)                                               # Mirror Image
    cv2.imshow('frame', frame)                                                     # Shows the Camera Capture
    cv2.imshow('frame4', IP.frame)                                                 # Shows Image Processed image
    if (cv2.waitKey(1) & 0xFF == ord('r')):
        print("Recording")                                                         # If r is pressed, print "Recording" and switch Record to true
        Record = True
    if Record:
        outMain.write(frame)                                                       # If Record has been set to true, write out what the camera sees in both normal view and IP view
        outBlob.write(IP.frame)
    if (cv2.waitKey(1) & 0xFF == ord('w')) and (Client.clientConnected == False):  # If w key is pressed, connect to server
        Client.SockConnect()                                                       # Connects to the local host
        Client.clientConnected = True

                                                                                   # If hands are within range
    if (IP.pos_right_hand[1] <= stringPos):
        Client.spamFilter = True                                                   # Set spamFilter to True.

                                                                                   # If client is connected, initial distance has been registered, and hands are within range:
    if Client.clientConnected and (IP.distance_init != 0.0) and (IP.pos_right_hand[1] >= stringPos) and Client.spamFilter and IP.speed_right_hand != 0:
        DC.data_hand_distance.append(IP.distance)                                  # Data save the right hand pos
        IP.distance = IP.distance / dividend                                       # Divides the Distance by 3
        counter += 1                                                               # Data counter
        DC.data_counter.append(counter)                                            # Adds the counter to the array in data collection
        DC.data_converted_Hand_distance.append(IP.distance)                        # Adds the hand distance to the array in data collection
        DC.data_Converted_speed.append(IP.speed_right_hand)                        # Adds the hand speed to the array in data collection
        Client.SendInfo(0, int(IP.distance), int(IP.speed_right_hand))             # Sends Distance and Speed
        Client.spamFilter = False                                                  # Set spamFilter to False
    if cv2.waitKey(1) & 0xFF == ord("q"):                                          # If q is pressed, break.
        DC.write_to_sheet()                                                        # Calls the function in data_Collection line 23
        break

outMain.release()                                                                  #Stops the recording to the outPutMain.avi file
outBlob.release()                                                                  #Stops the recording to the outPutBlob.avi file
cap.release()                                                                      # Closes video file or capturing device
cv2.destroyAllWindows()                                                            # Destroys all windows.

