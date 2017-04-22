#include "Form.h"
#include "Button.h"
#include <tchar.h>
#include "TextBox.h"
#include <memory>
#include <Winsock.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

namespace mns
{

	//Вектор элементов формы
	std::vector<BaseControl*> controls;
	//структура инициализации сокетов
	WSADATA verSoc = { 0 };
	//сокет клиента
	SOCKET Socket = NULL;

	//поток прослушивания
	HANDLE hThreadListener = NULL;
	//функция потока прослушивания
	DWORD WINAPI ThreadFuncListener(LPVOID);

	std::string messagesData;

	//Нажатие подключения
	bool ClickConnect(WPARAM, LPARAM);

	//Нажатие отправки
	bool ClickSend(WPARAM, LPARAM);

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
		//очистка ресурсов
		WSACleanup();
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
				controls.push_back(new TextBox(hWnd, _T("127.0.0.1"), 10, 5, 115, 20, 1, WS_VISIBLE | WS_CHILD | WS_BORDER));
				controls.push_back(new TextBox(hWnd, _T("1488"), 130, 5, 40, 20, 2, WS_VISIBLE | WS_CHILD | WS_BORDER));
				controls.push_back(new TextBox(hWnd, _T("Test"), 175, 5, 90, 20, 3, WS_VISIBLE | WS_CHILD | WS_BORDER));
				controls.push_back(new Button(hWnd, _T("CONNECT"), 270, 5, 95, 20, 4));
				controls.push_back(new TextBox(hWnd, _T("Chat Window"), 10, 30, 360, 335, 5));
				controls.push_back(new TextBox(hWnd, _T("Message Window"), 10, 350 + 25, 300, 50, 6));
				controls.push_back(new Button(hWnd, _T("SEND"), 310, 350 + 25, 60, 50, 7));

				controls[3]->SetEvent(ClickConnect, WM_COMMAND);
				controls[6]->SetEvent(ClickSend, WM_COMMAND);

				return 0;
			}
			case WM_COMMAND:

				for (int i = 0; i < controls.size(); i++)
				{
					if (controls[i]->GatID() == LOWORD(wParam))
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

	bool ClickSend(WPARAM wParam, LPARAM lParam)
	{
		if (Socket == NULL)
			return false;

		UINT lenOfMessageText = GetWindowTextLength(controls[5]->GetHandler());

		if (lenOfMessageText < 1)
			return false;

		std::string messageText;
		messageText.resize(lenOfMessageText+1);

		GetWindowTextA(controls[5]->GetHandler(), &messageText[0], messageText.size());

		send(Socket, &messageText[0], messageText.size(), NULL);
	}

	bool ClickConnect(WPARAM wParam, LPARAM lParam)
	{
		try
		{
			if (Socket != NULL)
			{
				closesocket(Socket);
				Socket = NULL;
				WSACleanup();
			}

			if (hThreadListener != NULL)
			{
				TerminateThread(hThreadListener, -1);
				CloseHandle(hThreadListener);
				hThreadListener = NULL;
			}

			//Инициализания версии сокетов
			if (WSAStartup(0x0202, &verSoc))
			{
				throw(std::exception("Can't initialize socket version: ", WSAGetLastError()));
			}

			Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
			if (Socket == SOCKET_ERROR)
			{
				WSACleanup();
				throw(std::exception("Can't create socket: ", GetLastError()));
			}

			//взятие IP
			std::string ip;
			ip.resize(16);
			GetWindowTextA(controls[0]->GetHandler(), &ip[0], 16);

			if (!strlen(&ip[0]))
			{
				throw(std::exception("Incorrect ip"));
			}

			//взятие порта
			std::string port;
			port.resize(5);
			GetWindowTextA(controls[1]->GetHandler(), &port[0], 5);

			if (!strlen(&port[0]))
			{
				throw(std::exception("Incorrect port"));
			}

			struct sockaddr_in 	addrClient = { 0 };
			addrClient.sin_addr.s_addr = inet_addr(&ip[0]);

			//если адрес не был инициализирован
			if (INADDR_NONE == addrClient.sin_addr.s_addr)
			{
				//пробуем взять его из имени хоста
				struct hostent *hostName = gethostbyname(&ip[0]);

				if (!hostName)
				{
					closesocket(Socket);
					throw(std::exception("Can't get host address"));
				}

				addrClient.sin_addr = *(struct in_addr *) hostName->h_addr_list[0];

			}

			addrClient.sin_family = AF_INET;
			addrClient.sin_port = ::htons(atoi(port.c_str()));

			if (SOCKET_ERROR == connect(Socket,
				(struct sockaddr*)&addrClient,
				sizeof(addrClient)))
			{
				closesocket(Socket);
				throw(std::exception("Can't connect to server"));
			}

			//запуск потока прослушивания
			hThreadListener = CreateThread(NULL,
				NULL,
				ThreadFuncListener,
				reinterpret_cast<LPVOID>(Socket),
				NULL,
				NULL);

			if (!hThreadListener)
			{
				throw(std::exception("Can't create thread listener"));
			}

			//отправка логина
			//взятие ника
			std::string nic;
			nic.resize(11);
			GetWindowTextA(controls[2]->GetHandler(), &nic[0], 11);

			if (!strlen(&nic[0]))
			{
				throw(std::exception("Incorrect nic"));
			}

			send(Socket,
				nic.c_str(),
				strlen(nic.c_str()),
				NULL);
		}
		catch (std::exception ex)
		{
			if (Socket != NULL)
			{
				closesocket(Socket);
				Socket = NULL;
			}

			if (hThreadListener != NULL)
			{
				TerminateThread(hThreadListener, -1);
				CloseHandle(hThreadListener);
				hThreadListener = NULL;
			}

			MessageBoxA(NULL, ex.what(), NULL, MB_ICONERROR);
			return false;
		}
		return true;
	}


	//поток чтения
	DWORD WINAPI ThreadFuncListener(LPVOID _param)
	{
		const int SIZE_BUF = 1024;

		SOCKET Socket = reinterpret_cast<SOCKET>(_param);

		char buf_recv[SIZE_BUF] = { 0 };
		int size_recv;
		do
		{

			memset(buf_recv, 0, sizeof(buf_recv));
			size_recv = ::recv(Socket,
				buf_recv,
				sizeof(buf_recv) - 1,
				0);

			if (size_recv && size_recv != SOCKET_ERROR)
			{
				messagesData += "\r\n";
				messagesData += buf_recv;
				SetWindowTextA(controls[4]->GetHandler(), messagesData.c_str());
			}
		} while (size_recv && size_recv != SOCKET_ERROR);

		return 0;
	}
}