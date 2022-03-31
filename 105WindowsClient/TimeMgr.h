#pragma once
class CTimeMgr
{
	DECLARE_SINGLETON(CTimeMgr)
private:
	CTimeMgr();
	~CTimeMgr();
public:
	float Get_DeltaTime(); 
	void Initialize(); 
	void UpdateTime(); 
private:
	LARGE_INTEGER m_OldTime; 
	LARGE_INTEGER m_CPUTick; 

	// ���� �������� �����ϸ� ������ �۾� ���� ���� ���ϰ� ���� �������� �����ϸ� ������ Ŀ�� ū���� �����ָ� ���� �����ϰ� ���� �����ϰ� ����ϰ� ���� �ټ� �ִ�. 
	float m_fDeltaTime; 
	// ���� �����Ѱ� �׳� �̵��ϴ� �Լ��� ���� ����ϵ� ���� ����ϵ� �ᱹ �̵��ӵ��� �Ȱ��� �����Բ� ������ִ� ����. 
};

