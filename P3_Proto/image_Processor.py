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
    origin_point = 0.0
    speed_right_hand = 0.0
    lower_limit = (100, 70, 150)
    upper_limit = (140, 255, 255)
    detector = 0

    def create_blob_detector(self):
        params = cv2.SimpleBlobDetector_Params()  # ..........................Create blob detector with parameters.

        params.filterByArea = True  # ........................................Filter blobs by total area.
        params.minArea = 700  # ..............................................Minimum area of a blob to be detected.
        params.maxArea = 15000  # ............................................Maximum area of a blob to be detected.
        params.filterByColor = True  # .......................................Filter blobs by colour.
        params.blobColor = 255  # ............................................Only detect white spots as blobs.
        params.filterByCircularity = False  # ................................Do not filter by circularity of blobs.
        params.filterByConvexity = False  # ..................................Do not filter by convexity of blobs.
        params.filterByInertia = False  # ....................................Do not filter by inertia of blobs.

        ver = cv2.__version__.split('.')  # ..................................Set version of blob detector created.
        if int(ver[0]) < 3:
            self.detector = cv2.SimpleBlobDetector(params)  # ................Create blob detector.
        else:
            self.detector = cv2.SimpleBlobDetector_create(params)  # .........Create blob detector.

    def set_frame(self, frame):  # ...........................................Setter method for frame attribute.
        self.frame = frame  # ................................................Sets frame attribute to the arg.
        self.frame = cv2.GaussianBlur(self.frame, (5, 5), 0)  # ..............Apply gaussian blur to the frame.

    def create_mask(self, image):  # .........................................Method to create binary mask of frame.
        hsv = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)  # ......................Convert frame to hsv colour space.
        mask = cv2.inRange(hsv, self.lower_limit, self.upper_limit)  # .......Colour threshold to create binary mask.
        return mask  # .......................................................Return binary mask.

    def reduce_noise(self, image):  # ........................................Method to reduce noise in mask.
        kernel = np.ones((5, 5), np.uint8)  # ................................5X5 kernel for the opening operation.
        kernel_close = np.ones((9, 9), np.uint8)  # ..........................9X9 kernel for the closing operation.
        mask_opened = cv2.morphologyEx(image, cv2.MORPH_OPEN, kernel)  # .....Function call to eradicate small blobs.
        mask_closed = cv2.morphologyEx(mask_opened,
                                       cv2.MORPH_CLOSE, kernel_close)  # .....Function call to fill in blobs with holes.
        self.mask = mask_closed  # ...........................................Set mask with reduced noise.
        return mask_closed  # ................................................Return mask with reduced noise.

    def detect_blobs(self, image):  # ........................................Method for blob detection.
        blobs = self.detector.detect(image)  # ...............................Function call to detect blobs in image arg
        return blobs  # ......................................................Return detected blobs.

    def locate_hands(self, image):  # ........................................Method to detect location of users' hands.
        self.pts = cv2.KeyPoint_convert(image)  # ............................Create key points on centre of all blobs.
        if len(self.pts) == 2:  # ............................................Execute ONLY when there are two blobs.
            if self.pts[0, 0] > self.pts[1, 0]:  # ...........................Checks which blob is the right hand.
                self.pos_left_hand[0] = self.pts[0, 0]  # ....................set X position of left hand.
                self.pos_left_hand[1] = self.pts[0, 1]  # ....................set Y position of left hand.
                self.pos_right_hand[0] = self.pts[1, 0]  # ...................set X position of right hand.
                self.pos_right_hand[1] = self.pts[1, 1]  # ...................set Y position of right hand.
            else:
                self.pos_left_hand[0] = self.pts[1, 0]  # ....................set X position of left hand.
                self.pos_left_hand[1] = self.pts[1, 1]  # ....................set Y position of left hand.
                self.pos_right_hand[0] = self.pts[0, 0]  # ...................set X position of right hand.
                self.pos_right_hand[1] = self.pts[0, 1]  # ...................set Y position of right hand.

    def calibrate(self):  # ..................................................Method for calibrating MIDI segment sizes.
        self.distance_init = self.distance  # ................................Set initial distance as distance at call.
        self.guitar_string_pos = self.pos_right_hand[1]  # ...................Set guitar string position at right hand.
        return self.distance_init  # .........................................return initial distance.

    def distance_hands(self):  # .............................................Method for finding distance between hands.
        if self.pos_left_hand[1] > self.pos_right_hand[1]:  # ................Checks which hand is higher.
            distance_y = self.pos_left_hand[1] - self.pos_right_hand[1]  # ...Subtract Y positions.
        else:
            distance_y = self.pos_right_hand[1] - self.pos_left_hand[1]  # ...Subtract Y positions.
        distance_x = self.pos_left_hand[0] - self.pos_right_hand[0]  # .......Subtract X positions.
        self.distance = math.sqrt(
            (distance_x ** 2) + (distance_y ** 2))  # ........................Formula for finding length of a vector.
        return self.distance  # ..............................................Return distance between hands.

    def speed(self):  # .....................................................Method for calculating speed.
        if self.origin_point != self.pos_right_hand[1]:  # ..................Checks if right hand has moved.
            if self.origin_point > self.pos_right_hand[1]:  # ...............Checks if right hand has moved down.
                distance_speed = self.origin_point - \
                                 self.pos_right_hand[1]  # ..................Found distance on Y axis
                self.speed_right_hand = distance_speed  # ...................sets speed.
                self.origin_point = self.pos_right_hand[1]  # ...............Sets origin as right hand pos for next time
            else:
                distance_speed = self.pos_right_hand[1] - self.origin_point  # Find distance on Y axis.
                self.speed_right_hand = distance_speed  # ...................Sets speed.
                self.origin_point = self.pos_right_hand[1]  # ...............Sets origin as right hand pos for next time

        if self.speed_right_hand <= 10:  # ..................................checks if value of speed is less than 8.
            self.speed_right_hand = 0  # ....................................Sets speed to 0.
        if 8 < self.speed_right_hand < 130:  # ..............................Checks if speed is within range.
            self.speed_right_hand = (self.speed_right_hand / 130) * 100  # ..Adjusts speed value to between 0 - 100.
        if self.speed_right_hand >= 130:  # .................................Checks if speed is over 130
            self.speed_right_hand = 100  # ..................................Sets speed to 100.
        return self.speed_right_hand  # .....................................Return adjusted speed of right hand.
