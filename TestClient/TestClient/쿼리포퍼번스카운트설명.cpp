#include "stdafx.h"

void main()
{
	LARGE_INTEGER BeginTime; 
	LARGE_INTEGER EndTime; 
	LARGE_INTEGER Frequency;
	float fDeltaTime = 0.f; 
	//CPU의 주파수를 얻어오는 함수. - CPU 진동. 즉, CPU의 초당 진동 수를 얻어오는 함수이다. 
	QueryPerformanceFrequency(&Frequency);
	while (true)
	{
		QueryPerformanceFrequency(&Frequency);
		// 이 함수는 메인보드가 가지고 있는 타이머의 누적값을 얻어오는 함수. 
		QueryPerformanceCounter(&BeginTime);
		system("pause"); 

		QueryPerformanceCounter(&EndTime);
		
		// 밑의 코드가 뜻하는 바는 End - Begin은 현재 진동한 진동수가 나올것 거기에 초당 진동수를 나눠주게 되면 시간을 구할 수 있다. 

		fDeltaTime = float(EndTime.QuadPart - BeginTime.QuadPart) / Frequency.QuadPart;

		cout << fDeltaTime << endl; 
	}


}