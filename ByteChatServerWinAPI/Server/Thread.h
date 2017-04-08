#pragma once
#include "IThreadParameter.h"
#include "WrapHandler.h"
#include <memory>

namespace mns
{
	class Thread
	{
		std::unique_ptr<WrapHandler> whThreadHandl;//���������� ������
		IThreadParameter * ptrThreadObj;//��������� �� �������� ������
	
	public:

		Thread(IThreadParameter *param = nullptr);
		
		virtual ~Thread(void);
		
		void Run(IThreadParameter * param = nullptr);//������ ������ ������ ������������������
		
		void Wait(const DWORD & WaitingTime = INFINITE);//����� ��������� ����� ������ ������
		
		void Close();//�������� ������

		bool operator!()const
		{
			return *this->whThreadHandl;
		}

		friend DWORD WINAPI ThreadFunction(LPVOID);//������������� ������� ������
	};
}