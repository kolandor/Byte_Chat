#pragma once
#include "BaseControl.h"
#include "Form.h"

namespace mns
{
	class Button : BaseControl
	{
		//метод обработки события
		bool(*Action)(const void*);

	public:
		Button(const HWND & parent, TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height, const int &id, bool(*ActionFunc)(const  void*));
		virtual ~Button();
	};
}