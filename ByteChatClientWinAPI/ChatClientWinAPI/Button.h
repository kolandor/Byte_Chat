#pragma once
#include "BaseControl.h"
#include "Form.h"

namespace mns
{
	class Button : public BaseControl
	{

	public:
		Button(const HWND & parent, TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height, const int &id);
		virtual ~Button();
	};
}