#include "StdAfx.h"
#include "MyPlane.h"
#include "resource.h"

CImageList CMyPlane::m_Images;

CMyPlane::~CMyPlane(void)
{
}
CMyPlane::CMyPlane(void):m_nHorMotion(0),m_nVerMotion(0)
{
	m_nWait = 0;
	m_ptPos.x = 300;
	m_ptPos.y = 400;
}

BOOL CMyPlane::Fired()
{
	if(m_nWait==0)
		return TRUE;
	else
		return FALSE;

}
BOOL CMyPlane::LoadImage()
{
	return CGameObject::LoadImage(m_Images,IDB_BITMAP12,RGB(0,0,0),69,78,1);
}
BOOL CMyPlane::Draw(CDC* pDC,BOOL bPause)
{
	m_nWait++;
	if(m_nWait>3)
		m_nWait=0;


	if(!bPause)
	{
		m_ptPos.x = m_ptPos.x + m_nHorMotion*8;
		m_ptPos.y = m_ptPos.y - m_nVerMotion*8;
	}
	//防止战机飞出窗口画面
	if(m_ptPos.x>=GAME_WIDTH-PLANE_WIDTH)
		m_ptPos.x =GAME_WIDTH-PLANE_WIDTH;
	if(m_ptPos.x<=0)
		m_ptPos.x=0;

	if(m_ptPos.y<=0)
		m_ptPos.y =0;

	if(m_ptPos.y>=GAME_HEIGHT-PLANE_HEIGHT)
		m_ptPos.y=GAME_HEIGHT-PLANE_HEIGHT;


	m_Images.Draw(pDC,0,m_ptPos,ILD_TRANSPARENT);
	return TRUE;
}