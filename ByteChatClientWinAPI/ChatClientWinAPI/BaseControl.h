#pragma once
#include <string>
#include <windows.h>

namespace mns
{
	class BaseControl
	{
	protected:
		//���������� ����
		HWND _hwndWindow;

		//id ����
		int _iID;

		//��� ����
		std::string _strWindowName;

		BaseControl()
		{
			
		}

		virtual ~BaseControl()
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
