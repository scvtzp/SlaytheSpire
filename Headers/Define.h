#pragma once

#define MAX_STR 256
#define MID_STR 128
#define MIN_STR 64

#define WINCX 1280
#define WINCY 720
#define TILECX 130
#define TILECY 68
#define TILEX 30
#define TILEY 20

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define SWORD	0x01
#define AXE		0x02
#define BOW		0x04

#define SHOP 1

#define NOCOPY(ClassName)						\
private:										\
	ClassName(ClassName& rObj) {};				\
	void operator=(ClassName& rObj) {}

#define DECLARE_SINGLETON(ClassName)			\
public:											\
static ClassName* Get_Instance()				\
{												\
	if (nullptr == m_pInstance)					\
		m_pInstance = new ClassName;			\
	return m_pInstance;							\
}												\
static void Destroy_Instance()					\
{												\
	if (m_pInstance)							\
	{											\
		delete m_pInstance;						\
		m_pInstance = nullptr;					\
	}											\
}												\
NOCOPY(ClassName)								\
private:										\
	static ClassName* m_pInstance;				


#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;

#define GET_INSTANCE(ClassName)					\
ClassName::Get_Instance()


#ifndef _AFX
#define ERR_MSG(msg) MessageBox(nullptr, msg, L"System Error", MB_OK)
#else
#define ERR_MSG(msg) AfxMessageBox(msg)
#endif