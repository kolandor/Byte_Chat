#include <windows.h>
#include <tchar.h>
#include <exception>
#include "Form.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,//дескриптор текущего приложения(окна)
	HINSTANCE hPrevInstance,//дескриптор предыдущего окна(вызвавшего данное окно)
	LPSTR lpCmdLine,//указатель на строку содержащую команды (в случаи запуска из под консоли)
	int nCmdShow)//состояние окна, (состояние в котором приложение будет находится в момент открытия))
{
	try
	{
		TCHAR * strWindowClassName = _T("ChatWinAPI"); //имя будущего класса окна

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