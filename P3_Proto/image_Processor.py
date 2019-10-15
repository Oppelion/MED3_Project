import cv2
import numpy as np


class imageProcessor:
    power = 0.0
    distance = 0.0
    pts = None
    pos_left_hand = 0.0
    pos_right_hand = 0.0
    frame = None
    mask = None

    def __init__(self, frame):
        self.power = 0.0
        self.distance = 0.0
        self.pts = None
        self.pos_left_hand = 0.0
        self.pos_right_hand = 0.0
        self.frame = frame

    def create_mask(self, image):
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(hsv, (50, 25, 25), (100, 200, 200))
        return mask

    def reduce_noise(self, image):
        kernel = np.ones((5, 5), np.uint8)
        mask_opened = cv2.morphologyEx(image, cv2.MORPH_OPEN, kernel)
        mask_closed = cv2.morphologyEx(mask_opened, cv2.MORPH_CLOSE, kernel)
        self.mask = mask_closed
        return mask_closed

    def detect_blobs(self, image):
        # Setup SimpleBlobDetector parameters.
        params = cv2.SimpleBlobDetector_Params()

        params.filterByArea = True
        params.minArea = 200
        params.filterByColor = True
        params.blobColor = 255
        params.filterByCircularity = False
        params.filterByConvexity = False
        params.filterByInertia = False

        # Create a detector with the parameters
        ver = cv2.__version__.split('.')
        if int(ver[0]) < 3:
            detector = cv2.SimpleBlobDetector(params)
        else:
            detector = cv2.SimpleBlobDetector_create(params)

        blobs = detector.detect(image)
        return blobs

    def locate_hands(self, image):
        self.pts = cv2.KeyPoint_convert(image)
        if len(self.pts) == 2:
            if self.pts[0, 0] > self.pts[1, 0]:
                self.pos_left_hand = self.pts[0, 0]
                self.pos_right_hand = self.pts[1, 0]
            else:
                self.pos_left_hand = self.pts[1, 0]
                self.pos_right_hand = self.pts[0, 0]

    def distance_hands(self):
        distance = self.pos_left_hand-self.pos_right_hand
        return distance

    def speed(self):
        val_y = []
        for x in range(len(self.pts)):
            all_val_y = self.pts[x][1]
            val_y.append(all_val_y)

        minValY = min(val_y)
        maxValY = max(val_y)

        dis = int(maxValY-minValY)

        # speed = dis/time
        # return speed

    # def calibrate_hands(self):
