#pragma once
#include "IThreadParameter.h"
#include "Client.h"
#include <vector>

namespace mns
{
	class ThreadParameterServerCommands : public IThreadParameter
	{
		CRITICAL_SECTION &cs;
		std::vector<client> &clients;
		SOCKET &servSocket;
	public:
		ThreadParameterServerCommands(CRITICAL_SECTION &cs, std::vector<client> &clients, SOCKET &servSocket);
		virtual ~ThreadParameterServerCommands();

		virtual DWORD RunThreadFunction(void);
	private:
		void Brodcast(std::string message);
	};
}