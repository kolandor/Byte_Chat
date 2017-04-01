#include "Form.h"
#include <tchar.h>


namespace mns
{
	LRESULT Form::WndProc(HWND hWnd, // ���������� ������
		UINT uMsg, // ���������, ���������� ��
		WPARAM wParam, // ���������
		LPARAM lParam) // ���������, ��� ������������ ���������
	{
		HDC hDC; // ������ ���������� ���������� ������ �� ������
		PAINTSTRUCT ps; // ���������, ���-��� ���������� � ���������� ������� (�������, ���� � ��)
		RECT rect; // ���-��, ������������ ������ ���������� �������
		COLORREF colorText = RGB(255, 0, 0); // ����� ���� ������
		switch (uMsg) {
		case WM_PAINT: // ���� ����� ����������, ��:
			hDC = BeginPaint(hWnd, &ps); // �������������� �������� ����������
			GetClientRect(hWnd, &rect); // �������� ������ � ������ ������� ��� ���������
			SetTextColor(hDC, colorText); // ������������� ���� ������������ ����������
			DrawText(hDC, _T("Hello World!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); // ������ �����
			EndPaint(hWnd, &ps); // ����������� ��������
			break;
		case WM_DESTROY: // ���� ������ ���������, ��:
			PostQuitMessage(NULL); // ���������� WinMain() ��������� WM_QUIT
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam); // ���� ������� ������
		}
		return NULL; // ���������� ��������

	}

	Form::Form(TCHAR * strWindowClassName, HINSTANCE hInstance, int x, int y ,int width, int heigth, int iShowWindow)
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
			HWND(NULL), // ���������� ������������� ������ (� ��� ��� ���. ����)
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
}