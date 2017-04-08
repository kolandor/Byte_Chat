#pragma once
#include "IThreadParameter.h"
#include <vector>
#include "Client.h"

namespace mns
{
	enum
	{
		BUFFER_SIZE = 1024,
		LOGIN_LENGHT = 20
	};

	class ThreadParameterClientListen : public IThreadParameter
	{
		CRITICAL_SECTION &cs;
		std::vector<client> &clients;
		int &clientCount;
		int index;
	public:
		ThreadParameterClientListen(int index,int &clientCount, CRITICAL_SECTION &cs, std::vector<client> &clients);
		virtual ~ThreadParameterClientListen();

		virtual DWORD RunThreadFunction(void);
	private:
		void Brodcast(std::string message);
	};

}