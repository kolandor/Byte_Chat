#pragma once
#include <windows.h>

namespace mns
{
	class IThreadParameter//����������� ����� ��� �������� � �����
	{
	public:
		IThreadParameter() {};
		virtual ~IThreadParameter() {};

		virtual DWORD RunThreadFunction(void) = 0;//������� ������
	};
}