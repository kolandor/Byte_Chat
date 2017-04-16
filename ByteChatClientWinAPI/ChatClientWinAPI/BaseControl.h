#pragma once
#include <string>
#include <windows.h>
#include <vector>

namespace mns
{
	class BaseControl
	{
	public:

		typedef bool(*Action)(WPARAM wParam, LPARAM lParam);

		struct Event
		{
			//метод обработки события
			Action act;

			UINT uMsg; // сообщение, посылаемое ОС
		};

	protected:
		//дескриптор окна
		HWND _hwndWindow;

		//id окна
		int _iID;

		//имя окна
		std::string _strWindowName;

		std::vector<Event> events;

		BaseControl()
		{
			
		}

		virtual ~BaseControl()
		{
			
		}

	public:

		inline HWND GetHandler() const
		{
			return _hwndWindow;
		}

		inline int GatID() const
		{
			return _iID;
		}

		inline std::string GetName() const
		{
			return _strWindowName;
		}

		inline void SetEvent(Action action, UINT message)
		{
			events.push_back(Event{ action, message });
		}

		inline void EventStart(UINT message, WPARAM wParam, LPARAM lParam)
		{
			for(size_t i = 0; i < events.size(); i++)
			{
				if (events[i].uMsg == message)
					events[i].act(wParam, lParam);
			}
		}
	};
}
