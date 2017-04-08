#pragma once
#include <exception>
#include <string>
#include "Convert.h"

namespace mns
{
	class MyExce : public std::exception//персональные исключения
	{
		std::wstring wstrErrorMessage;
		int iErrorCode;//код ошибки
	public:
		MyExce(const std::string &ErrMsg = nullptr, const int iErrCode = 0) : exception(ErrMsg.c_str()), iErrorCode(iErrCode)//конструктор с параметрами по умолчанию
		{
			this->wstrErrorMessage = Convert::StrToWStr(ErrMsg);
		}

		virtual ~MyExce()//деструктор
		{}

		std::wstring GetErrorMessage(void)const throw()//возврат сообщения
		{
			return this->wstrErrorMessage;
		}

		int GetErrorCode(void)const throw()//возврат кода ошибки
		{
			return this->iErrorCode;
		}

		friend std::ostream & operator << (std::ostream &os, const MyExce &ex)//дружествкнный оператор вывода
		{
			os << ex.what() << ", Error Code: " << ex.iErrorCode;
			return os;
		}
	};
}