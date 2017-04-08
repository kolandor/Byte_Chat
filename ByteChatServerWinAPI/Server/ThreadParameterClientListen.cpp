#include "ThreadParameterClientListen.h"
#include <iostream>


namespace mns
{
	ThreadParameterClientListen::ThreadParameterClientListen(int index, int &clientCount, CRITICAL_SECTION &cs, std::vector<client> &clients):
		cs(cs), clients(clients), index(index), clientCount(clientCount)
	{
	}


	ThreadParameterClientListen::~ThreadParameterClientListen()
	{
	}
	DWORD ThreadParameterClientListen::RunThreadFunction(void)
	{
		try
		{
			while(this->clients[this->index].clientSocket 
				!=
				SOCKET_ERROR)
			{
				std::string messageBuffer(BUFFER_SIZE, '\0');

				//приём сообщения
				int receivedSize = recv(this->clients[this->index].clientSocket,
					&messageBuffer[0],
					messageBuffer.size(),
					0);

				if(receivedSize != SOCKET_ERROR && this->clients[this->index].clientSocket != SOCKET_ERROR)
				{
					//певое подключение если ника нет
					if(!this->clients[this->index].login.size())
					{
						this->clients[this->index].login = messageBuffer;
						this->clients[this->index].login.resize(strlen(&messageBuffer[0]));
						char connectMsg[] = "Connected: ";

						//вывод серверу инфо о подключенном клиенте
						std::cout << connectMsg << messageBuffer.c_str() << std::endl;
						
						EnterCriticalSection(&this->cs);

						//массовая рассылка о тодключении клиента
						Brodcast(connectMsg + messageBuffer);
					}
					else//если логин есть, значит, рассылаем сообщение клиента
					{
						EnterCriticalSection(&this->cs);

						std::cout << this->clients[this->index].login.c_str() << ": " << messageBuffer.c_str() << std::endl;
						//массовая рассылка сообщения клиента
						std::string longMessageCreator = this->clients[this->index].login + ": " + messageBuffer;
						Brodcast(longMessageCreator);
					}
					LeaveCriticalSection(&this->cs);
				}
				else
				{
					EnterCriticalSection(&this->cs);
					closesocket(this->clients[this->index].clientSocket);
					this->clients[this->index].clientSocket = SOCKET_ERROR;
					LeaveCriticalSection(&this->cs);
				}
			}
		}
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
		}
		//отключение клиента
		EnterCriticalSection(&this->cs);
		
		//закрытие сокета
		closesocket(this->clients[this->index].clientSocket);
		this->clients[this->index].clientSocket = NULL;

		Brodcast("Disconnected: " + this->clients[this->index].login);

		std::cout << "Disconnected: " << this->clients[this->index].login.c_str() << std::endl;
		//обнуление логина
		this->clients[this->index].login.resize(0);

		//уменьшение кол-ва клиентов
		this->clientCount--;

		LeaveCriticalSection(&this->cs);

		return 0;
	}

	void ThreadParameterClientListen::Brodcast(std::string message)
	{
		//проход по всем клиентам
		for(int i = 0; i < this->clients.size(); i++)
		{
			//если сокет активен
			if(this->clients[i].clientSocket && this->clients[i].clientSocket != SOCKET_ERROR)
			{
				//отсылка сообщения
				int sizeSent = send(this->clients[i].clientSocket,
					&message[0],
					strlen(&message[0]),
					0);

				//если не получилось отослать сообщение тогда сокет закрывается
				if(sizeSent == SOCKET_ERROR)
				{
					closesocket(this->clients[i].clientSocket);
					this->clients[i].clientSocket = SOCKET_ERROR;
				}
			}
		}
	}
}