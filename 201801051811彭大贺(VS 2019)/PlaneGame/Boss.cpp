#include "StdAfx.h"
#include "Boss.h"
#include "Resource.h"

CImageList CBoss::m_Images;

CBoss::CBoss(void)
{
	//���ȷ��Xλ��
	m_ptPos.x = rand() % (GAME_WIDTH - BOSS_HEIGHT) + 1;

	//���ȷ��ͼ������
	m_nImgIndex = 0;
	m_ptPos.y=0;

	//����ͼ������ȷ������
    m_nMotion = 1;
	m_ptPos.y =0;
	//��ʼ���ٶ�
	m_V = 3;
	//������ʱ
	m_nWait = 0;
	y=2;
	x=1;
}

CBoss::~CBoss(void)
{
}
BOOL CBoss::LoadImage()
{
	return CGameObject::LoadImage(m_Images, IDB_BITMAP7 , RGB(0, 0, 0), 180, 108, 1);
}
BOOL CBoss::Draw(CDC* pDC, BOOL bPause)
{
	m_nWait++;
	if (m_nWait>10)
		m_nWait = 0;
	if (!bPause)
	{
		m_ptPos.y = m_ptPos.y +y;
		m_ptPos.x = m_ptPos.x +x;
	}
	if (m_ptPos.x <= 0)
	{
		m_ptPos.x = 0;
		x = 1;
	}
	if (m_ptPos.y <= 15)
	{
		m_ptPos.y = 15;
		y = 2;
	}
	if (m_ptPos.y >= 250)
	{
		m_ptPos.y = 250;
		y = -2;
	}
	if (m_ptPos.x >= GAME_WIDTH - BOSS_WIDTH-15)
	{
		m_ptPos.x = GAME_WIDTH - BOSS_WIDTH-15;
		x = -1;
	}
	m_Images.Draw(pDC, m_nImgIndex, m_ptPos, ILD_TRANSPARENT);

	return TRUE;
}
BOOL CBoss::Fired()
{
	if (m_nWait == 0)
		return TRUE;
	else
		return FALSE;
}