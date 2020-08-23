#include "StdAfx.h"
#include "Bomb.h"
#include "resource.h"


CImageList CBomb::m_Images;


CBomb::CBomb(int x,int y):CGameObject(x,y)
{

}

CBomb::~CBomb(void)
{
}
BOOL CBomb::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP14,RGB(0,0,0),30,40,1);
}
BOOL CBomb::Draw(CDC* pDC,BOOL bPause)
{
	if(!bPause)
	{
		m_ptPos.y = m_ptPos.y - speedy;//我机子弹倾斜问题
		m_ptPos.x = m_ptPos.x + speedx;
	}

	if(m_ptPos.y < -BOMB_HEIGHT||m_ptPos.x<-BOMB_WIDTH||m_ptPos.x>=GAME_WIDTH+BOMB_WIDTH)
		return FALSE;

	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);

	return TRUE;
}