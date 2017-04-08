#pragma once
#include "BaseControl.h"

class TextBox : public mns::BaseControl
{
	//����� ��������� �������
	bool(*Action)(const void*);

public:

	//���������� ���������� ���������� �������� ��� TextBox
	TextBox(const HWND & parent, TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height, const int &id, bool(*ActionFunc)(const  void*));
	virtual ~TextBox();
};

