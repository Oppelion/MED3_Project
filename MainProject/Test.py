import Client
import cv2

TestClient = Client.qClient()

while True:
    if cv2.waitKey(1) & 0xFF == ord("q"):
        TestClient.Send(10, 10.10)
