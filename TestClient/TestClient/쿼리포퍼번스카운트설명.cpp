#include "stdafx.h"

void main()
{
	LARGE_INTEGER BeginTime; 
	LARGE_INTEGER EndTime; 
	LARGE_INTEGER Frequency;
	float fDeltaTime = 0.f; 
	//CPU�� ���ļ��� ������ �Լ�. - CPU ����. ��, CPU�� �ʴ� ���� ���� ������ �Լ��̴�. 
	QueryPerformanceFrequency(&Frequency);
	while (true)
	{
		QueryPerformanceFrequency(&Frequency);
		// �� �Լ��� ���κ��尡 ������ �ִ� Ÿ�̸��� �������� ������ �Լ�. 
		QueryPerformanceCounter(&BeginTime);
		system("pause"); 

		QueryPerformanceCounter(&EndTime);
		
		// ���� �ڵ尡 ���ϴ� �ٴ� End - Begin�� ���� ������ �������� ���ð� �ű⿡ �ʴ� �������� �����ְ� �Ǹ� �ð��� ���� �� �ִ�. 

		fDeltaTime = float(EndTime.QuadPart - BeginTime.QuadPart) / Frequency.QuadPart;

		cout << fDeltaTime << endl; 
	}


}