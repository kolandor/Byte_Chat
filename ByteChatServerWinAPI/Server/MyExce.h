#pragma once
#include <exception>
#include <string>
#include "Convert.h"

namespace mns
{
	class MyExce : public std::exception//������������ ����������
	{
		std::wstring wstrErrorMessage;
		int iErrorCode;//��� ������
	public:
		MyExce(const std::string &ErrMsg = nullptr, const int iErrCode = 0) : exception(ErrMsg.c_str()), iErrorCode(iErrCode)//����������� � ����������� �� ���������
		{
			this->wstrErrorMessage = Convert::StrToWStr(ErrMsg);
		}

		virtual ~MyExce()//����������
		{}

		std::wstring GetErrorMessage(void)const throw()//������� ���������
		{
			return this->wstrErrorMessage;
		}

		int GetErrorCode(void)const throw()//������� ���� ������
		{
			return this->iErrorCode;
		}

		friend std::ostream & operator << (std::ostream &os, const MyExce &ex)//������������� �������� ������
		{
			os << ex.what() << ", Error Code: " << ex.iErrorCode;
			return os;
		}
	};
}