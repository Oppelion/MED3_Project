import Client
import cv2

TestClient = Client.Client()

while True:
    if cv2.waitKey(1) & 0xFF == ord("q"):
        TestClient.SendInfo(10, 10.10)
