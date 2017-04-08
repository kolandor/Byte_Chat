#include <Windows.h>
#include <Winsock.h>
#include <iostream>
#include "Client.h"
#include <locale.h>
#include "ThreadParameterClientListen.h"
#include "Thread.h"
#include "MyExce.h"
#include <vector>
#include <conio.h>
#include "WrapHandler.h"

#pragma comment(lib, "Ws2_32.lib")
#include "ThreadParameterServerCommands.h"

//�������������� DLL

int main()
{
	//setlocale(LC_ALL, "");
	try
	{
		mns::WrapHandler hColor = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hColor, 0xA);
		//��������� ������������� �������
		WSADATA verSoc = { 0 };

		std::cout << "Initialization socket vertion" << std::endl;
		if (WSAStartup(0x0202, &verSoc))
		{
			throw(mns::MyExce("Can't initialize a socket servion",
				WSAGetLastError()));
		}

		//��������� �����
		std::cout << "Creating the server socket" << std::endl;
		SOCKET servSocket = socket(AF_INET, SOCK_STREAM, 0);
		if(servSocket == INVALID_SOCKET)
		{
			WSACleanup();
			throw(mns::MyExce("Can't create the server socket",
				WSAGetLastError()));
		}

		std::cout << "Input port: ";
		int port = 0;
		std::cin >> port;

		//��������� ����������
		sockaddr_in local_addr = { 0 };
		local_addr.sin_family = AF_INET;//��������� ����������
		local_addr.sin_port = htons(port);//����
		local_addr.sin_addr.s_addr = NULL;//��������� �����

		//������ ������ �� ���������� ������
		std::cout << "Binding a socket with the sockaddr struct" << std::endl;
		if(bind(servSocket,
			reinterpret_cast<sockaddr*>(&local_addr),
			sizeof(local_addr)) == SOCKET_ERROR)
		{
			closesocket(servSocket);
			WSACleanup();
			throw(mns::MyExce("Can't bind a socket with the sockaddr struct",
				WSAGetLastError()));
		}


		std::cout << "Input the max amount of clients(no less than 5): ";
		int clienCount = 0;
		std::cin >> clienCount;

		if (clienCount < 5)
			throw(mns::MyExce("too few amount of clients"));

		std::vector<client> clientSockets(clienCount);

			//��������� ������������� ����� �����������
		std::cout << "Setting the max amount of clients" << std::endl;
		if (listen(servSocket, clientSockets.size()) == SOCKET_ERROR)
		{
			closesocket(servSocket);
			WSACleanup();
			throw(mns::MyExce("Can't set max amount of clients",
				WSAGetLastError()));
		}

		//����������� ������
		CRITICAL_SECTION critSec = { 0 };
		std::cout << "Initialization a critical section" << std::endl;
		InitializeCriticalSection(&critSec);

		//���������� ������������ ��������
		int connectedClientsCount = 0;

		std::cout << "Server online, waiting for clients..." << std::endl;

		mns::Thread(new mns::ThreadParameterServerCommands(critSec, clientSockets, servSocket)).Run();

		while (servSocket != SOCKET_ERROR)
		{
			try
			{
				//������������ ������
				SOCKET connectingSocketClient = NULL;
				//���� � ������������ �������
				sockaddr_in clientAddrInfo = { 0 };

				//������ ��������� ������������� �������
				int sizeClientAddrInfo = sizeof(clientAddrInfo);

				//�������� ����������� �������
				connectingSocketClient = accept(servSocket,
					reinterpret_cast<sockaddr*>(&clientAddrInfo),
					&sizeClientAddrInfo);

				//�������� ������������ �����������
				if (connectingSocketClient == INVALID_SOCKET && servSocket != INVALID_SOCKET)
					throw(mns::MyExce("Couldn't connect a client"));
				if (servSocket == INVALID_SOCKET)
					continue;
				else
				{
					//�������� ��������� ����
					if (connectedClientsCount < clientSockets.size())
					{
						//���� � ����������� ������
						EnterCriticalSection(&critSec);

						for (int i = 0; i < clientSockets.size(); i++)
						{
							if (!clientSockets[i].clientSocket)
							{
								//�������� ������
								clientSockets[i].clientSocket = connectingSocketClient;

								mns::Thread(new mns::ThreadParameterClientListen(i, connectedClientsCount, critSec, clientSockets)).Run();
								break;
							}
						}
						connectedClientsCount++;
						LeaveCriticalSection(&critSec);
					}
					else
					{
						char errorMesage[] = "Server is full, try connection later...";
						send(connectingSocketClient, errorMesage, sizeof(errorMesage), 0);
						closesocket(connectingSocketClient);
						throw mns::MyExce("Can't connect a client");
					}
				}
			}
			catch (mns::MyExce &ex)
			{
				std::cout << ex.what() << std::endl;
			}
		}
		//�������� ����������� ������
		DeleteCriticalSection(&critSec);

		//�������� ������
		closesocket(servSocket);

	}
	catch (std::exception &ex)
	{
		MessageBoxA(nullptr, ex.what(), NULL, MB_ICONERROR);
	}
	catch (...)
	{
		MessageBoxA(nullptr, "Undefined exception!", NULL, MB_ICONERROR);
	}

	std::cout << "Press any key to exit..." << std::endl;

	_getch();

	//������������ ���������
	WSACleanup();
	return 0;
}