#pragma once

template<typename T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T; 
		if (FAILED(pObj->Initialize()))
		{
			ERR_MSG(L"Obj Create Failed!"); 
			return nullptr; 
		}
		return pObj; 
	}
};