﻿#include "pch.h"
#include <iostream>

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

void ErrorShow(const char* msg)
{
	int32 errCode = ::WSAGetLastError();
	cout<<msg<<" ErrorCode : "<<errCode << endl;
}

int main()
{
	WSAData wsaData;
	if (::WSAStartup(MAKEWORD(2,2),&wsaData) != 0)
		return 0;

	// TCP 통신. 서버의 주소를 받아와서 연결.

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
	{
		ErrorShow("Socket");
		return 0;
	}

	SOCKADDR_IN serverAddr; // IPv4
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777); // 80: HTTP 리틀엔디안을 빅엔디안 방식으로 바꿔줌.

	if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
	{
		ErrorShow("Connect");
		return 0;
	}

	// 연결 성공.

	cout<<"Connected To Server!"<<endl;

	while (true)
	{
		char sendBuffer[100];
		cin>>sendBuffer;
		int32 resultCode = ::send(clientSocket,sendBuffer,sizeof(sendBuffer),0);

		char recvBuffer[1000];

		int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
		if (recvLen <= 0)
		{
			int32 errCode = ::WSAGetLastError();
			cout << "Recv ErrorCode : " << errCode << endl;
			return 0;
		}

		cout << "Recv Data! Data = " << recvBuffer << endl;
		cout << "Recv Data! Len = " << recvLen << endl;
		//this_thread::sleep_for(1s);
	}

	// 소켓 리소스 반환
	::closesocket(clientSocket);

	// 윈속 종료
	::WSACleanup();
}