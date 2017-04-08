#pragma once
#include <windows.h>

namespace mns
{
	class IThreadParameter//абстрактный класс для передачи в поток
	{
	public:
		IThreadParameter() {};
		virtual ~IThreadParameter() {};

		virtual DWORD RunThreadFunction(void) = 0;//функция потока
	};
}