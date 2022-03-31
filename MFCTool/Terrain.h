#pragma once
class CMFCToolView;
class CTerrain
{
public:
	CTerrain();
	~CTerrain();
public:
	void Set_View(CMFCToolView* pView) { m_pView = pView;  }
	vector<TILE*>& Get_Tile() { return m_vecTile; }
public:
	void TileChange(const D3DXVECTOR3& rMouse, const BYTE& rbyDrawID, const BYTE& rbyOption =0);
	int Get_Index(const D3DXVECTOR3& rPos); 
	bool IsPicking(const D3DXVECTOR3& rPos, const int& iIndex); 
	void SetRatio(D3DXMATRIX* pOut, const float& fRatioX, const float& fRatioY);
	void MiniRender();
public:
	HRESULT Initialize();
	void Render(); 
	void Release(); 
private:
	vector<TILE*> m_vecTile;
	CMFCToolView* m_pView; 
};

