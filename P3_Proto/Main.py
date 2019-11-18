from Client import*
from image_Processor import*

dividend = 4
IP = imageProcessor()  # ......................................................Instantiate imageProcessor object.
IP.create_blob_detector()
Client = client()  # ..........................................................Instantiate client object.
cap = cv2.VideoCapture(0)  # ..................................................Begin video capture.

while True:  # ................................................................Infinite loop to run the program.
    ret, frame = cap.read()  # ................................................Read from the camera capture.

    IP.set_frame(frame)  # ....................................................Set the frame and apply blur.
    IP.mask = IP.create_mask(IP.frame)  # .....................................Create binary mask with blobs.
    IP.frame = IP.reduce_noise(IP.mask)  # ....................................Reduce noise in the mask.
    IP.frame = IP.detect_blobs(IP.frame)  # ...................................Detect blobs in the mask.
    IP.locate_hands(IP.frame)  # ..............................................Locate which blobs are hands.
    if len(IP.pts) == 2:  # ...................................................Checks if there are exactly two blobs.
        IP.distance = IP.distance_hands()  # ..................................Finds distance between hands.
        if IP.distance_init == 0.0:  # ........................................Checks if initial distance has been found
            if cv2.waitKey(1) & 0xFF == ord('l'):  # ..........................Checks if L is pressed.
                IP.distance_init = IP.calibrate() / dividend  # ...............Calibrate and adjust value of distance.
                Client.SendInfo(int(IP.distance_init), 0, 0)  # ...............Send distance_init to the server.
        IP.speed_right_hand = IP.speed()  # ...................................Calculate speed of right hand.

    IP.frame = cv2.drawKeypoints(IP.mask, IP.frame, np.array([]), (0, 0, 255),
                                 cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)  # Draw key points on the blobs.

    stringPos = int(IP.guitar_string_pos)  # ..................................Sets position of Guitar String
    cv2.rectangle(frame, (0, stringPos - 10), (640, stringPos + 10), (150, 150, 150))
    if IP.distance < ((IP.distance_init * 4) * 1.2):  # ........................If the distance is within the maximum
        # ......................................................................Make the line black
        frame = cv2.line(frame, (IP.pos_left_hand[0], IP.pos_left_hand[1]), (IP.pos_right_hand[0], IP.pos_right_hand[1]), 0, thickness=5)
    else:  # ...................................................................Otherwise make the line Red.
        frame = cv2.line(frame, (IP.pos_left_hand[0], IP.pos_left_hand[1]), (IP.pos_right_hand[0], IP.pos_right_hand[1]), (0, 0, 255), thickness=5)

    cv2.imshow('frame', frame)  # ..............................................Shows the Camera Capture
    cv2.imshow('frame4', IP.frame)  # ..........................................Shows Image Processed image
    if cv2.waitKey(1) & 0xFF == ord('w'):  # ...................................If w key is pressed, connect to server
        Client.SockConnect()  # ................................................Connects to the local host
        Client.clientConnected = True

    # ..........................................................................If hands are within range
    if (IP.pos_right_hand[1] <= stringPos - 10) or (IP.pos_right_hand[1] >= stringPos + 10):
        Client.spamFilter = True  # ............................................Set spamFilter to True.

    # ..........................................................................If client is connected and
    # ..........................................................................Initial distance has been registered
    # ..........................................................................And hands are within range
    if Client.clientConnected and (IP.distance_init != 0.0) and (IP.pos_right_hand[1] >= stringPos - 10) and (IP.pos_right_hand[1] <= stringPos + 10) and Client.spamFilter:
        IP.distance = IP.distance / dividend  # ................................Divides the Distance by 3
        Client.SendInfo(0, int(IP.distance), int(IP.speed_right_hand))  #.......Sends Distance and Speed
        Client.spamFilter = False  # ...........................................Set spamFilter to False
    if cv2.waitKey(1) & 0xFF == ord("q"):  # ...................................If q is pressed, break. 
        break

cap.release()  # ...............................................................Closes video file or capturing device
cv2.destroyAllWindows()  # .....................................................Destroys all windows. 
