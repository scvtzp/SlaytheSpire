// TestClient.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <map>
#include <algorithm>

class CMyStringCmp
{
public:
	CMyStringCmp() {}
	CMyStringCmp(const char* pName)
		:m_pString(pName)
	{}
	~CMyStringCmp() {}; 

public:
	template<typename T > 
	bool operator()(T& rPair)
	{
		if (!strcmp(m_pString, rPair.first))
			return true; 

		return false; 
	}

private:
	const char* m_pString; 
};
int main()
{
	// 람다식. 이름없는 함수. 
// 	[/*캡쳐절 혹은 람다소개식*/](/*인자 혹은 매개변수 혹은 ㅍ..ㅏ라미터*/) 
// 	{
// 		// 함수 몸체. 
// 	};
// 
// 	[]()
// 	{
// 		cout << "Hello World " << endl; 
// 	}();

// 	int a = 10, b = 20; 
// 
// 	// 단순 값복사 형식의 캡쳐 방법. 그것도 단일 변수일 경우. 
// 	[a]() 
// 	{
// 		// 현재 값복사형식으로 캡쳐를 진행하고 있다. 이때 그 변수는 자동 상수화가 일어난다. 즉 값변경 불가. 
// 		a = 99; 
// 		// a 변수를 제외한 다른 변수는 캡쳐를 하지 않았기 때문에 사용 불가. 
// 		cout << b << endl; 
// 		// 값 읽기 가능. 
// 		cout << a << endl; 
// 	}();

// 	int a = 10, b = 20;
// 
// 	// 단순 값복사 형식의 캡쳐 방법. 그것도 복수일 변수일 경우. 
// 	[a, b]()
// 	{
// 		// 현재 값복사형식으로 캡쳐를 진행하고 있다. 이때 그 변수는 자동 상수화가 일어난다. 즉 값변경 불가. 
// 		//a = 99;
// 		cout << b << endl;
// 		// 값 읽기 가능. 
// 		cout << a << endl;
// 	}();


// 	int a = 10, b = 20, c = 30, d = 40, e = 50;
// 
// 	// = 이용하면 외부에 있는 모든 변수를 값복사 형식으로 캡쳐 하겠다. 즉, 값변경 불가하다. 
// 	[=]()
// 	{
// 		// 현재 값복사형식으로 캡쳐를 진행하고 있다. 이때 그 변수는 자동 상수화가 일어난다. 즉 값변경 불가. 
// 		//a = 99;
// 		cout << b << endl;
// 		// 값 읽기 가능. 
// 		cout << a << c << d << e << endl;
// 	}();

// 	int a = 10, b = 20, c = 30, d = 40, e = 50;
// 
// 	// & 이용하면 외부에 있는 모든 변수를 레퍼런스 형식으로 캡쳐 하겠다. 즉, 값변경 가능.
// 	[&]()
// 	{
// 		a = 99;
// 		b = 22; 
// 		c = 33;
// 		d = 123; 
// 		e = 908; 
// 		cout << b << endl;
// 		// 값 읽기 가능. 
// 		cout << a << c << d << e << endl;
// 	}();

//	int a = 10, b = 20, c = 30, d = 40, e = 50;

// 	// 만약 a 변수는 레퍼런스 형식으로 필요. d 변수는 단순 값을 얻오은 형식으로 사용하고 싶다 ? 
// 	[&a, d]()
// 	{
// 		a = 99;
// 		// 값 읽기 가능. 
// 		cout << a << c << d << e << endl;
// 	}();


// 	float iTotal = 0; 
	// 람다식의 경우 반환타입을 굳이 명시해줄 필요가 없다. 넘어가는 데이터에 따라 자동으로 반환타입을 추론 한다. 
	// 만약 명시하고 싶다면 ->를 이용하면 된다. 
// 	iTotal = [](int a, float b)->int 
// 	{
// 		return a + b; 
// 	}(10, 20.22 );
// 
// 	cout << iTotal << endl; 

	map<const char*, int> mapTest; 
	mapTest.emplace("가나다", 20); 
	mapTest.emplace("박병건", 22);
	mapTest.emplace("한경철", 29);
	mapTest.emplace("지각자", 223);
	mapTest.emplace("게다가 연락도 없이 개새켜ㅑ", 30);
	mapTest.emplace("어떻게 해야 연락도 없지 시발.. ", 30);
// 함수 객체를 활용하는 방법. 
// 	auto& iter_find = find_if(mapTest.begin(), mapTest.end(),CMyStringCmp("지각자") );
// 
// 	if (mapTest.end() == iter_find)
// 	{
// 		cout << " 실패.. " << endl; 
// 	}
// 	cout << iter_find->first << " , " << iter_find->second << endl;

	char* pName = new char; 
	cin >> pName; 

	auto& iter_find = find_if(mapTest.begin(), mapTest.end(), [=](auto& rPair) 
	{
		if (!strcmp(rPair.first, pName))
			return true; 
		return false;
	});

	if (mapTest.end() == iter_find)
	{
		cout << " 실패.. " << endl;
	}
	cout << iter_find->first << " , " << iter_find->second << endl;
    return 0;

	 //스플릿 윈도우 멤버 함수에 GetPane 함수가 있다. 이 함수는 지정한 행과 열에 위치한 cWnd를 얻어올수 있다. 

}

