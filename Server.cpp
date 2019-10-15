#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

int recvArray[3];

void recieveData(SOCKET s, char* buffer, int bufflen) {
	int iResult = 10;
	do {
		iResult = recv(s, buffer, bufflen, 0);
		if (iResult > 0)
		{

			/*!!OBS!! IMPORTANT Array only has 3 indexes*/

			for (int i = 0; i < 3; i++)
			{
				recvArray[i] = *(buffer + i);
			}
			/*First index in sended array*/		printf("Bytes received: %d\n", *buffer);
			/*Second index in sended array*/	printf("Second point: %d\n", *(buffer + 1));
			/*Third index in sended array*/		printf("Third point: %d\n", *(buffer + 2));

			/*!!OBS!! IMPORTANT Array only has 3 indexes*/

		}
		else if (iResult == 0)
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());
	} while (iResult > 0);
}

int main()
{
	// Declare WSADATA object, only used once during WSAStartup, tells the program we will be using sockets
	WSADATA WSAData;

	// The socket
	SOCKET server, client;

	// An object which contains information about the socket
	SOCKADDR_IN serverAddr, clientAddr;

	// First parameter: MAKEWORD, specifies the type of winsock being used
	// Second parameter: Adress for the WSAData object we created
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	// Initializes the socket, AF_INET defines the format for the adress as IPv4
	// SOCK_STREAM specifies the type of connection as TCP
	server = socket(AF_INET, SOCK_STREAM, 0);

	// IP address for the server (LocalHost)
	serverAddr.sin_addr.s_addr = INADDR_ANY;
	// Connection type for the server (TCP)
	serverAddr.sin_family = AF_INET;
	// Port number used by the server
	serverAddr.sin_port = htons(60000);

	// Binds the socket with the ip address w. server socket, address information and size of the second parameter (the address)
	bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	/*
		Listener that allows clients to connect
		first parameter is the socket server
		second parameter is the maximum lenght of the queue of pending connections (SOMAXCONN makes the backlog set a maximum reasonable value)
	*/
	listen(server, SOMAXCONN);

	/* UNKNOWN CODE :=) */

	cout << "Listening for incoming connections..." << endl;

	int clientAddrSize = sizeof(clientAddr);
	while (true)
	{
		if ((client = accept(server, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET)
		{
			cout << "Client connected!" << endl;
			cout << x << " " << y << endl;

			char* buffer = new char[256];
			recieveData(client, buffer, 256);

			//closesocket(client);
		}
	}
}