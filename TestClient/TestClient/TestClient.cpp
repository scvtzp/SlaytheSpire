// TestClient.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
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
	// ���ٽ�. �̸����� �Լ�. 
// 	[/*ĸ���� Ȥ�� ���ټҰ���*/](/*���� Ȥ�� �Ű����� Ȥ�� ��..�������*/) 
// 	{
// 		// �Լ� ��ü. 
// 	};
// 
// 	[]()
// 	{
// 		cout << "Hello World " << endl; 
// 	}();

// 	int a = 10, b = 20; 
// 
// 	// �ܼ� ������ ������ ĸ�� ���. �װ͵� ���� ������ ���. 
// 	[a]() 
// 	{
// 		// ���� �������������� ĸ�ĸ� �����ϰ� �ִ�. �̶� �� ������ �ڵ� ���ȭ�� �Ͼ��. �� ������ �Ұ�. 
// 		a = 99; 
// 		// a ������ ������ �ٸ� ������ ĸ�ĸ� ���� �ʾұ� ������ ��� �Ұ�. 
// 		cout << b << endl; 
// 		// �� �б� ����. 
// 		cout << a << endl; 
// 	}();

// 	int a = 10, b = 20;
// 
// 	// �ܼ� ������ ������ ĸ�� ���. �װ͵� ������ ������ ���. 
// 	[a, b]()
// 	{
// 		// ���� �������������� ĸ�ĸ� �����ϰ� �ִ�. �̶� �� ������ �ڵ� ���ȭ�� �Ͼ��. �� ������ �Ұ�. 
// 		//a = 99;
// 		cout << b << endl;
// 		// �� �б� ����. 
// 		cout << a << endl;
// 	}();


// 	int a = 10, b = 20, c = 30, d = 40, e = 50;
// 
// 	// = �̿��ϸ� �ܺο� �ִ� ��� ������ ������ �������� ĸ�� �ϰڴ�. ��, ������ �Ұ��ϴ�. 
// 	[=]()
// 	{
// 		// ���� �������������� ĸ�ĸ� �����ϰ� �ִ�. �̶� �� ������ �ڵ� ���ȭ�� �Ͼ��. �� ������ �Ұ�. 
// 		//a = 99;
// 		cout << b << endl;
// 		// �� �б� ����. 
// 		cout << a << c << d << e << endl;
// 	}();

// 	int a = 10, b = 20, c = 30, d = 40, e = 50;
// 
// 	// & �̿��ϸ� �ܺο� �ִ� ��� ������ ���۷��� �������� ĸ�� �ϰڴ�. ��, ������ ����.
// 	[&]()
// 	{
// 		a = 99;
// 		b = 22; 
// 		c = 33;
// 		d = 123; 
// 		e = 908; 
// 		cout << b << endl;
// 		// �� �б� ����. 
// 		cout << a << c << d << e << endl;
// 	}();

//	int a = 10, b = 20, c = 30, d = 40, e = 50;

// 	// ���� a ������ ���۷��� �������� �ʿ�. d ������ �ܼ� ���� ����� �������� ����ϰ� �ʹ� ? 
// 	[&a, d]()
// 	{
// 		a = 99;
// 		// �� �б� ����. 
// 		cout << a << c << d << e << endl;
// 	}();


// 	float iTotal = 0; 
	// ���ٽ��� ��� ��ȯŸ���� ���� ������� �ʿ䰡 ����. �Ѿ�� �����Ϳ� ���� �ڵ����� ��ȯŸ���� �߷� �Ѵ�. 
	// ���� ����ϰ� �ʹٸ� ->�� �̿��ϸ� �ȴ�. 
// 	iTotal = [](int a, float b)->int 
// 	{
// 		return a + b; 
// 	}(10, 20.22 );
// 
// 	cout << iTotal << endl; 

	map<const char*, int> mapTest; 
	mapTest.emplace("������", 20); 
	mapTest.emplace("�ں���", 22);
	mapTest.emplace("�Ѱ�ö", 29);
	mapTest.emplace("������", 223);
	mapTest.emplace("�Դٰ� ������ ���� �����Ѥ�", 30);
	mapTest.emplace("��� �ؾ� ������ ���� �ù�.. ", 30);
// �Լ� ��ü�� Ȱ���ϴ� ���. 
// 	auto& iter_find = find_if(mapTest.begin(), mapTest.end(),CMyStringCmp("������") );
// 
// 	if (mapTest.end() == iter_find)
// 	{
// 		cout << " ����.. " << endl; 
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
		cout << " ����.. " << endl;
	}
	cout << iter_find->first << " , " << iter_find->second << endl;
    return 0;

	 //���ø� ������ ��� �Լ��� GetPane �Լ��� �ִ�. �� �Լ��� ������ ��� ���� ��ġ�� cWnd�� ���ü� �ִ�. 

}

