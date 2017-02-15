#include "Client.h"
#include "BF/System/Log.h"

#define SERVER_IP_ADDRESS "127.0.0.1"
#define SERVER_PORT "27015"

namespace BF
{
	namespace Network
	{
		Client::Client()
		{
		}

		Client::~Client()
		{
		}

		void Client::Initialize()
		{
			BF_LOG_INFO("Initializing Winsock 2");
			iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
			if (iResult != 0) 
				BF_LOG_ERROR("WSAStartup failed with error: %d\n", iResult);

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;

			// Resolve the server address and port
			iResult = getaddrinfo(SERVER_IP_ADDRESS, SERVER_PORT, &hints, &result);
			if (iResult != 0) 
			{
				BF_LOG_ERROR("getaddrinfo failed with error: %d\n", iResult);
				WSACleanup();
			}
		}

		void Client::Connect()
		{
			// Attempt to connect to an address until one succeeds
			for (ptr = result; ptr != NULL; ptr = ptr->ai_next) 
			{
				// Create a SOCKET for connecting to server
				ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
				if (ConnectSocket == INVALID_SOCKET) 
				{
					BF_LOG_ERROR("socket failed with error: %ld\n", WSAGetLastError());
					WSACleanup();
				}

				// Connect to server.
				iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
				if (iResult == SOCKET_ERROR) 
				{
					closesocket(ConnectSocket);
					ConnectSocket = INVALID_SOCKET;
					continue;
				}
				break;
			}

			freeaddrinfo(result);

			if (ConnectSocket == INVALID_SOCKET) 
			{
				BF_LOG_ERROR("Unable to connect to server!\n");
				WSACleanup();
			}
		}

		void Client::Run()
		{
		}

		void Client::Shutdown()
		{
		}

		void Client::CleanUp()
		{
		}
	}
}