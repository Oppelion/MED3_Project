from image_Processor import *

IP = imageProcessor()
cap = cv2.VideoCapture(0)


while True:
    ret, frame = cap.read()

    IP.set_frame(frame)
    IP.mask = IP.create_mask(frame)
    IP.frame = IP.reduce_noise(IP.mask)
    IP.frame = IP.detect_blobs(IP.frame)
    IP.locate_hands(IP.frame)
    if len(IP.pts) == 2:
        IP.distance_hands()
        if IP.distance_init == 0.0:
            IP.calibrate()
    IP.detect_movement()
    if IP.movement:
        IP.time = time.time()
        IP.speed(cap)
        IP.movement = False

    IP.frame = cv2.drawKeypoints(IP.mask, IP.frame, np.array([]), (0, 0, 255),
                                 cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

    cv2.imshow('frame', frame)
    cv2.imshow('frame4', IP.frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything done, release the capture
cap.release()
cv2.destroyAllWindows()
