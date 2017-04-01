#include "Form.h"
#include "Button.h"
#include <tchar.h>

namespace mns
{
	Form::Form(TCHAR * strWindowClassName, HINSTANCE hInstance, int x, int y, int width, int heigth, int iShowWindow)
	{
		//���������� ���������
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

		//�������� �������� ����������� ������ ����(� ���������� ���� �����������)
		if (!RegisterClassEx(&_wndClass))
		{
			throw std::exception("Window Class Initial Error");
		}

		BaseControl::_hwndWindow = CreateWindow(_wndClass.lpszClassName, // ��� ������
			strWindowClassName, // ��� ���� (�� ��� ������)
			DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU, // ������ �����������
			x, y, width, heigth,
			HWND(NULL), // ���������� ������������� ���� (� ��� ��� ���. ����)
			NULL, // ���������� ���� (� ��� ��� ���)
			HINSTANCE(hInstance), // .... ���������� ����������
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

	LRESULT Form::WndProc(HWND hWnd, // ���������� ����
		UINT uMsg, // ���������, ���������� ��
		WPARAM wParam, // ���������
		LPARAM lParam) // ���������, ��� ������������ ���������
	{
		try
		{
			switch (uMsg)
			{
				//������������� ������������ ��������
			case WM_CREATE:
			{

				Button test(hWnd, _T("Test"), 10, 10, 50, 50, 1, nullptr);

				return 0;
			}
			case WM_COMMAND:


				return 0;

			case WM_DESTROY:

				PostQuitMessage(NULL);

				return 0;

			default:
				//�������� �� ������������ ��������� �����
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