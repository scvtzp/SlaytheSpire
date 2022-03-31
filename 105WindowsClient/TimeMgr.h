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

	// 자주 프레임을 실행하면 간격이 작아 작은 값을 곱하고 가끔 프레임을 실행하면 간격이 커서 큰값을 곱해주면 자주 실행하건 가끔 실행하건 비슷하게 맞춰 줄수 있다. 
	float m_fDeltaTime; 
	// 내가 이해한건 그냥 이동하는 함수를 많이 출력하든 적게 출력하든 결국 이동속도는 똑같이 나오게끔 만들어주는 개념. 
};

