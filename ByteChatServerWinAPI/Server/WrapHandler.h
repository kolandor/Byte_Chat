#pragma once
#include  <windows.h>

namespace mns
{
	class WrapHandler//������ ��� ����������� ������
	{
		HANDLE hHandler;//����������
	public:
		WrapHandler(const HANDLE &hThr = 0) : hHandler(hThr)//����������� � ����������� �� ���������
		{}

		WrapHandler(const WrapHandler &) = delete;//������ ������������ �����������

		virtual ~WrapHandler()//����������
		{
			if (this->hHandler)//�������� ����������� �� ��������
			{
				CloseHandle(this->hHandler);//��������
				this->hHandler = 0;
			}
		}

		const WrapHandler & operator = (const WrapHandler &) = delete;//������ ��������� �����������

		operator HANDLE (void)const throw()//�������� ��������
		{
			return this->hHandler;
		}

		bool operator ! (void)const throw()//�������� �������� �����������
		{
			return this->hHandler;
		}
	};
}