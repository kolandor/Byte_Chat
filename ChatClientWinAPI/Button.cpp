#include "Button.h"


namespace mns
{
	Button::Button(const HWND & parent,TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height,const int &id, bool(*ActionFunc)(const  void*))
	{
		BaseControl::_hwndWindow = CreateWindow(
			TEXT("Button"),   // указатель на зарегистрированное им€ класса
			strButtonName,  // указатель на им€ окна
			WS_CHILD | WS_VISIBLE,// стиль окна
			x,                 // горизонтальна€ позици€ окна
			y,                 // вертикальна€ позици€ окна
			width,            // ширина окна
			height,           // высота окна
			parent,       // дескриптор родительского или окна владельца
			reinterpret_cast<HMENU>(id),           // дескриптор меню или ID дочернего окна
			GetModuleHandle(NULL),      // дескриптор экземпл€ра приложени€
			nullptr         // указатель на данные создани€ окна
		);

		//проверка создани€ дескриптора
		if (!BaseControl::_hwndWindow)
		{
			throw std::exception("Can't create button");
		}

		BaseControl::_iID = id;

		BaseControl::_strWindowName = reinterpret_cast<wchar_t>(strButtonName);

		this->Action = ActionFunc;
	}

	Button::~Button()
	{
	}
}