#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

void passData(char* indexZero)
{/*MUST HAVE 3 INDEXES*/
	int recvArray[3];
	for (int i = 0; i < 3; i++)
	{
		recvArray[i] = *(indexZero + i); //Assigning recvArray to the dereferenced pointer position of the recieved data
		//indexZero is the pointer recieved, thats points to the memory position of index 0 of the array send from python
		//indexZero + 1 is the next memory position, and since the recieved data is an array, then every index of that array is ordered in memory
	}

	/*Implement function call that sends data and starts the MIDI player here*/
	/*StartMIDI(recvArray[]);*/
}

void recieveData(SOCKET s, char* _memPosIndexZero, int ignoreMe) {
	int iResult = 1;
	do {
		iResult = recv(s, _memPosIndexZero, bufflen, 0);
		if (iResult > 0)
		{
			passData(_memPosIndexZero);
			printf("Bytes received: %d\n", *_memPosIndexZero);		//Print dereferenced value of the memory position of recieved array[0]
			printf("Second point: %d\n", *(_memPosIndexZero + 1));	//Print dereferenced value of the memory position + 1(next memory location) of recieved array[0]
			printf("Third point: %d\n", *(_memPosIndexZero + 2));	//Print dereferenced value of the memory position + 2(next next memory location) of recieved array[0]
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

			char* _memPosIndexZero = new char[256];
			recieveData(client, _memPosIndexZero, 256);

			//closesocket(client);
		}
	}
}