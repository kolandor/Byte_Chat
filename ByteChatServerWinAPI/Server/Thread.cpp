#include "Thread.h"
#include "MyExce.h"

namespace mns
{
	DWORD WINAPI ThreadFunction(LPVOID lpParameter)//������� ������
	{
		//������ �� ����������� ������� �������� ������������� � ������ 
		IThreadParameter *FunctionalObj = reinterpret_cast<Thread*>(lpParameter)->ptrThreadObj;
		
		FunctionalObj->RunThreadFunction();//����� ������(�������� ���������� � ������)
										   
										   //////////////////////////////////��������� ���������, ����� ������� �������� ��� ������
										   /////////////////////////////////��� ������ �������� �����������
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
	{//������ ������

		if(&this->ptrThreadObj != &param && param)//�������� ��������������� � ��� ���������
			this->ptrThreadObj = param;
		
		if (!this->ptrThreadObj)//��������� ������� ���������
			throw(MyExce("Thread parameter is empty!"));

		DWORD dwExitThreadCode = 0;
		GetExitCodeThread(*(this->whThreadHandl), &dwExitThreadCode);
		if (dwExitThreadCode == STILL_ACTIVE)//�������� ������ �� ������ ������
			throw(MyExce("ThreadHandle still active!"));

		//������ ������
		this->whThreadHandl.reset(new WrapHandler(CreateThread(0, 0, ThreadFunction, this, 0, 0)));
	}

	void Thread::Wait(const DWORD & WaitingTime)
	{//�������� ������
		if (WaitForSingleObject(*(this->whThreadHandl), WaitingTime) != WAIT_OBJECT_0)//�������� ������ � ��������
			throw(MyExce("Thread waiting error", GetLastError()));

		DWORD dwExitThreadCode = 0;
		if (!GetExitCodeThread(*(this->whThreadHandl), &dwExitThreadCode))//���� � ������ ����� �������� ������
			throw(MyExce("Thread working error", dwExitThreadCode));
		else
		{
			if (dwExitThreadCode == STILL_ACTIVE)//����� ��� � ������
				throw(MyExce("Thread Still active", dwExitThreadCode));
		}
	}

	void Thread::Close()
	{
		if (*(this->whThreadHandl))//�������� ������� �����������
			if (!CloseHandle(*(this->whThreadHandl)))//������� ��������
				throw(MyExce("Thread closing error", GetLastError()));
	}
}