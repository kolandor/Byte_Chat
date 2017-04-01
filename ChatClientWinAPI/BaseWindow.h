#pragma once
#include <string>
#include <windows.h>

namespace mns
{
	class BaseWindow
	{
	protected:
		//���������� ����
		HWND _hwndWindow;

		//id ����
		int _iID;

		//��� ����
		std::string _strWindowName;

		BaseWindow()
		{
			
		}

		virtual ~BaseWindow()
		{
			
		}

	public:
		HWND GetHandler()
		{
			return _hwndWindow;
		}

		int GatID()
		{
			return _iID;
		}

		std::string GetName()
		{
			return _strWindowName;
		}
	};
}
