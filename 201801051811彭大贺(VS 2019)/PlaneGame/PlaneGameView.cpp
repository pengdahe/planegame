// PlaneGameView.cpp : CPlaneGameView ���ʵ��

#include "stdafx.h"
#include "PlaneGame.h"

#include "PlaneGameDoc.h"
#include "PlaneGameView.h"
#include "MyPlane.h"
#include "Enemy.h"
#include "Bomb.h"
#include "Ball.h"
#include "Explosion.h"
#include <atlimage.h>
#include <Windows.h>
#include "Boss.h"
#include "BossBall.h"
#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneGameView

IMPLEMENT_DYNCREATE(CPlaneGameView, CView)

BEGIN_MESSAGE_MAP(CPlaneGameView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()

	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CPlaneGameView ����/����

//����Ѫ����������ȫ�ֱ���
int CPlaneGameView::score = 0;
int CPlaneGameView::life = 10;
int CPlaneGameView::num = 100;
int CPlaneGameView::n=1;
int CPlaneGameView::sx = 0;
int CPlaneGameView::life1 = 100;
int CPlaneGameView::cnt = 0;
CPlaneGameView::CPlaneGameView():m_pMe(NULL)
{
	// TODO: �ڴ˴���ӹ������
}

CPlaneGameView::~CPlaneGameView()
{

}

BOOL CPlaneGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPlaneGameView ����

void CPlaneGameView::OnDraw(CDC* /*pDC*/)
{
	CPlaneGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPlaneGameView ��ӡ

BOOL CPlaneGameView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPlaneGameView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPlaneGameView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CPlaneGameView ���

#ifdef _DEBUG
void CPlaneGameView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneGameDoc* CPlaneGameView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneGameDoc)));
	return (CPlaneGameDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneGameView ��Ϣ�������
void CPlaneGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	//HWND hwnd = AfxGetApp()->GetMainWnd()->GetSafeHwnd();   //��ȡ�����ھ��
	//SetWindowPos(hwnd, HWND_NOTOPMOST, 100, 100, 950, 600, SWP_NOMOVE);
	// TODO: �ڴ����ר�ô����/����û���
	//PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC|SND_LOOP);//��������

	//��ʼ����Ϸ
	InitGame();
}
void CPlaneGameView::StopGame()
{
	delete m_pMe;
	delete m_pMemDC;
	delete m_pDC;
	delete m_pMemBitmap;
	//delete enemy;
}

BOOL CPlaneGameView::InitGame()
{
	CRect rc;
	GetClientRect(rc);

	//�������������
	srand( (unsigned)time( NULL ) );

	//�����豸DC
	m_pDC = new CClientDC(this);

	//�����ڴ�DC
	m_pMemDC = new CDC;
	m_pMemDC->CreateCompatibleDC(m_pDC);

	//�����ڴ�λͼ
	m_pMemBitmap = new CBitmap;
	m_pMemBitmap->CreateCompatibleBitmap(m_pDC,GAME_WIDTH,GAME_HEIGHT);

	//��λͼѡ���ڴ�DC
	m_pMemDC->SelectObject(m_pMemBitmap);

	CMyPlane::LoadImage();
	CEnemy::LoadImage();
	CBomb::LoadImage();
	CBall::LoadImage();
	CExplosion::LoadImage();
	CBoss::LoadImage();
	CBossBall::LoadImage();
	//��������(ս��)
	m_pMe = new CMyPlane;

	//������Ϸ
	SetTimer(1,30,NULL);
    //PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	 PlaySound((LPCTSTR)IDR_WAVE1, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC|SND_LOOP);//��������//��������
	//PlaySound((LPCTSTR)IDR_WAVE1, NULL, SND_RESOURCE | SND_ASYNC| SND_LOOP);
	return TRUE;
}

void CPlaneGameView::UpdateFrame(CDC* pMemDC)
{
	//�������
	//pMemDC->FillSolidRect(0,0,GAME_WIDTH,GAME_HEIGHT,RGB(84, 142, 239));
	CDC memDC;
	memDC.CreateCompatibleDC(pMemDC);
	CBitmap bmpDraw;
	bmpDraw.LoadBitmap(IDB_BITMAP1);
	
	CBitmap* pbmpOld = memDC.SelectObject(&bmpDraw);
	pMemDC->BitBlt(0, 0, 800, 600, &memDC, 0, 0, SRCCOPY);
	memDC.SelectObject(pbmpOld);
	//�����ı���ͼ
	CRect rctClient;
	GetClientRect(rctClient);
	
	static int imagelocation = 0;
	CDC memDC1;
	memDC1.CreateCompatibleDC(pMemDC);
	CBitmap bmpDraw1;

	if(cnt==0)
	bmpDraw1.LoadBitmapW(IDB_BITMAP1);//����λͼ
	if(cnt==1) 
	bmpDraw1.LoadBitmapW(IDB_BITMAP11);//����λͼ
	if(cnt==2)
     bmpDraw1.LoadBitmapW(IDB_BITMAP13);//����λͼ

	CBitmap * pbmpold = memDC1.SelectObject(&bmpDraw1);
	pMemDC->BitBlt(0, imagelocation, 800, 600 - imagelocation, &memDC1, 0, 0, SRCCOPY);//���ö�̬����
	pMemDC->BitBlt(0, 0, 800, imagelocation, &memDC1, 0, 600 - imagelocation, SRCCOPY);
	imagelocation++;

	if (imagelocation == 600)
		imagelocation = 0;

	//�����ҷ�ս��
	if(m_pMe!=NULL)
	{
		if(score>=200)
		{ 
			CString str3 = _T("�ϴ� life��");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(255, 0, 0));
	   pMemDC->TextOut(45 * 1, 60 * 1, str3);
	   str3.Format(_T("%d"), CPlaneGameView::getlife1());
	   pMemDC->TextOut(120 * 1, 60 * 1, str3);
		}
	   m_pMe->Draw(m_pMemDC,FALSE);
	 CString str1 = _T("  now�÷� ��");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(255, 0, 0));
	   pMemDC->TextOut(35* 1, 20* 1, str1);
	   str1.Format(_T("%d"), CPlaneGameView::getscore());
	   pMemDC->TextOut(110 * 1, 20 * 1, str1);
	
	CString str2 = _T("  nowս��������");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(255, 0, 0));
	   pMemDC->TextOut(50 * 1, 40 * 1, str2);
	   str2.Format(_T("%d"), CPlaneGameView::getlife());
	   pMemDC->TextOut(110 * 1, 40 * 1, str2);

	   if(score<=1000)
	   {//��ʾ�ؿ�
	   CString str4 = _T("ctrl���ӵ�A���ո��ӵ�B���������Ҽ��ƶ�");
	   pMemDC->SetBkMode(TRANSPARENT);
	   pMemDC->SetTextAlign(TA_CENTER);
	   pMemDC->SetTextColor(RGB(255, 0, 0));
	   pMemDC->TextOut(480* 1, 20* 1, str4);
	   str4.Format(_T("%d"), CPlaneGameView::getcnt()+1);
	   pMemDC->TextOut(350* 1, 300 * 1, str4);
	   }
	   CString str4444 = _T("F1��������Ѫ��F2���м���Ѫ��F3���߼���Ѫ");
	   pMemDC->TextOut(480 * 1, 60 * 1, str4444);
	   CString str44 = _T("��200�ֿ��Գ����ϴ���������ɽ�����һ��");
	   pMemDC->TextOut(480* 1, 40 * 1, str44);
	 if(cnt==3)
	    {   //Game Over
		
		CString str=_T("��ϲͨ��!");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255,0,0));
		pMemDC->TextOut(GAME_WIDTH/2,GAME_HEIGHT/2,str);
		}
	}
	

	if(m_pMe==NULL)
	{   //Game Over
		
		//PlaySound((LPCTSTR)IDR_WAVE3, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
		CString str=_T("�ף�����һ�ְ�!");
		pMemDC->SetBkMode(TRANSPARENT);
		pMemDC->SetTextAlign(TA_CENTER);
		pMemDC->SetTextColor(RGB(255,0,0));
		pMemDC->TextOut(GAME_WIDTH/2,GAME_HEIGHT/2,str);
		  
	}

	//���� ��������ը���л����ӵ���Boss,Bossball
	for(int i=0;i<6;i++)
	{
		POSITION pos1,pos2;
		for( pos1 = m_ObjList[i].GetHeadPosition(); ( pos2 = pos1 ) != NULL; )
		{
			CGameObject* pObj = (CGameObject*)m_ObjList[i].GetNext( pos1 );
			if(!pObj->Draw(pMemDC,FALSE))
			{
				m_ObjList[i].RemoveAt(pos2);
				delete pObj;
			}
		}
	}

	//�����ڴ�DC���豸DC
	m_pDC->BitBlt(0,0,GAME_WIDTH,GAME_HEIGHT,m_pMemDC,0,0,SRCCOPY);
}
void CPlaneGameView::AI()
{
	static int nCreator = rand() %5+5;

	//��������л�
	if(nCreator<=0)
	{
		nCreator = rand()%(5-getcnt())+10;
		m_ObjList[enEnemy].AddTail(new CEnemy());
	}
	nCreator--;
		
	if(m_pMe==NULL)
		return;

	//����ĸ���������ƶ�ս��
	for(int i=0;i<4;i++)
	{
		int nMeMotion=0;
		m_pMe->SetVerMotion(0);
		m_pMe->SetHorMotion(0);

		nMeMotion = GetKey(VK_UP);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(1);
		    
		nMeMotion = GetKey(VK_DOWN);
		if(nMeMotion==1)
			m_pMe->SetVerMotion(-1);

		nMeMotion = GetKey(VK_RIGHT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(1);

		nMeMotion = GetKey(VK_LEFT);
		if(nMeMotion==1)
			m_pMe->SetHorMotion(-1);
	}
	
	//����ս������
	if (GetKey(VK_SPACE) == 1)
	{
		if (m_pMe != NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			CBomb* bomb1 = new CBomb(pt.x + 50, pt.y + 20);
			bomb1->setspeedx(2);
			bomb1->setspeedy(8);
			m_ObjList[enBomb].AddTail(bomb1);

			CBomb* bomb2 = new CBomb(pt.x, pt.y + 20);
			bomb2->setspeedx(-2);
			bomb2->setspeedy(8);
			m_ObjList[enBomb].AddTail(bomb2);
			CBomb* bomb3 = new CBomb(pt.x + 25, pt.y + 20);
			bomb3->setspeedx(0);
			bomb3->setspeedy(10);
			m_ObjList[enBomb].AddTail(bomb3);
		}
	}
	if(GetKey(VK_LCONTROL)==1)//������ctrl��
	{
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			CPoint pt = m_pMe->GetPoint();
			
			{
			CBomb *bomb1 = new CBomb(pt.x +25, pt.y + 20);
					bomb1->setspeedx(0);
					bomb1->setspeedy(10);
					m_ObjList[enBomb].AddTail(bomb1);
			}
		
		}
	}


	//�л������ӵ�

	CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enEnemy].GetHeadPosition();ePos!=NULL;)
	{
          CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos);
		  if(!pEnemy->Fired())
			  continue;
		  CPoint  ePt = pEnemy->GetPoint();

		  BOOL by=FALSE;

		  //�л���ս��ǰ��
		  if(pEnemy->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(pEnemy->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBall].AddTail(new CBall(ePt.x+10,ePt.y+10,pEnemy->GetMontion()));
		  }
	}
	
	//�л��ӵ�ը��ս��
		POSITION bPos1 = NULL, bPos2 = NULL;
		CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBall* pBall = (CBall*)m_ObjList[enBall].GetNext(bPos1);
			CRect bRect = pBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
              life--;
				//��ӱ�ըЧ��
				//	PlaySound((LPCTSTR)IDR_EXPLOTAION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left, mRect.top)
					);

				//ɾ���ӵ�
				m_ObjList[enBall].RemoveAt(bPos2);
				delete pBall;

				//ɾ��ս��
				if (life == 0){
					delete m_pMe;
					m_pMe = NULL;
					break;}
			}
		}
	

	//��Ѫģʽ
		if(GetKey(VK_F1)==1)
		{ life=100;
		}
		if (GetKey(VK_F2) == 1)
		{
			life = 1000;
		}
		if (GetKey(VK_F3) == 1)
		{
			life = 2000;
		}
	//C�ӵ�
	/*if(GetKey(VK_SHIFT)==1)//����shift��
	{
		
	{	CPoint pt = m_pMe->GetPoint();
		if(m_pMe!=NULL && m_pMe->Fired())
		{
			       CBomb *bomb1 = new CBomb(pt.x + 50, pt.y + 30);
					bomb1->setspeedx(10);
					bomb1->setspeedy(20);
					m_ObjList[enBomb].AddTail(bomb1);
					  CBomb *bomb9 = new CBomb(pt.x + 50, pt.y + 30);
					bomb1->setspeedx(5);
					bomb1->setspeedy(20);
					m_ObjList[enBomb].AddTail(bomb9);
					  CBomb *bomb10 = new CBomb(pt.x + 50, pt.y + 30);
					bomb1->setspeedx(15);
					bomb1->setspeedy(20);
					m_ObjList[enBomb].AddTail(bomb10);

					CBomb *bomb2 = new CBomb(pt.x , pt.y + 30);
					bomb2->setspeedx(-10);
					bomb2->setspeedy(20);
					m_ObjList[enBomb].AddTail(bomb2);
					CBomb *bomb11 = new CBomb(pt.x , pt.y + 30);
					bomb2->setspeedx(-5);
					bomb2->setspeedy(20);
					m_ObjList[enBomb].AddTail(bomb11);
					CBomb *bomb12 = new CBomb(pt.x , pt.y + 30);
					bomb2->setspeedx(-15);
					bomb2->setspeedy(20);
					m_ObjList[enBomb].AddTail(bomb12);
					CBomb *bomb3 = new CBomb(pt.x +25, pt.y + 30);
					bomb3->setspeedx(0);
					bomb3->setspeedy(20);
					m_ObjList[enBomb].AddTail(bomb3);
					CBomb *bomb4 = new CBomb(pt.x + 50, pt.y -30);
					bomb4->setspeedx(10);
					bomb4->setspeedy(-20);
					m_ObjList[enBomb].AddTail(bomb4);
					CBomb *bomb13 = new CBomb(pt.x + 50, pt.y -30);
					bomb4->setspeedx(5);
					bomb4->setspeedy(-20);
					m_ObjList[enBomb].AddTail(bomb13);
					CBomb *bomb14 = new CBomb(pt.x + 50, pt.y -30);
					bomb4->setspeedx(15);
					bomb4->setspeedy(-20);
					m_ObjList[enBomb].AddTail(bomb14);
					CBomb *bomb5 = new CBomb(pt.x , pt.y -30);
					bomb5->setspeedx(-10);
					bomb5->setspeedy(-20);
					m_ObjList[enBomb].AddTail(bomb5);
					  CBomb *bomb6 = new CBomb(pt.x , pt.y + 30);
					bomb6->setspeedx(-20);
					bomb6->setspeedy(0);
					m_ObjList[enBomb].AddTail(bomb6);  
					CBomb *bomb7 = new CBomb(pt.x + 50, pt.y+20 );
					bomb7->setspeedx(20);
					bomb7->setspeedy(0);
					m_ObjList[enBomb].AddTail(bomb7);
					  CBomb *bomb8 = new CBomb(pt.x + 25, pt.y -60);
					bomb8->setspeedx(0);
					bomb8->setspeedy(-20);
					m_ObjList[enBomb].AddTail(bomb8);
					  
		}
	}    
	}*/
	if (GetKey(VK_F8) == 1)
	{
		sx = 1;
	}
	/*if(sx==1)     //wu di mo shi
	{	CPoint pt = m_pMe->GetPoint();
	if (m_pMe != NULL && m_pMe->Fired())
	{
		CBomb* bomb1 = new CBomb(pt.x + 50, pt.y + 30);
		bomb1->setspeedx(10);
		bomb1->setspeedy(20);
		m_ObjList[enBomb].AddTail(bomb1);
		CBomb* bomb9 = new CBomb(pt.x + 50, pt.y + 30);
		bomb1->setspeedx(5);
		bomb1->setspeedy(20);
		m_ObjList[enBomb].AddTail(bomb9);
		CBomb* bomb10 = new CBomb(pt.x + 50, pt.y + 30);
		bomb1->setspeedx(15);
		bomb1->setspeedy(20);
		m_ObjList[enBomb].AddTail(bomb10);

		CBomb* bomb2 = new CBomb(pt.x, pt.y + 30);
		bomb2->setspeedx(-10);
		bomb2->setspeedy(20);
		m_ObjList[enBomb].AddTail(bomb2);
		CBomb* bomb11 = new CBomb(pt.x, pt.y + 30);
		bomb2->setspeedx(-5);
		bomb2->setspeedy(20);
		m_ObjList[enBomb].AddTail(bomb11);
		CBomb* bomb12 = new CBomb(pt.x, pt.y + 30);
		bomb2->setspeedx(-15);
		bomb2->setspeedy(20);
		m_ObjList[enBomb].AddTail(bomb12);
		CBomb* bomb3 = new CBomb(pt.x + 25, pt.y + 30);
		bomb3->setspeedx(0);
		bomb3->setspeedy(20);
		m_ObjList[enBomb].AddTail(bomb3);
		CBomb* bomb4 = new CBomb(pt.x + 50, pt.y - 30);
		bomb4->setspeedx(10);
		bomb4->setspeedy(-20);
		m_ObjList[enBomb].AddTail(bomb4);
		CBomb* bomb13 = new CBomb(pt.x + 50, pt.y - 30);
		bomb4->setspeedx(5);
		bomb4->setspeedy(-20);
		m_ObjList[enBomb].AddTail(bomb13);
		CBomb* bomb14 = new CBomb(pt.x + 50, pt.y - 30);
		bomb4->setspeedx(15);
		bomb4->setspeedy(-20);
		m_ObjList[enBomb].AddTail(bomb14);
		CBomb* bomb5 = new CBomb(pt.x, pt.y - 30);
		bomb5->setspeedx(-10);
		bomb5->setspeedy(-20);
		m_ObjList[enBomb].AddTail(bomb5);
		CBomb* bomb6 = new CBomb(pt.x, pt.y + 30);
		bomb6->setspeedx(-20);
		bomb6->setspeedy(0);
		m_ObjList[enBomb].AddTail(bomb6);
		CBomb* bomb7 = new CBomb(pt.x + 50, pt.y + 20);
		bomb7->setspeedx(20);
		bomb7->setspeedy(0);
		m_ObjList[enBomb].AddTail(bomb7);
		CBomb* bomb8 = new CBomb(pt.x + 25, pt.y - 60);
		bomb8->setspeedx(0);
		bomb8->setspeedy(-20);
		m_ObjList[enBomb].AddTail(bomb8);

	}
	*/
//����boss
		if (n==1 && score>200)
	{
		m_ObjList[enBoss].AddTail(new CBoss);
		n=0;	
	}	
		/*if (n == 1 && score > 200)
		{
			m_ObjList[enBoss].AddTail(new CBoss);
			n = 0;
		}*/


		//Boss�����ӵ�

	//CPoint PlanePt = m_pMe->GetPoint();
	for(POSITION ePos=m_ObjList[enBoss].GetHeadPosition();ePos!=NULL;)
	{
          CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(ePos);
		  if(!pBoss->Fired())
			  continue;
		  CPoint  ePt = pBoss->GetPoint();

		  BOOL by=FALSE;

		  //�л���ս��ǰ��
		  if(pBoss->GetMontion()==1 && ePt.y<PlanePt.y)
		         by=  TRUE;
		  //�л���ս������
		  if(pBoss->GetMontion()==-1 && ePt.y>PlanePt.y)
				 by=  TRUE;	

		  if(by && ePt.x >= PlanePt.x && ePt.x<PlanePt.x+CMyPlane::PLANE_WIDTH)
		  {
              m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x+10,ePt.y+10,pBoss->GetMontion()));
			  m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x+50,ePt.y+10,pBoss->GetMontion()));
			   m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x+170,ePt.y+10,pBoss->GetMontion()));
			  m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x+130,ePt.y+10,pBoss->GetMontion()));
			  m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x+90,ePt.y+10,pBoss->GetMontion()));
			   m_ObjList[enBossBall].AddTail(new CBossBall(ePt.x+0,ePt.y+50,pBoss->GetMontion()));
			        
					  
		  }
	}

	
	//Boss�ӵ�ը��ս��
		//POSITION bPos1 = NULL, bPos2 = NULL;
		//CRect mRect = m_pMe->GetRect();
		for (bPos1 = m_ObjList[enBossBall].GetHeadPosition(); (bPos2 = bPos1) != NULL;)
		{
			CBossBall* pBossBall = (CBossBall*)m_ObjList[enBossBall].GetNext(bPos1);
			CRect bRect = pBossBall->GetRect();
			CRect tmpRect;
			if (tmpRect.IntersectRect(&bRect, mRect))
			{
              life--;
				//��ӱ�ըЧ��
				//	PlaySound((LPCTSTR)IDR_EXPLOTAION, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top)
					);

				//ɾ���ӵ�
				m_ObjList[enBossBall].RemoveAt(bPos2);
				delete pBossBall;

				//ɾ��ս��
				if (life == 0){
					delete m_pMe;
					m_pMe = NULL;
					break;}
			}
		}



	//�л���ս����ײ
	POSITION eePos1 = NULL, eePos2 = NULL;
	for (eePos1 = m_ObjList[enEnemy].GetHeadPosition(); (eePos2 = eePos1) != NULL;)
	{
	CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(eePos1);
		CRect m1Rect = pEnemy->GetRect();
	CRect tmpRect;
		if (tmpRect.IntersectRect(&mRect, m1Rect))
		{
			score=score+3;
			//PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
			//��ӱ�ըЧ��
			life=life-2;
			if(life<=0)
			{delete m_pMe;
		m_pMe = NULL;}
		m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left, mRect.top));
		//ɾ���л�
			
		m_ObjList[enEnemy].RemoveAt(eePos2);
		delete pEnemy;
		
			//CShowBoard::score +=enemy_score;
		break;
		}
	}


	 //ս������ըBoss��
			POSITION yPos1 = NULL, yPos2 = NULL;
			for (yPos1 = m_ObjList[enBomb].GetHeadPosition(); (yPos2 = yPos1) != NULL;)
			{
				CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(yPos1);
				CRect bRect = pBomb->GetRect();
				POSITION gPos1 = NULL, gPos2 = NULL;
				for (gPos1 = m_ObjList[enBoss].GetHeadPosition(); (gPos2 = gPos1) != NULL;)
				{
					CBoss* pBoss = (CBoss*)m_ObjList[enBoss].GetNext(gPos1);
					CRect mRect = pBoss->GetRect();
					CRect tmpRect;
					if (tmpRect.IntersectRect(&bRect, mRect))
					{   
						score++;
						//��ӱ�ըЧ��
						m_ObjList[enExplosion].AddTail(new CExplosion(mRect.left+60, mRect.top+70));
						//ɾ������
						m_ObjList[enBomb].RemoveAt(yPos2);
						delete pBomb;
						//ɾ��boss��
						life1 -= 1;
						if(life1==0)
						{   
							int i=life;
							m_ObjList[enBoss].RemoveAt(gPos2);
							delete pBoss;
							cnt++;
							life+=2;
							life1=100+50*cnt;
						   if(life-i==2)
						   {
							   score=0;
						   }
						   n=1;
							break;
							
						}
						if(cnt==3)
							cnt=0;
					}
				}
			}

	//ս������ը���л�
	POSITION mPos1=NULL,mPos2=NULL;
	for(mPos1=m_ObjList[enBomb].GetHeadPosition();(mPos2=mPos1)!=NULL;)
	{
		CBomb* pBomb = (CBomb*)m_ObjList[enBomb].GetNext(mPos1);
		CRect bRect = pBomb->GetRect();
	
		POSITION ePos1=NULL,ePos2=NULL;
		for(ePos1=m_ObjList[enEnemy].GetHeadPosition();(ePos2=ePos1)!=NULL;)
		{
			CEnemy* pEnemy = (CEnemy*)m_ObjList[enEnemy].GetNext(ePos1);
			CRect mRect = pEnemy->GetRect();
			CRect tmpRect;
			if(tmpRect.IntersectRect(&bRect,mRect))
			{
				//PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
				score+=2;
				//��ӱ�ըЧ��
				m_ObjList[enExplosion].AddTail(
					new CExplosion(mRect.left,mRect.top)
					);
				//ɾ������
				m_ObjList[enBomb].RemoveAt(mPos2);
				delete pBomb;

				//ɾ���л�
				m_ObjList[enEnemy].RemoveAt(ePos2);
				delete pEnemy;
				break;

			}
		}
	}
	
}
void CPlaneGameView::OnTimer(UINT_PTR nIDEvent)
{
	//ˢ����Ϸ֡����: ���ڴ�DC�ϻ�ͼ
	UpdateFrame(m_pMemDC);
	AI();
	
	CView::OnTimer(nIDEvent);
}



void CPlaneGameView::OnDestroy()
{
	CView::OnDestroy();
	this->StopGame();
	// TODO: �ڴ˴������Ϣ����������
}
