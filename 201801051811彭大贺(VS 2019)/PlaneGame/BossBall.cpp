#include "StdAfx.h"
#include "Bossball.h"
#include "resource.h"

CImageList CBossBall::m_Images;

CBossBall::CBossBall(int x, int y, int nMontion) :CGameObject(x, y), m_nMotion(nMontion)
{

}

CBossBall::~CBossBall(void)
{
}
BOOL CBossBall::Draw(CDC* pDC, BOOL bPause)
{
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y + m_nMotion * 20;
	}

	if (m_ptPos.y > GAME_HEIGHT + BALL_HEIGHT)
		return FALSE;
	if (m_ptPos.y < -BALL_HEIGHT)
		return FALSE;

	m_Images.Draw(pDC, 0, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}

BOOL CBossBall::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP5, RGB(0, 0, 0), 40, 50, 1);
}