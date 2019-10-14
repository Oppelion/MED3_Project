import Client
import cv2

cam = cv2.VideoCapture(0)

while True:
    ret, frame = cam.read()
    cv2.imshow("h", frame)
    if cv2.waitKey(1) & 0xFF == ord("c"):
        break
    if cv2.waitKey(1) & 0xFF == ord("q"):
        Client.SockConnect()
    if cv2.waitKey(1) & 0xFF == ord("r"):
        Client.SendInfo(5, 5, 5)

cam.release()
cv2.destroyAllWindows()