#pragma once
#include "BaseWindow.h"

namespace mns
{
	class Form : public BaseWindow
	{
		WNDCLASSEX _wndClass;
	public:
		Form(TCHAR * strWindowClassName, HINSTANCE hInstance, int x, int y, int width, int heigth, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM));
		virtual ~Form();
	};
}