#pragma once
#include "BaseControl.h"

namespace mns
{
	class Form : public BaseControl
	{
		WNDCLASSEX _wndClass;

		static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

		//TO DO:
		//�������� ��������� controls ��� ���������� ��������� �����
		//� ���������� �����������
		//static std::vector<std::unique_ptr<BaseControl>> controls;

	public:
		Form(TCHAR *strWindowClassName, HINSTANCE hInstance, int x, int y, int width, int heigth, int iShowWindow);
		virtual ~Form();

	};
}