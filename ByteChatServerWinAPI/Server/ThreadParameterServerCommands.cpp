#include "ThreadParameterServerCommands.h"
#include <iostream>
#include <string>
#include <conio.h>


namespace mns
{
	//����������� ������� �������
	enum
	{
		ESC = 27,
		INPUT_TEXT = 116
	};

	ThreadParameterServerCommands::ThreadParameterServerCommands(CRITICAL_SECTION &cs, std::vector<client> &clients, SOCKET &servSocket) :
		cs(cs), clients(clients), servSocket(servSocket)
	{
	}


	ThreadParameterServerCommands::~ThreadParameterServerCommands()
	{
	}
	DWORD ThreadParameterServerCommands::RunThreadFunction(void)
	{
		try
		{
			while (this->servSocket
				!=
				SOCKET_ERROR)
			{
				//����� ��������
				switch (_getch())
				{
				case ESC:
					EnterCriticalSection(&this->cs);

					std::cout << "Server is shutdown..." << std::endl;

					this->Brodcast("Server is shutdown...");

					//�������� ������
					closesocket(this->servSocket);
					this->servSocket = SOCKET_ERROR;

					LeaveCriticalSection(&this->cs);
					break;
					
					//��������� �� �������
				/*case INPUT_TEXT:
					EnterCriticalSection(&this->cs);

					std::cout << "������� ���������: ";

					std::string message;

					std::getline(std::cin, message);

					message = "Server: " + message;

					this->Brodcast(message);

					LeaveCriticalSection(&this->cs);
					break;*/
				}
			}
		}
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}

		return 0;
	}

	void ThreadParameterServerCommands::Brodcast(std::string message)
	{
		//������ �� ���� ��������
		for (int i = 0; i < this->clients.size(); i++)
		{
			//���� ����� �������
			if (this->clients[i].clientSocket && this->clients[i].clientSocket != SOCKET_ERROR)
			{
				//������� ���������
				int sizeSent = send(this->clients[i].clientSocket,
					&message[0],
					strlen(&message[0]),
					0);

				//���� �� ���������� �������� ��������� ����� ����� �����������
				if (sizeSent == SOCKET_ERROR)
				{
					closesocket(this->clients[i].clientSocket);
					this->clients[i].clientSocket = SOCKET_ERROR;
				}
			}
		}
	}
}