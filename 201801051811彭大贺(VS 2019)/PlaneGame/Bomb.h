#pragma once
#include "gameobject.h"

class CBomb :
	public CGameObject
{
public:
	CBomb(int x,int y);
	~CBomb(void);
	int speedx;
	int speedy;
	BOOL Draw(CDC* pDC,BOOL bPause);
	void setspeedx(int vx){ speedx = vx; }
	void setspeedy(int vy){ speedy = vy; }
	static BOOL LoadImage();
	//BOOL Draw(CDC* pDC,BOOL bPause);

	//static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos,CPoint(m_ptPos.x+10,m_ptPos.y+BOMB_HEIGHT));
	}
private:
	static const int BOMB_HEIGHT = 40;
	static const int BOMB_WIDTH =30;
	static CImageList m_Images;

};
