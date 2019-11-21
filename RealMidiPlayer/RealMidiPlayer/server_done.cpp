#include <iostream>		//Standard
#include <WinSock2.h>	//Network library
#include <ws2tcpip.h>	//Library used by WinSock2
#include "server_done.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//     _   _  U _____ u   ____    U _____ u      __  __      _       ____               ____       _   _      _       ____     ____   U _____ u _   _    ____	  //
//    |'| |'| \| ___"|/U |  _"\ u \| ___"|/    U|' \/ '|uU  /"\  uU /"___|u   ___    U /"___|     |'| |'| U  /"\  u U|  _"\ uU|  _"\ u\| ___"|/| \ |"|  / __"| u  //
//   /| |_| |\ |  _|"   \| |_) |/  |  _|"      \| |\/| |/ \/ _ \/ \| |  _ /  |_"_|   \| | u      /| |_| |\ \/ _ \/  \| |_) |/\| |_) |/ |  _|" <|  \| |><\___ \/   //
//   U|  _  |u | |___    |  _ <    | |___       | |  | |  / ___ \  | |_| |    | |     | |/__     U|  _  |u / ___ \   |  __/   |  __/   | |___ U| |\  |u u___) |   //
//    |_| |_|  |_____|   |_| \_\   |_____|      |_|  |_| /_/   \_\  \____|  U/| |\u    \____|     |_| |_| /_/   \_\  |_|      |_|      |_____| |_| \_|  |____/>>  //
//   //   \\  <<   >>   //   \\_  <<   >>     <<,-,,-.   \\    >>  _)(|_.-,_|___|_,-._// \\      //   \\  \\    >>  ||>>_    ||>>_    <<   >> ||   \\,-.)(  (__)  //
//  (_") ("_)(__) (__) (__)  (__)(__) (__)     (./  \.) (__)  (__)(__)__)\_)-' '-(_/(__)(__)    (_") ("_)(__)  (__)(__)__)  (__)__)  (__) (__)(_")  (_/(__)		  //
//																																								  //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma comment(lib, "Ws2_32.lib")																			//Compiler directive which leaves a comment in generated object file
using namespace std;

void passData(char* indexZero)																				// Sets the recvArray to the recieved data
{/*MUST HAVE 3 INDEXES*/
	for (int i = 0; i < 3; i++)
	{
		recvArray[i] = *(indexZero + i);																	//Assigning recvArray to the dereferenced pointer position of the recieved data
																											//indexZero is the pointer recieved, thats points to the memory position of index 0 of the array send from python
																											//indexZero + 1 is the next memory position, and since the recieved data is an array, then every index of that array is ordered in memory
		cout << "Data recieved from the server untreated: " << recvArray[i] << "\n";
	}
	getData = true;
}



void recieveData(SOCKET s, char* _memPosIndexZero, int len) 												// Function called recieveData, takes the socket that recieves the data, a pointer array which points to index zero in the recieved data
{
	int iResult;
	do {
		iResult = recv(s, _memPosIndexZero, len, 0);														//iResult is the amount of bytes recieved
		if (iResult > 0)
		{
			passData(_memPosIndexZero);																		//Function found on line 20
		}
		else if (iResult == 0)																				//Checks if the data recieved doesn't contain anything
			printf("Connection closed\n");
		else
			printf("recv failed: %d\n", WSAGetLastError());													//Prints the error status for the last Windows Sockets operation that failed.
	} while (iResult > 0);																					//Runs the code above while iResult contains information
}

int server_main()
{
	WSADATA WSAData;																						// Declare WSADATA object, only used once during WSAStartup, tells the program we will be using sockets

	SOCKET server, client;																					// The socket
	
	SOCKADDR_IN serverAddr, clientAddr;																		// An object which contains information about the socket

																											
	WSAStartup(MAKEWORD(2, 0), &WSAData);		/*..........................................................Without this line, client will be denied access
																											First parameter: MAKEWORD, specifies the type of winsock being used
																											Second parameter: Adress for the WSAData object we created
																											*/

	server = socket(AF_INET, SOCK_STREAM, 0);	/*..........................................................Initializes the socket, AF_INET defines the format for the adress as IPv4
																											SOCK_STREAM specifies the type of connection as TCP
																											*/

	serverAddr.sin_addr.s_addr = INADDR_ANY;																// IP address for the server (LocalHost)

	serverAddr.sin_family = AF_INET;																		// Connection type for the server (TCP)

	serverAddr.sin_port = htons(60000);																		// Port number used by the server

	bind(server, (SOCKADDR*)&serverAddr, sizeof(serverAddr));												// Binds the socket with the ip address w. server socket, address information and size of the second parameter (the address)

	listen(server, SOMAXCONN);					/*..........................................................Listener that allows clients to connect
																											first parameter is the socket server
																											second parameter is the maximum lenght of the queue of pending connections (SOMAXCONN makes the backlog set a maximum reasonable value)
																											*/

	cout << "Listening for incoming connections..." << endl;												//Initial message when starting the server

	int clientAddrSize = sizeof(clientAddr);																//Stores the clientAddrSize
	while (true)
	{
		if ((client = accept(server, (SOCKADDR*)&clientAddr, &clientAddrSize)) != INVALID_SOCKET )			//This runs when a client has succesfully connected to the server
		{
			cout << "Client connected!" << endl;
				
			char* _memPosIndexZero = new char[10];															//Char pointer used to store recieved bytes
			recieveData(client, _memPosIndexZero, 10);														//Function call that takes the socket which is to be watched, array for storaging and the length of the pointer array

			cout << "End2" << endl;
			//closesocket(client);																			//Shuts down the socket connection if used
		}
		cout << "End" << endl;
		return 0;
	}
}