#include "Form.h"
#include <tchar.h>


namespace mns
{
	LRESULT Form::WndProc(HWND hWnd, // дескриптор окошка
		UINT uMsg, // сообщение, посылаемое ќ—
		WPARAM wParam, // параметры
		LPARAM lParam) // сообщений, дл€ последующего обращени€
	{
		HDC hDC; // создаЄм дескриптор ориентации текста на экране
		PAINTSTRUCT ps; // структура, сод-ща€ информацию о клиентской области (размеры, цвет и тп)
		RECT rect; // стр-ра, определ€юща€ размер клиентской области
		COLORREF colorText = RGB(255, 0, 0); // задаЄм цвет текста
		switch (uMsg) {
		case WM_PAINT: // если нужно нарисовать, то:
			hDC = BeginPaint(hWnd, &ps); // инициализируем контекст устройства
			GetClientRect(hWnd, &rect); // получаем ширину и высоту области дл€ рисовани€
			SetTextColor(hDC, colorText); // устанавливаем цвет контекстного устройства
			DrawText(hDC, _T("Hello World!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // рисуем текст
			EndPaint(hWnd, &ps); // заканчиваем рисовать
			break;
		case WM_DESTROY: // если окошко закрылось, то:
			PostQuitMessage(NULL); // отправл€ем WinMain() сообщение WM_QUIT
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam); // если закрыли окошко
		}
		return NULL; // возвращаем значение

	}

	Form::Form(TCHAR * strWindowClassName, HINSTANCE hInstance, int x, int y ,int width, int heigth, int iShowWindow)
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

		BaseControl::_hwndWindow = CreateWindow(_wndClass.lpszClassName, // им€ класса
			strWindowClassName, // им€ окна (то что сверху)
			DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU, // режимы отображени€
			x, y, width, heigth,
			HWND(NULL), // дескриптор родительского окошка (у нас нет род. окон)
			NULL, // дескриптор меню (у нас его нет)
			HINSTANCE(hInstance), // .... экземпл€ра приложени€
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
}