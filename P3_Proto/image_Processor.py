import cv2
import numpy as np
import math


class imageProcessor:
    power = 0.0
    distance = 0.0
    distance_init = 0.0
    pts = None
    pos_right_hand = [0, 0]
    pos_left_hand = [0, 0]
    guitar_string_pos = 0
    movement = False
    frame = None
    mask = None
    #time = 0.0
    numb_of_frames = 0.0
    origin_point = 0.0
    speed_right_hand = 0.0

    def set_frame(self, frame):
        self.frame = frame

    def create_mask(self, image, lower_limit, upper_limit):
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
        mask = cv2.inRange(hsv, lower_limit, upper_limit)
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
                self.pos_left_hand[0] = self.pts[0, 0]
                self.pos_left_hand[1] = self.pts[0, 1]
                self.pos_right_hand[0] = self.pts[1, 0]
                self.pos_right_hand[1] = self.pts[1, 1]
            else:
                self.pos_left_hand[0] = self.pts[1, 0]
                self.pos_left_hand[1] = self.pts[1, 1]
                self.pos_right_hand[0] = self.pts[0, 0]
                self.pos_right_hand[1] = self.pts[0, 1]

    def calibrate(self):
        self.distance_hands()
        self.distance_init = self.distance
        self.guitar_string_pos = self.pos_right_hand[1]
        return self.distance_init

    def distance_hands(self):
        if self.pos_left_hand[1] > self.pos_right_hand[1]:
            distance_y = self.pos_left_hand[1] - self.pos_right_hand[1]
        else:
            distance_y = self.pos_right_hand[1] - self.pos_left_hand[1]

        distance_x = self.pos_left_hand[0] - self.pos_right_hand[0]

        self.distance = math.sqrt((distance_x**2) + (distance_y**2))
        return self.distance

    def detect_movement(self):
        if(self.pos_right_hand[1] > (self.guitar_string_pos + 75))or(self.pos_right_hand[1] < (self.guitar_string_pos - 75)):
            self.movement = True

    def speed(self, capture):
        if self.numb_of_frames == capture.get(cv2.CAP_PROP_FPS):

            if self.origin_point != self.pos_right_hand[1]:

                if self.origin_point > self.pos_right_hand[1]:
                    distance_speed = self.origin_point-self.pos_right_hand[1]
                    self.speed_right_hand = distance_speed/1
                    self.origin_point = self.pos_right_hand[1]
                    self.numb_of_frames = 0.0
                else:
                    distance_speed = self.pos_right_hand[1]-self.origin_point
                    self.speed_right_hand = distance_speed / 1
                    self.origin_point = self.pos_right_hand[1]
                    self.numb_of_frames = 0.0
        else:
            self.numb_of_frames += 1

        return self.speed_right_hand
