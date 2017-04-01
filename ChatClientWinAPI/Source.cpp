#include <windows.h>
#include <tchar.h>
#include <exception>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
	HINSTANCE hInstance,//дескриптор текущего приложени€(окна)
	HINSTANCE hPrevInstance,//дескриптор предыдущего окна(вызвавшего данное окно)
	LPSTR lpCmdLine,//указатель на строку содержащую команды (в случаи запуска из под консоли)
	int nCmdShow)//состо€ние окна, (состо€ние в котором приложение будет находитс€ в момент открыти€))
{
	try
	{
		TCHAR * strWindowClassName = _T("ChatWinAPI"); //им€ будущего класса окна

		MSG msg;

		WNDCLASSEX wndClass;
		//заполнение структуры
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

		//проверка успешной регистрации класса окна(и собственно сама регистраци€)
		if (!RegisterClassEx(&wndClass))
		{
			throw std::exception("Window Class Initial Error");
		}

		HWND hChatWindow = nullptr;

		hChatWindow = CreateWindow(
			wndClass.lpszClassName,
			_T("Byte Chat"),
			WS_OVERLAPPEDWINDOW | WS_VSCROLL, // режимы отображени€ окошка
			CW_USEDEFAULT, // положение окна по оси х (по умолчанию)
			NULL, // позици€ окна по оси у (раз дефолт в х, то писать не нужно)
			CW_USEDEFAULT, // ширина окона (по умолчанию)
			NULL, // высота окна (раз дефолт в ширине, то писать не нужно)
			HWND(NULL), // дескриптор родительского окошка (у нас нет род. окон)
			NULL, // дескриптор меню (у нас его нет)
			HINSTANCE(hInstance), // .... экземпл€ра приложени€
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