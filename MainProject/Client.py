import socket

# makes socket into an object, with the constructor set to the standard
# Address Format Internet and Socket Stream which is TCP
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Create a socket
def SockConnect():
    # connects to the local host ip at port 80.000
    sock.connect(('localhost', 60000))

# Send two variables x and y
def SendInfo(x, y):
    # function call for sending to the defined IP and Port
    sock.send(x, y)
    # Can receive up to 4096 bytes from a peer
    sock.recv(4096)

# Closes the socket so that it is unused
def CloseSocket():
    sock.close()
