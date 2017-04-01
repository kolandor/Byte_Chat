#pragma once
#include <string>
#include <windows.h>

namespace mns
{
	class BaseWindow
	{
		//дескриптор окна
		HWND _hwndWindow;

		int _iID;

		//имя окна
		std::string _strWindowName;

	public:
		BaseWindow();
		virtual ~BaseWindow();
	};
}
