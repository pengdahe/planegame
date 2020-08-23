#pragma once
#include "GameObject.h"

class CBossBall :public CGameObject
{
public:
	CBossBall(int x, int y, int nMontion);
	~CBossBall(void);

	//BOOL Draw(CDC* pDC, BOOL bPause);
	int speedX;
	int speedY;
	BOOL Draw(CDC* pDC,BOOL bPause);
	void setspeedX(int vX){ speedX = vX; }
	void setspeedY(int vY){ speedY = vY; }

	static BOOL LoadImage();

	CRect GetRect()
	{
		return CRect(m_ptPos, CPoint(m_ptPos.x + BALL_HEIGHT, m_ptPos.y + BALL_HEIGHT));
	}
private:
	static const int BALL_HEIGHT = 8;
	static CImageList m_Images;
	int    m_nMotion;
};