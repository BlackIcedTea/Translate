
// TranslateDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Translate.h"
#include "TranslateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTranslateDlg �Ի���




CTranslateDlg::CTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTranslateDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_FRONT, m_wndFront);
    DDX_Control(pDX, IDC_BEHIND, m_wndBehind);
}

BEGIN_MESSAGE_MAP(CTranslateDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_FRONT, &CTranslateDlg::OnBnClickedFront)
    ON_WM_MOVE()
    ON_WM_DESTROY()
    ON_BN_CLICKED(IDC_TRANSLATE, &CTranslateDlg::OnBnClickedTranslate)
    ON_BN_CLICKED(IDC_BEHIND, &CTranslateDlg::OnBnClickedBehind)
    
END_MESSAGE_MAP()


// CTranslateDlg ��Ϣ�������

BOOL CTranslateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��



    // ������ͼ����
    m_pFrontView = new CTranslateView(_T("�Զ����"),_T("auto"),TRUE);
	// ������ͼ
    m_pFrontView->Create(L"",L"",WS_CHILD|WS_VISIBLE,CRect(10,50,440,500),this,NULL,NULL);
    m_pFrontView->OnInitialUpdate();
    // ������ͼ����
    m_pArrayView[0] = new CTranslateView(_T("Ӣ��"),_T("en"));
    // ������ͼ
     m_pArrayView[0]->Create(L"",L"",WS_CHILD|WS_VISIBLE,CRect(440,50,1100,500),this,NULL,NULL);
     m_pArrayView[0]->OnInitialUpdate();

     // �������ڶ���(����ǰ������ѡ��)
     m_pFrontLonguage = new CLanguageDialog(&m_wndFront,m_pFrontView,TRUE);
     // ��������
     m_pFrontLonguage->Create(IDD_TRANSLATEDIALOG);



     // �������ڶ���(����������ѡ��)
     m_pBehindLonguage = new CLanguageDialog(&m_wndBehind,m_pArrayView[0],FALSE);
     // ��������
     m_pBehindLonguage->Create(IDD_TRANSLATEDIALOG);
     // ��ʾ����
    
     // ���ഫ�ݻ������
     m_pFrontLonguage->m_pMutexObject = m_pBehindLonguage;


     // ����Ĭ��ǰ��ť����
     m_wndFront.SetWindowText(_T("�Զ����"));
     // ����Ĭ�Ϻ�ť����
    m_wndBehind.SetWindowText(_T("Ӣ��"));



    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTranslateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTranslateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTranslateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// �����ť(����ǰ)����ѡ��
void CTranslateDlg::OnBnClickedFront()
{
    
    // ����Ի����λ��
    CRect DialogRect;
    // ��ȡ�Ի����λ��
    GetDlgItem(IDC_FRONT)->GetWindowRect(&DialogRect);
    // ���ô���λ��
    m_pFrontLonguage->SetWindowPos(NULL,DialogRect.left,DialogRect.bottom,0,0,SWP_NOSIZE);

    // �������뽹��
    
    

    // ��ʾ����
    
    m_pFrontLonguage->SetFocus();
    
    m_pFrontLonguage->ShowWindow(SW_SHOW);
    
    
    m_pFrontLonguage->UpdateWindow();
    m_pFrontLonguage->SetActiveWindow();
    
        
    
}

// �����ť(��Ҫ����ɵ�����)����ѡ��
void CTranslateDlg::OnBnClickedBehind()
{
    // ����Ի����λ��
    CRect DialogRect;
    // ��ȡ�Ի����λ��
    GetDlgItem(IDC_BEHIND)->GetWindowRect(&DialogRect);
    // ���ô���λ��
    m_pBehindLonguage->SetWindowPos(NULL,DialogRect.left,DialogRect.bottom,0,0,SWP_NOSIZE);
    // �������뽹��
    
    
    
    m_pBehindLonguage->SetFocus();
    // ��ʾ����
    m_pBehindLonguage->ShowWindow(SW_SHOW);
    m_pBehindLonguage->SetActiveWindow();
   
    
}





void CTranslateDlg::OnMove(int x, int y)
{
    CDialog::OnMove(x, y);

    //// ����Ի����λ��
    //CRect DialogRect;
    //// ��ȡ�Ի����λ��
    //GetDlgItem(IDC_FRONT)->GetWindowRect(&DialogRect);
    //// ���ô���λ��
    //m_pDialog->SetWindowPos(NULL,DialogRect.left,DialogRect.bottom,0,0,SWP_NOSIZE);

    
    
}

BOOL CTranslateDlg::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: �ڴ����ר�ô����/����û���

    return CDialog::Create(lpszTemplateName, pParentWnd);
}

void CTranslateDlg::OnDestroy()
{
    CDialog::OnDestroy();

    // ���ٷ������ԶԻ���
    m_pFrontLonguage->DestroyWindow();
    
    // �����ӶԻ���
    

}

void CTranslateDlg::OnBnClickedTranslate()
{
    // ��ȡ��������
    m_pFrontView->GetDlgItem(IDC_EDIT)->GetWindowText(CTranslateView::strText);
    // ����
    m_pArrayView[0]->Translate();
}



BOOL CTranslateDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}


