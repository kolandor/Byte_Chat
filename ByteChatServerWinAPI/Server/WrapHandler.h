#pragma once
#include  <windows.h>

namespace mns
{
	class WrapHandler//обёртка для дескриптора потока
	{
		HANDLE hHandler;//дескриптор
	public:
		WrapHandler(const HANDLE &hThr = 0) : hHandler(hThr)//конструктор с параметрами по умолчанию
		{}

		WrapHandler(const WrapHandler &) = delete;//запрет конструктора копирования

		virtual ~WrapHandler()//деструктор
		{
			if (this->hHandler)//проверка дескриптора на открытие
			{
				CloseHandle(this->hHandler);//закрытие
				this->hHandler = 0;
			}
		}

		const WrapHandler & operator = (const WrapHandler &) = delete;//запрет оператора копирования

		operator HANDLE (void)const throw()//передача значения
		{
			return this->hHandler;
		}

		bool operator ! (void)const throw()//проверка открытия дескриптора
		{
			return this->hHandler;
		}
	};
}