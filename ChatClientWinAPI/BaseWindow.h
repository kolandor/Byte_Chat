#pragma once
#include <string>
#include <windows.h>

namespace mns
{
	class BaseWindow
	{
		//���������� ����
		HWND _hwndWindow;

		int _iID;

		//��� ����
		std::string _strWindowName;

	public:
		BaseWindow();
		virtual ~BaseWindow();
	};
}
