#include <windows.h>
#include <tchar.h>
#include <exception>
#include "Form.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

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

		mns::Form ChatWindow(_T("ByteChat"), hInstance, 0,0, 400, 400, WndProc);

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