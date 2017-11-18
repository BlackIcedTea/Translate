// LanguageDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Translate.h"
#include "LanguageDialog.h"



// CLanguageDialog �Ի���

IMPLEMENT_DYNAMIC(CLanguageDialog, CDialog)

CLanguageDialog::CLanguageDialog(CWnd* pParent /*=NULL*/) : CDialog(CLanguageDialog::IDD, pParent)
{
    // ����ѡ��ť
    m_pButton = NULL;
    // �Ƿ�Ϊǰһ���İ�ť
    m_bIsFront = TRUE;
}

CLanguageDialog::CLanguageDialog(CButton* pButton,CTranslateView* pView ,BOOL bIsFront ,CWnd* pParent/*=NULL*/ ) : CDialog(CLanguageDialog::IDD, pParent)
{
    // ����ѡ��ť
    m_pButton = pButton;
    // �Ƿ�Ϊǰһ���İ�ť
    m_bIsFront = bIsFront;
    m_pView = pView;
    // �������
    m_pMutexObject = NULL;
}

CLanguageDialog::~CLanguageDialog()
{
}

void CLanguageDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLanguageDialog, CDialog)
    ON_WM_CTLCOLOR()
    ON_WM_LBUTTONDOWN()
    ON_WM_KILLFOCUS()
    ON_WM_PAINT()
    ON_COMMAND_RANGE(0xF0,0x10B,OnCommand)
    ON_WM_SETFOCUS()
    ON_WM_NCLBUTTONDOWN()
    ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CLanguageDialog ��Ϣ�������
BOOL CLanguageDialog::OnInitDialog()
{
    CDialog::OnInitDialog();


    CRect rc; // rounded rectangle 
    GetClientRect(&rc); // window rect in screen coords
    m_rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,3,3); 
    //�����������
    SetWindowRgn(m_rgn,TRUE); // set window region to make rounded window
    // ���ô�����ɫ
    m_brush.CreateSolidBrush(RGB(135,206,235));   //   ����һ��ɫˢ�� 


    // ��һ��
    m_wndBut[0].Create(_T("��������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,75,80,95),this,0xF0);
    m_wndBut[1].Create(_T("��ɳ������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,100,90,120),this,0xF1);
    m_wndBut[2].Create(_T("����������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,125,90,145),this,0xF2);
    m_wndBut[3].Create(_T("������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(15,150,65,170),this,0xF3);
    // �ڶ���
    m_wndBut[4].Create(_T("������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,75,155,95),this,0xF4);
    m_wndBut[5].Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,100,145,120),this,0xF5);
    m_wndBut[6].Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,125,145,145),this,0xF6);
    m_wndBut[7].Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,150,145,170),this,0xF7);
    m_wndBut[8].Create(_T("������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(105,175,155,195),this,0xF8);
    // ������
    m_wndBut[9].Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,75,215,95),this,0xF9);
    m_wndBut[10].Create(_T("������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,100,225,120),this,0xFA);
    m_wndBut[11].Create(_T("�ݿ���"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,125,225,145),this,0xFB);
    m_wndBut[12].Create(_T("����������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(175,150,245,170),this,0xFC);
    // ������
    m_wndBut[13].Create(_T("��������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,75,335,95),this,0xFD);
    m_wndBut[14].Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,100,310,120),this,0xfE);
    m_wndBut[15].Create(_T("�����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,125,320,145),this,0xFF);
    m_wndBut[16].Create(_T("˹����������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,150,350,170),this,0x100);
    m_wndBut[17].Create(_T("̩��"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(270,175,310,195),this,0x101);
    // ������
    m_wndBut[18].Create(_T("������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,75,415,95),this,0x102);
    m_wndBut[19].Create(_T("��������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,100,430,120),this,0x103);
    m_wndBut[20].Create(_T("ϣ����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,125,415,145),this,0x104);
    m_wndBut[21].Create(_T("��������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(365,150,430,170),this,0x105);
    // ������
    m_wndBut[22].Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,75,490,95),this,0x106);
    m_wndBut[23].Create(_T("Ӣ��"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,100,490,120),this,0x107);
    m_wndBut[24].Create(_T("�������"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,125,515,145),this,0x108);
    m_wndBut[25].Create(_T("����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,150,490,170),this,0x109);
    m_wndBut[26].Create(_T("���ķ���"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(450,175,515,195),this,0x10A);
    
    if(m_bIsFront == TRUE)
    {// ����ǰ����ѡ����ͼ
        // �Զ����������
        m_wndAutoBut.Create(_T("�Զ����"),WS_CHILD|WS_VISIBLE|WS_TABSTOP  ,CRect(10,10,90,36),this,0x10B);
        // ����Ĭ�������ַ���
        CTranslateView::strPreLanguage = _T("auto");
        // Ĭ�Ͼ�IDΪ�Զ����
        m_nOldID = 0x10B;
        
    }else
    {// ��Ҫ�����ʲô����ѡ����ͼ
        // Ĭ��Ӣ��
        m_nOldID = 0x107;
        // ѭ����� ��ѡ��
        for (int nIndex = 0;nIndex<27;nIndex++)
        {
            //m_wndBut[nIndex].ModifyStyle(0,BS_CHECKBOX|BS_AUTOCHECKBOX);
        }
        
    }

    // �����Զ�����ֹ
    GetDlgItem(m_nOldID)->EnableWindow(FALSE);
    




    return TRUE;  // return TRUE unless you set the focus to a contro
    // �쳣: OCX ����ҳӦ���� FALSE
}



HBRUSH CLanguageDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC,   pWnd,   nCtlColor);

    ////�����һ���Ƿ�Ϊ�Ի�����ж����
    if(nCtlColor == CTLCOLOR_DLG)
        return m_brush;   //������ɫˢ��

    return   hbr;
}

void CLanguageDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
    //ShowWindow(SW_HIDE);

    CDialog::OnLButtonDown(nFlags, point);
}


void CLanguageDialog::OnKillFocus(CWnd* pNewWnd)
{
    ShowWindow(SW_HIDE);
    CDialog::OnKillFocus(pNewWnd);
    
    
}

BOOL CLanguageDialog::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{

    return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}


void CLanguageDialog::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    // ����������
    CFont* pOldFont = dc.SelectObject(CFont::FromHandle( (HFONT)GetStockObject(DEFAULT_GUI_FONT)));

    // ����͸��
    dc.SetBkMode(TRANSPARENT);
    // �����ı�
    dc.TextOut(15,60,_T("ABC"));
    dc.TextOut(105,60,_T("DEFG"));
    dc.TextOut(175,60,_T("HIJKLMN"));
    dc.TextOut(270,60,_T("OPQRST"));
    dc.TextOut(365,60,_T("UVWX"));
    dc.TextOut(450,60,_T("YZ"));
    

    // ���þ�����
    dc.SelectObject(pOldFont);

}
void CLanguageDialog::OnCommand(UINT nID)
{
    // ������ʱ��ť����
    CString strWindowName;
    
    // ��ֹ��ť
    GetDlgItem(nID)->EnableWindow(FALSE);
    // ���þ�IDΪ���Ե��״̬
    GetDlgItem(m_nOldID)->EnableWindow(TRUE);
   

    // ��ȡ����,
    GetDlgItem(nID)->GetWindowText(strWindowName);
    // ���õ���ť��
    m_pButton->SetWindowText(strWindowName);
    // ���õ���ʾ����
    m_pView->GetDlgItem(IDC_TYPE)->SetWindowText(strWindowName);

    // ����ID������������
    // �ж��Ƿ�Ϊ��������Զ���
    if ( m_bIsFront == TRUE)
    {

        // �ж��Ƿ����Զ��ж�
        if ( m_nOldID != 0x10B)
        { // �����ֹ
            m_pMutexObject->GetDlgItem(m_nOldID)->EnableWindow(TRUE);
        }

        // �ж��Ƿ��� �Զ��ж�ID
        if (nID!=0x10B)
        {// ���ǲŷ��� ��ͬ������ͻ������
            m_pMutexObject->GetDlgItem(nID)->EnableWindow(FALSE);
        }

        // ���������ַ���
        CTranslateView::strPreLanguage = GetLanguagText(nID);
    }else
    {
        // �ж��Ƿ�Ϊ����
        // �ж��Ƿ�Ϊ�Զ��ж�
        if( nID!=0x10B )
        {
            // ���÷���������
            m_pView->m_strLanguage = GetLanguagText(nID);
            
        }
    }


    // ����Ϊ��ID
    m_nOldID = nID;
    // ���ش���
    ShowWindow(SW_HIDE);
}

wchar_t* CLanguageDialog::GetLanguagText(UINT nID)
{


    // ��������
    if(nID == 0xF0 )
        return L"ara";
    // ��ɳ������
    else if ( nID == 0xF1 )
        return L"est";
    // ����������
    else if ( nID == 0xF2 )
        return L"bul";
    // ������
    else if ( nID == 0xF3 )
        return L"pl";
    // ������
    else if( nID == 0xF4 )
        return L"dan";
    // ����
    else if( nID == 0xF5 )
        return L"de";
    // ����
    else if( nID == 0xF6 )
        return L"ru";
    // ����
    else if( nID == 0xF7 )
        return L"fra";
    // ������
    else if( nID == 0xF8 )
        return L"fin";
    // ����
    else if( nID == 0xF9 )
        return L"kor";
    // ������
    else if( nID == 0xFA )
        return L"nl";
    // �ݿ���
    else if( nID == 0xFB )
        return L"cs";
    // ����������
    else if( nID == 0xFC )
        return L"rom";
    // ��������
    else if( nID == 0xFD )
        return L"pt";
    // ����
    else if( nID == 0xFE )
        return L"jp";
    // �����
    else if( nID == 0xFF )
        return L"swe";
    // ˹����������
    else if( nID == 0x100 )
        return L"slo";
    // ̩��
    else if( nID == 0x101 )
        return L"th";
    // ������
    else if( nID == 0x102 )
        return L"wyw";
    // ��������
    else if( nID == 0x103 )
        return L"spa";
    // ϣ����
    else if( nID == 0x104 )
        return L"el";
    // ��������
    else if ( nID == 0x105 )
        return L"hu";
    // ����
    else if ( nID == 0x106 )
        return L"zh";
    // Ӣ��
    else if ( nID == 0x107 )
        return L"en";
    // �������
    else if ( nID == 0x108 )
        return L"it";
    // ����
    else if ( nID == 0x109 )
        return L"yue";
    // ���ķ���
    else if ( nID == 0x10A )
        return L"cht";
    // �Զ����
    else 
        return L"auto";
}

void CLanguageDialog::OnSetFocus(CWnd* pOldWnd)
{
    CDialog::OnSetFocus(pOldWnd);

    // TODO: �ڴ˴������Ϣ����������
}

void CLanguageDialog::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

    CDialog::OnNcLButtonDown(nHitTest, point);
}

void CLanguageDialog::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
    CDialog::OnActivate(nState, pWndOther, bMinimized);
    // û�����뽹��
    if( WA_INACTIVE == nState)
    {
        // ���ش���
        ShowWindow(SW_HIDE);
    }
}
