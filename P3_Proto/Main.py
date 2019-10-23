from image_Processor import *
import Client

IP = imageProcessor()
cap = cv2.VideoCapture(0)

distance = 0.0
distance_init = 0.0
speed = 0.0
clientConnected = False
nonCalibration = True
dividend = 4

lower_limit = (100, 150, 150)
upper_limit = (140, 255, 255)

while nonCalibration == False:
    ret, frame2 = cap.read()
    cv2.rectangle(frame2, (328, 238), (332, 242), (150, 150, 150))

    hsv = cv2.cvtColor(frame2, cv2.COLOR_BGR2HSV)
    cv2.imshow('frame2', hsv)
    if cv2.waitKey(1) & 0xFF == ord('e'):
        pixel = frame2[240][330]
        lower_limit = np.array((pixel[0] - 15, pixel[1] - 15, pixel[2] - 15), dtype=np.uint8, ndmin=1)
        upper_limit = np.array((pixel[0] + 15, pixel[1] + 15, pixel[2] + 15), dtype=np.uint8, ndmin=1)
        nonCalibration = False

while True:
    ret, frame = cap.read()

    IP.set_frame(frame)
    IP.mask = IP.create_mask(IP.frame, lower_limit, upper_limit)
    IP.frame = IP.reduce_noise(IP.mask)
    IP.frame = IP.detect_blobs(IP.frame)
    IP.locate_hands(IP.frame)
    if len(IP.pts) == 2:
        distance = IP.distance_hands()
        if IP.distance_init == 0.0:
            distance_init = IP.calibrate()
    IP.detect_movement()
    if IP.movement:
        speed = IP.speed(cap)
        IP.movement = False

    IP.frame = cv2.drawKeypoints(IP.mask, IP.frame, np.array([]), (0, 0, 255),
                                 cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

    cv2.imshow('frame', frame)
    cv2.imshow('frame4', IP.frame)
    lastDist = int(distance)
    lastSpeed = int(speed)
    if cv2.waitKey(1) & 0xFF == ord('w'):
        Client.SockConnect()
        clientConnected = True
    if clientConnected == True and distance_init != 0.0 and distance != lastDist and speed != lastSpeed and IP.pos_right_hand[1] >= (IP.guitar_string_pos - 10) and IP.pos_right_hand[1] <= (IP.guitar_string_pos + 10):
        distance_init = distance_init / dividend
        distance = distance / dividend
        speed = speed / dividend
        Client.SendInfo(int(distance_init), int(distance), int(speed))
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
