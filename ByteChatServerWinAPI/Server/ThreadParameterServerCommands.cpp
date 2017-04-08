#include "ThreadParameterServerCommands.h"
#include <iostream>
#include <string>
#include <conio.h>


namespace mns
{
	//стандартные команды сервера
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
				//выбор действия
				switch (_getch())
				{
				case ESC:
					EnterCriticalSection(&this->cs);

					std::cout << "Server is shutdown..." << std::endl;

					this->Brodcast("Server is shutdown...");

					//закрытие сокета
					closesocket(this->servSocket);
					this->servSocket = SOCKET_ERROR;

					LeaveCriticalSection(&this->cs);
					break;
					
					//Сообщения от сервера
				/*case INPUT_TEXT:
					EnterCriticalSection(&this->cs);

					std::cout << "Введите сообщение: ";

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
		//проход по всем клиентам
		for (int i = 0; i < this->clients.size(); i++)
		{
			//если сокет активен
			if (this->clients[i].clientSocket && this->clients[i].clientSocket != SOCKET_ERROR)
			{
				//отсылка сообщения
				int sizeSent = send(this->clients[i].clientSocket,
					&message[0],
					strlen(&message[0]),
					0);

				//если не получилось отослать сообщение тогда сокет закрывается
				if (sizeSent == SOCKET_ERROR)
				{
					closesocket(this->clients[i].clientSocket);
					this->clients[i].clientSocket = SOCKET_ERROR;
				}
			}
		}
	}
}