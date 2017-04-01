#include "Form.h"


namespace mns
{
	Form::Form(TCHAR * strWindowClassName, HINSTANCE hInstance, int x, int y ,int width, int heigth, LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM))
	{
		//заполнение структуры
		_wndClass.cbSize = sizeof(_wndClass);
		_wndClass.style = CS_HREDRAW | CS_VREDRAW;
		_wndClass.lpfnWndProc = WndProc;
		_wndClass.lpszMenuName = nullptr;
		_wndClass.lpszClassName = strWindowClassName;
		_wndClass.cbWndExtra = NULL;
		_wndClass.cbClsExtra = NULL;
		_wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		_wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
		_wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		_wndClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		_wndClass.hInstance = hInstance;

		//проверка успешной регистрации класса окна(и собственно сама регистраци€)
		if (!RegisterClassEx(&_wndClass))
		{
			throw std::exception("Window Class Initial Error");
		}

		BaseWindow::_hwndWindow = CreateWindow(_wndClass.lpszClassName, // им€ класса
			strWindowClassName, // им€ окна (то что сверху)
			DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU, // режимы отображени€
			x, y, width, heigth,
			HWND(NULL), // дескриптор родительского окошка (у нас нет род. окон)
			NULL, // дескриптор меню (у нас его нет)
			HINSTANCE(hInstance), // .... экземпл€ра приложени€
			NULL);

		if (!BaseWindow::_hwndWindow)
		{
			throw std::exception("Window Cerate Error");
		}

		BaseWindow::_strWindowName = reinterpret_cast<wchar_t>(strWindowClassName);
	}


	Form::~Form()
	{
	}
}