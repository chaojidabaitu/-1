#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include "C0704.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "7001"

int main(int argc, char** argv)
{
	{
		C0704::msg0704 = C0704::Str2Array(C0704::str0704);
		C0704::Generate0704(C0704::msg0704, C0704::msg0704len);
	}
	WSADATA wsaData;
	SOCKET ConnectSocket[3096] = { INVALID_SOCKET };
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	const char* sendbuf = "this is a test";
	char recvbuf[DEFAULT_BUFLEN];
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	// Validate the parameters
	if (argc != 2)
	{
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0)
	{
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	// Resolve the server address and port
	iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
	if (iResult != 0)
	{
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Attempt to connect to an address until one succeeds
	for (int i = 0; i < C0704::send0704len; i++)
	{
		for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			// Create a SOCKET for connecting to server
			ConnectSocket[i] = socket(ptr->ai_family, ptr->ai_socktype,
				ptr->ai_protocol);
			if (ConnectSocket[i] == INVALID_SOCKET)
			{
				printf("socket failed with error: %ld\n", WSAGetLastError());
				WSACleanup();
				return 1;
			}

			// Connect to server.
			iResult = connect(ConnectSocket[i], ptr->ai_addr, (int)ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				closesocket(ConnectSocket[i]);
				ConnectSocket[i] = INVALID_SOCKET;
				continue;
			}
			break;
		}

		if (ConnectSocket[i] == INVALID_SOCKET)
		{
			printf("Unable to connect to server!\n");
			WSACleanup();
			return 1;
		}
	}

	freeaddrinfo(result);

	// Send an initial buffer
	int ccc = 0;
	do
	{
		for (int i = 0; i < C0704::send0704len; i++)
		{
			iResult = send(ConnectSocket[i], (char*)(C0704::send0704[i]), C0704::msg0704len, 0);
			if (iResult == SOCKET_ERROR)
			{
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ConnectSocket[i]);
				WSACleanup();
				return 1;
			}
			//Sleep(100);
		}
		C0704::ChangeTime();
		printf("c=%d\r\n", ccc);
		if ((ccc % 10) == 0)
		{
			// Receive until the peer closes the connection
			for (int i = 0; i < C0704::send0704len; i++)
			{
				//do
				{
					iResult = recv(ConnectSocket[i], recvbuf, recvbuflen, 0);
					if (iResult > 0)
						printf("Bytes received: %d\n", iResult);
					else if (iResult == 0)
						printf("Connection closed\n");
					else
						printf("recv failed with error: %d\n", WSAGetLastError());

				}
				//while (iResult > 0);
			}
		}
		Sleep(100);
	} while ((++ccc) < 600);

	// cleanup
	for (int i = 0; i < C0704::send0704len; i++)
	{
		// shutdown the connection since no more data will be sent
		iResult = shutdown(ConnectSocket[i], SD_BOTH);
		if (iResult == SOCKET_ERROR)
		{
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket[i]);
			WSACleanup();
			return 1;
		}

		closesocket(ConnectSocket[i]);
	}
	WSACleanup();

	return 0;
}