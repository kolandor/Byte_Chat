#include "Button.h"


namespace mns
{
	Button::Button(const HWND & parent,TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height,const int &id, bool(*ActionFunc)(const  void*))
	{
		BaseControl::_hwndWindow = CreateWindow(
			TEXT("Button"),   // ��������� �� ������������������ ��� ������
			strButtonName,  // ��������� �� ��� ����
			WS_CHILD | WS_VISIBLE,// ����� ����
			x,                 // �������������� ������� ����
			y,                 // ������������ ������� ����
			width,            // ������ ����
			height,           // ������ ����
			parent,       // ���������� ������������� ��� ���� ���������
			reinterpret_cast<HMENU>(id),           // ���������� ���� ��� ID ��������� ����
			GetModuleHandle(NULL),      // ���������� ���������� ����������
			nullptr         // ��������� �� ������ �������� ����
		);

		//�������� �������� �����������
		if (!BaseControl::_hwndWindow)
		{
			throw std::exception("Can't create button");
		}

		BaseControl::_iID = id;

		BaseControl::_strWindowName = reinterpret_cast<wchar_t>(strButtonName);

		this->Action = ActionFunc;
	}

	Button::~Button()
	{
	}
}