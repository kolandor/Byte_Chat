#pragma once
#include <string>

namespace mns
{
	class Convert
	{
	public:
		Convert();
		virtual ~Convert();

		static std::string WstrToStr(const std::wstring &);//�������������� � wstr � str
		static int WstrToStr(std::string&, const std::wstring &, const int & ConvertCount = -1);//�������������� wstr � str � ��������� ����� ��������������� ��������

		static std::wstring StrToWStr(const std::string &);//�������������� � str � wstr
		static int StrToWstr(std::wstring&, const std::string &);//��������������  str � wstr � ��������� ����� ��������������� �������� ������ ���-�� ��������
	};
}