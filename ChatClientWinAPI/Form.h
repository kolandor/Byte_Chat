#pragma once
#include "BaseControl.h"

namespace mns
{
	class Form : public BaseControl
	{
		WNDCLASSEX _wndClass;

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	public:
		Form(TCHAR * strWindowClassName, HINSTANCE hInstance, int x, int y, int width, int heigth, int iShowWindow);
		virtual ~Form();
	};
}