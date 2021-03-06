#include "TextBox.h"



TextBox::TextBox(const HWND & parent, TCHAR * strButtonName, const int &x, const int &y, const int &width, const int &height,
		const int &id, const DWORD params)
{
	BaseControl::_hwndWindow = CreateWindow(
		TEXT("Edit"),   // ��������� �� ������������������ ��� ������
		strButtonName,  // ��������� �� ��� ����
		params,// ����� ����
		x,                 // �������������� ������� ����
		y,                 // ������������ ������� ����
		width,            // ������ ����
		height,           // ������ ����
		parent,       // ���������� ������������� ��� ���� ���������
		reinterpret_cast<HMENU>(id),           // ���������� ���� ��� ID ��������� ����
		GetModuleHandle(NULL),      // ���������� ���������� ����������
		nullptr         // ��������� �� ������ �������� ����
	);

	//�������� �������� �����������
	if (!BaseControl::_hwndWindow)
	{
		throw std::exception("Can't create button");
	}

	BaseControl::_iID = id;

	BaseControl::_strWindowName = reinterpret_cast<wchar_t>(strButtonName);
}


TextBox::~TextBox()
{
}
