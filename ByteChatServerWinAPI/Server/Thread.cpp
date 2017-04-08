#include "Thread.h"
#include "MyExce.h"

namespace mns
{
	DWORD WINAPI ThreadFunction(LPVOID lpParameter)//функция потока
	{
		//взятие из переданного объекта парметра отработающего в потоке 
		IThreadParameter *FunctionalObj = reinterpret_cast<Thread*>(lpParameter)->ptrThreadObj;
		
		FunctionalObj->RunThreadFunction();//метод потока(параметр работающий в потоке)
										   
										   //////////////////////////////////Изменение структуры, поток удаляет параметр при выходе
										   /////////////////////////////////Это делает параметр независимым
		delete FunctionalObj;
		return 0;
	}

	Thread::Thread(IThreadParameter * param) : ptrThreadObj(param), whThreadHandl(new WrapHandler())
	{
	}

	Thread::~Thread(void)
	{
	}

	void Thread::Run(IThreadParameter *param)
	{//запуск потока

		if(&this->ptrThreadObj != &param && param)//проверка самокопирования и нул указателя
			this->ptrThreadObj = param;
		
		if (!this->ptrThreadObj)//прооверка наличия параметра
			throw(MyExce("Thread parameter is empty!"));

		DWORD dwExitThreadCode = 0;
		GetExitCodeThread(*(this->whThreadHandl), &dwExitThreadCode);
		if (dwExitThreadCode == STILL_ACTIVE)//проверка потока на работу потока
			throw(MyExce("ThreadHandle still active!"));

		//запуск потока
		this->whThreadHandl.reset(new WrapHandler(CreateThread(0, 0, ThreadFunction, this, 0, 0)));
	}

	void Thread::Wait(const DWORD & WaitingTime)
	{//ожидание потока
		if (WaitForSingleObject(*(this->whThreadHandl), WaitingTime) != WAIT_OBJECT_0)//проверка ошибок и ожидание
			throw(MyExce("Thread waiting error", GetLastError()));

		DWORD dwExitThreadCode = 0;
		if (!GetExitCodeThread(*(this->whThreadHandl), &dwExitThreadCode))//кода с котрым поток завершил работу
			throw(MyExce("Thread working error", dwExitThreadCode));
		else
		{
			if (dwExitThreadCode == STILL_ACTIVE)//поток еще в работе
				throw(MyExce("Thread Still active", dwExitThreadCode));
		}
	}

	void Thread::Close()
	{
		if (*(this->whThreadHandl))//проверка наличия дескриптора
			if (!CloseHandle(*(this->whThreadHandl)))//попытка закрытия
				throw(MyExce("Thread closing error", GetLastError()));
	}
}