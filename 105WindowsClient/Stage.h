
#include "Scene.h"
class CStage :
	public CScene
{
public:
	CStage();
	virtual ~CStage();

	// CScene��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void Release() override;
};
