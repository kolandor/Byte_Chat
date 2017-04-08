#pragma once
#include <string>

namespace mns
{
	class Convert
	{
	public:
		Convert();
		virtual ~Convert();

		static std::string WstrToStr(const std::wstring &);//преобразование в wstr в str
		static int WstrToStr(std::string&, const std::wstring &, const int & ConvertCount = -1);//преобразование wstr в str с возвратом числа преобразованных символов

		static std::wstring StrToWStr(const std::string &);//преобразование в str в wstr
		static int StrToWstr(std::wstring&, const std::string &);//преобразование  str в wstr с возвратом числа преобразованных символов опредю кол-ва символов
	};
}