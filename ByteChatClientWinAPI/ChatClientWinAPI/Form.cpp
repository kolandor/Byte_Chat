#include "Form.h"
#include "Button.h"
#include <tchar.h>
#include "TextBox.h"
#include <memory>

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

	std::vector<BaseControl*> controls;

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
				controls.push_back(new TextBox(hWnd, _T("192.168.123.123"), 10, 5, 115, 20, 1, WS_VISIBLE | WS_CHILD | WS_BORDER));
				controls.push_back(new TextBox(hWnd, _T("port"), 130, 5, 40, 20, 2, WS_VISIBLE | WS_CHILD | WS_BORDER));
				controls.push_back(new TextBox(hWnd, _T("UserName"), 175, 5, 90, 20, 3, WS_VISIBLE | WS_CHILD | WS_BORDER));
				controls.push_back(new Button(hWnd, _T("CONNECT"), 270, 5, 95, 20, 4));
				controls.push_back(new TextBox(hWnd, _T("Chat Window"), 10, 30, 360, 335, 5));
				controls.push_back(new TextBox(hWnd, _T("Message Window"), 10, 350 + 25, 300, 50, 6));
				controls.push_back(new Button(hWnd, _T("SEND"), 310, 350 + 25, 60, 50, 7));

				return 0;
			}
			case WM_COMMAND:

				for(int i = 0; i < controls.size(); i++)
				{
					if(controls[i]->GatID() == LOWORD(wParam))
					{
						controls[i]->EventStart(uMsg, wParam, lParam);
					}
				}

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

	const int SIZE_IP = 20;
	const int SIZE_BUF = 1024;
	const int LOGIN = 10;

	//поток вывода сообщения
	DWORD WINAPI ThreadMessage(LPVOID _param)
	{
		MessageBoxA(NULL, (char*)_param, "Anonym message", MB_OK);

		return 0;
	}

	//поток чтения
	DWORD WINAPI Thread(LPVOID _param)
	{

		SOCKET Socket = (SOCKET)_param;

		char buf_recv[SIZE_BUF];
		int size_recv;
		char Message[SIZE_BUF] = { 0 };
		do
		{

			memset(buf_recv, 0, sizeof(buf_recv));
			size_recv = ::recv(Socket,
				buf_recv,
				sizeof(buf_recv) - 1,
				0);

			if (size_recv && size_recv != SOCKET_ERROR)
			{
				memset(Message, 0, sizeof(Message));

				memcpy(Message, buf_recv, SIZE_BUF);
				::CreateThread(NULL,
					NULL,
					ThreadMessage,
					(LPVOID)&Message,
					NULL,
					NULL);
			}
		} while (size_recv && size_recv != SOCKET_ERROR);

		return 0;
	}
}