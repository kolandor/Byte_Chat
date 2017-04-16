#pragma once
#include "BaseControl.h"

class TextBox : public mns::BaseControl
{
	//����� ��������� �������
	bool(*Action)(const void*);

public:

	//���������� ���������� ���������� �������� ��� TextBox
	TextBox(const HWND & parent, TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height,
		const int &id, const DWORD params = WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL | WS_BORDER);
	virtual ~TextBox();
};

