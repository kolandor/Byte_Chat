#include <windows.h>
#include <tchar.h>
#include <exception>

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

		WNDCLASSEX wndClass;
		//���������� ���������
		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = CS_HREDRAW | CS_VREDRAW;
		wndClass.lpfnWndProc = WndProc;
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = strWindowClassName;
		wndClass.cbWndExtra = NULL;
		wndClass.cbClsExtra = NULL;
		wndClass.hIcon = LoadIcon(nullptr, IDI_WINLOGO);
		wndClass.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);
		wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wndClass.hbrBackground = reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
		wndClass.hInstance = hInstance;

		//�������� �������� ����������� ������ ����(� ���������� ���� �����������)
		if (!RegisterClassEx(&wndClass))
		{
			throw std::exception("Window Class Initial Error");
		}

		HWND hChatWindow = nullptr;

		hChatWindow = CreateWindow(
			wndClass.lpszClassName,
			_T("Byte Chat"),
			WS_OVERLAPPEDWINDOW | WS_VSCROLL, // ������ ����������� ������
			CW_USEDEFAULT, // ��������� ���� �� ��� � (�� ���������)
			NULL, // ������� ���� �� ��� � (��� ������ � �, �� ������ �� �����)
			CW_USEDEFAULT, // ������ ����� (�� ���������)
			NULL, // ������ ���� (��� ������ � ������, �� ������ �� �����)
			HWND(NULL), // ���������� ������������� ������ (� ��� ��� ���. ����)
			NULL, // ���������� ���� (� ��� ��� ���)
			HINSTANCE(hInstance), // .... ���������� ����������
			NULL);

		if (!hChatWindow)
		{
			throw std::exception("Window Cerate Error");
		}

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