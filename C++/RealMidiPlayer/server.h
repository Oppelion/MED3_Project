#pragma once
#ifndef SERVER_H
#define SERVER_H
#include <WinSock2.h>	//Network library
#include <ws2tcpip.h>	//Library used by WinSock2

extern int recvArray[3];
extern bool getData;
class Server
{
public:
	Server();
	void passData(char* indexZero);
	void receiveData(SOCKET s, char* _memPosIndexZero, int len);
	int server_main();
};
#endif