from P3_Proto import Client
from P3_Proto.image_Processor import*

distance = 0.0
distance_init = 0.0
speed = 0.0
dividend = 3
img_counter = 0
img_counter2 = 0

IP = imageProcessor()  # ......................................................Instantiate imageProcessor object.
cap = cv2.VideoCapture(0)  # ..................................................Begin video capture.

while True:  # ................................................................Infinite loop to run the program.
    ret, frame = cap.read()  # ................................................Read from the camera capture.

    IP.set_frame(frame)  # ....................................................Set the frame and apply blur.
    IP.mask = IP.create_mask(IP.frame)  # .....................................Create binary mask with blobs.
    IP.frame = IP.reduce_noise(IP.mask)  # ....................................Reduce noise in the mask.
    IP.frame = IP.detect_blobs(IP.frame)  # ...................................Detect blobs in the mask.
    IP.locate_hands(IP.frame)  # ..............................................Locate which blobs are hands.
    if len(IP.pts) == 2:  # ...................................................Checks if there are exactly two blobs.
        distance = IP.distance_hands()  # .....................................Finds distance between hands.
        if IP.distance_init == 0.0:  # ........................................Checks if initial distance has been found
            if cv2.waitKey(1) & 0xFF == ord('l'):  # ..........................Checks if L is pressed.
                distance_init = IP.calibrate() / dividend  # ..................Calibrate and adjust value of distance.
                Client.SendInfo(int(distance_init), 0, 0)  # ..................Send distance_init to the server.
        speed = IP.speed()  # .................................................Calculate speed of right hand.
        speed = IP.speed_control()  # .........................................Adjust value of speed to be 0 - 100.

    IP.frame = cv2.drawKeypoints(IP.mask, IP.frame, np.array([]), (0, 0, 255),
                                 cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)  # Draw key points on the blobs.

    stringPos = int(IP.guitar_string_pos)
    cv2.rectangle(frame, (0, stringPos - 10), (640, stringPos + 10), (150, 150, 150))

    cv2.imshow('frame', frame)
    cv2.imshow('frame4', IP.frame)
    lastDist = int(distance)
    lastSpeed = int(speed)
    if cv2.waitKey(1) & 0xFF == ord('w'):
        Client.SockConnect()
        Client.clientConnected = True

    if (Client.clientConnected is True) and (distance_init != 0.0) and (IP.pos_right_hand[1] >= IP.guitar_string_pos - 10) and \
            (IP.pos_right_hand[1] <= IP.guitar_string_pos + 10):
        distance = distance / dividend
        print(distance_init, " + ", distance, " + ", speed)
        Client.SendInfo(0, int(distance), int(speed))
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
