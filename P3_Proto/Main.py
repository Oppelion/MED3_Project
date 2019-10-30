from P3_Proto import Client
from P3_Proto.image_Processor import*

IP = imageProcessor()
cap = cv2.VideoCapture(0)

distance = 0.0
distance_init = 0.0
speed = 0.0
dividend = 3

while True:
    ret, frame = cap.read()

    IP.set_frame(frame)
    IP.mask = IP.create_mask(IP.frame)
    IP.frame = IP.reduce_noise(IP.mask)
    IP.frame = IP.detect_blobs(IP.frame)
    IP.locate_hands(IP.frame)
    if len(IP.pts) == 2:
        distance = IP.distance_hands()
        if IP.distance_init == 0.0:
            if cv2.waitKey(1) & 0xFF == ord('l'):
                distance_init = IP.calibrate() / dividend
                Client.SendInfo(int(distance_init), 0, 0)
        speed = IP.speed()
        speed = IP.speed_control()

    IP.frame = cv2.drawKeypoints(IP.mask, IP.frame, np.array([]), (0, 0, 255),
                                 cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

    stringPos = int(IP.guitar_string_pos)
    cv2.rectangle(frame, (0, stringPos - 10), (640, stringPos + 10), (150, 150, 150))

    cv2.imshow('frame', frame)
    cv2.imshow('frame4', IP.frame)
    lastDist = int(distance)
    lastSpeed = int(speed)
    if cv2.waitKey(1) & 0xFF == ord('w'):
        Client.SockConnect()
        clientConnected = True
    print(IP.guitar_string_pos)
    print(IP.pos_right_hand[1])
    if IP.pos_right_hand[1] == IP.guitar_string_pos:
        print('Hello strikes back')

    if (Client.clientConnected is True) and (distance_init != 0.0) and (IP.pos_right_hand[1] >= IP.guitar_string_pos - 10) and \
            (IP.pos_right_hand[1] <= IP.guitar_string_pos + 10):
        # distance_init = distance_init / dividend
        distance = distance / dividend
        print(distance_init, " + ", distance, " + ", speed)
        Client.SendInfo(0, int(distance), int(speed))
    if cv2.waitKey(1) & 0xFF == ord("q"):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
