#include "BaseWindow.h"


namespace mns
{
	BaseWindow::BaseWindow(UINT &style, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM), TCHAR * MenuName, TCHAR * ClassName, HICON &icon, )
	{
		TCHAR * strWindowClassName = _T("ChatWinAPI"); //имя будущего класса окна

		WNDCLASSEX wndClass;
		//заполнение структуры
		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = style;
		wndClass.lpfnWndProc = WndProc;
		wndClass.lpszMenuName = MenuName;
		wndClass.lpszClassName = ClassName;
		wndClass.cbWndExtra = NULL;
		wndClass.cbClsExtra = NULL;
		wndClass.hIcon = icon;
		wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.hInstance = hInstance;
	}


	BaseWindow::~BaseWindow()
	{
	}
}