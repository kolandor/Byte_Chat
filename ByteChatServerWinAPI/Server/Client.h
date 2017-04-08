#pragma once
#include <winsock.h>
#include <string>

struct client
{
	std::string login;
	SOCKET clientSocket;
};