#include <windows.h>
#include <tchar.h>
#include <exception>
#include "Form.h"

int WINAPI WinMain(
	HINSTANCE hInstance,//���������� �������� ����������(����)
	HINSTANCE hPrevInstance,//���������� ����������� ����(���������� ������ ����)
	LPSTR lpCmdLine,//��������� �� ������ ���������� ������� (� ������ ������� �� ��� �������)
	int nCmdShow)//��������� ����, (��������� � ������� ���������� ����� ��������� � ������ ��������))
{
	try
	{
		TCHAR * strWindowClassName = _T("ChatWinAPI"); //��� �������� ������ ����

		MSG msg;

		mns::Form ChatWindow(_T("ByteChat"), hInstance, 100, 100, 400, 500, nCmdShow);

		BOOL bRet;

		while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
		{
			if (bRet == -1)//��������� ����������� ������
			{
				throw std::exception("Critical exception in Callback Function");
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		return msg.wParam;
	}
	catch (std::exception ex)
	{
		MessageBoxA(NULL, ex.what(), "Initial Error", MB_OK);
		return -1;
	}
	catch (...)
	{
		MessageBoxA(NULL, "Undefined Exception", "Critical ERROR", MB_OK);
		return -1;
	}
}