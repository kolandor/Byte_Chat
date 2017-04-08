#pragma once
#include "IThreadParameter.h"
#include "WrapHandler.h"
#include <memory>

namespace mns
{
	class Thread
	{
		std::unique_ptr<WrapHandler> whThreadHandl;//дескриптор потока
		IThreadParameter * ptrThreadObj;//указатель на параметр потока
	
	public:

		Thread(IThreadParameter *param = nullptr);
		
		virtual ~Thread(void);
		
		void Run(IThreadParameter * param = nullptr);//запуск работы потока параметризированый
		
		void Wait(const DWORD & WaitingTime = INFINITE);//время ожэидания конца работы потока
		
		void Close();//закрытие потока

		bool operator!()const
		{
			return *this->whThreadHandl;
		}

		friend DWORD WINAPI ThreadFunction(LPVOID);//дружественная функция потока
	};
}