#pragma once
#include "WrapHandler.h"


inline void SetConsoleCollor(const int &color)
{
	static mns::WrapHandler hColor = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hColor, color);
}