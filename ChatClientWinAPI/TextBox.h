#pragma once
#include "BaseControl.h"

class TextBox : public mns::BaseControl
{
	//метод обработки события
	bool(*Action)(const void*);

public:

	//желательна реализация визуальных настроек для TextBox
	TextBox(const HWND & parent, TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height, const int &id, bool(*ActionFunc)(const  void*));
	virtual ~TextBox();
};

