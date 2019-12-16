import socket


class client:
    spamFilter = True
    clientConnected = False
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Make a socket object.
                                                              # Address Format Internet and Socket Stream which is TCP

    def SockConnect(self):                                    # Method to connect to the server.
        self.sock.connect(('localhost', 60000))               # connects to the local host ip at port 80.000.

    def SendInfo(self, x, y, z):                              # Method that sends three variables to the server.
        data = [x, y, z]                                      # Array that stores the data to be sent.
        data2 = bytearray(data)                               # Convert the data into bytes, stored in a new array.
        self.sock.sendall(data2)                              # function call for sending to the defined IP and Port.
        print(self.spamFilter)

    def CloseSocket(self):                                    # Method to close the socket.
        self.sock.close()                                     # Closes the socket.
