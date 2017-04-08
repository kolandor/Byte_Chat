#include "Form.h"
#include "Button.h"
#include <tchar.h>
#include "TextBox.h"

namespace mns
{
	Form::Form(TCHAR * strWindowClassName, HINSTANCE hInstance, int x, int y, int width, int heigth, int iShowWindow)
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

		//проверка успешной регистрации класса окна(и собственно сама регистрация)
		if (!RegisterClassEx(&_wndClass))
		{
			throw std::exception("Window Class Initial Error");
		}

		BaseControl::_hwndWindow = CreateWindow(_wndClass.lpszClassName, // имя класса
			strWindowClassName, // имя окна (то что сверху)
			DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU, // режимы отображения
			x, y, width, heigth,
			HWND(NULL), // дескриптор родительского окна (у нас нет род. окон)
			NULL, // дескриптор меню (у нас его нет)
			HINSTANCE(hInstance), // .... экземпляра приложения
			NULL);

		if (!BaseControl::_hwndWindow)
		{
			throw std::exception("Window Cerate Error");
		}

		ShowWindow(BaseControl::_hwndWindow, iShowWindow);
		UpdateWindow(BaseControl::_hwndWindow);

		BaseControl::_strWindowName = reinterpret_cast<wchar_t>(strWindowClassName);
	}


	Form::~Form()
	{
	}

	LRESULT Form::WndProc(HWND hWnd, // дескриптор окна
		UINT uMsg, // сообщение, посылаемое ОС
		WPARAM wParam, // параметры
		LPARAM lParam) // сообщений, для последующего обращения
	{
		try
		{
			switch (uMsg)
			{
				//инициализация динамических объектов
			case WM_CREATE:
			{

				TextBox text_box_chat(hWnd, _T("Chat Window"), 10, 15, 360, 350, 1, nullptr);
				TextBox text_box_message(hWnd, _T("Message Window"), 10, 350 + 25, 300, 50, 2, nullptr);
				Button send_button(hWnd, _T("SEND"), 310, 350 + 25, 60, 50, 2, nullptr);

				return 0;
			}
			case WM_COMMAND:


				return 0;

			case WM_DESTROY:

				PostQuitMessage(NULL);

				return 0;

			default:
				//передача не обработанных сообщений далее
				return DefWindowProc(hWnd, uMsg, wParam, lParam);
			}
		}
		catch (std::exception ex)
		{

			MessageBoxA(NULL, ex.what(), NULL, MB_ICONERROR);

			PostQuitMessage(-1);
			return -1;
		}
	}
}