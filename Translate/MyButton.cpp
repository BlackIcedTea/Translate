// MyButton.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Translate.h"
#include "MyButton.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
    // Ĭ�����û��������
    m_bMouseOver = FALSE;

}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
    ON_WM_MOUSEMOVE()
    ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)//��Ҫ���ñ�ĺ�����Ϣ����
END_MESSAGE_MAP()



// CMyButton ��Ϣ�������



void CMyButton::PreSubclassWindow()
{
    // �����Ի��Ʒ��
    ModifyStyle(0,BS_OWNERDRAW);

    CButton::PreSubclassWindow();
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    //////////////////////////////////////////////////////////////////////////
    CDC   MemDC;   //���ȶ���һ����ʾ�豸����   
    CBitmap   MemBitmap;//����һ��λͼ����   
    //���������Ļ��ʾ���ݵ��ڴ���ʾ�豸   
    MemDC.CreateCompatibleDC(NULL);   
    //��ʱ�����ܻ�ͼ����Ϊû�еط���   ^_^   
    //////////////////////////////////////////////////////////////////////////

    // ��ȡ��ͼ����
    CDC dc; 
    dc.Attach(lpDrawItemStruct->hDC);

    //////////////////////////////////////////////////////////////////////////
    //���潨��һ������Ļ��ʾ���ݵ�λͼ������λͼ�Ĵ�С������ô��ڵĴ�С   
    MemBitmap.CreateCompatibleBitmap(&dc,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom);
    //��λͼѡ�뵽�ڴ���ʾ�豸��   
    //ֻ��ѡ����λͼ���ڴ���ʾ�豸���еط���ͼ������ָ����λͼ��   
    CBitmap   *pOldBit=MemDC.SelectObject(&MemBitmap);   
    // ����BRUSH�ṹ����Ϣ
    LOGBRUSH LogBrush = {0};
    // ������ˢ
    CBrush* pSysBrush = CBrush::FromHandle((HBRUSH)GetStockObject(4                       ));
   
    // ��ȡBRUSH��ˢ��ɫ
    pSysBrush->GetLogBrush(&LogBrush);
    
    //���ñ���ɫ��λͼ����ɾ����������õ��ǰ�ɫ��Ϊ����   
    //��Ҳ�������Լ�Ӧ���õ���ɫ   
    MemDC.FillSolidRect(0,0,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom,LogBrush.lbColor);   
    
    
    //////////////////////////////////////////////////////////////////////////

    // ������ˢ����
    CBrush brush;
    // ������ɫ��ˢ
    brush.CreateSolidBrush(RGB(255,255,255));
   
    // ����ˢ���õ���ͼ����
    CBrush* pOldBrush = dc.SelectObject(&brush);
    // ����ͼ��
    MemDC.RoundRect(&lpDrawItemStruct->rcItem,CPoint(10,10));
    // ���þͻ�ˢ
    MemDC.SelectObject(pOldBrush);
    // ���ñ���͸��
    MemDC.SetBkMode(TRANSPARENT);
    

    if(m_bMouseOver==TRUE)//�ж��Ƿ���BUTTON��
    {//���������
        MemDC.SetTextColor(RGB(0,114,227)); // ���ú�ɫ�ı�
    }else
    {//��겻������
        MemDC.SetTextColor(RGB(0,0,0)); // ������ɫ�ı�
    }
  
    // ��������
    MemDC.DrawText(_T("Hello"),&lpDrawItemStruct->rcItem,DT_CENTER | DT_VCENTER | DT_SINGLELINE );

    //////////////////////////////////////////////////////////////////////////
    //���ڴ��е�ͼ��������Ļ�Ͻ�����ʾ   
    dc.BitBlt(0,0,lpDrawItemStruct->rcItem.right,lpDrawItemStruct->rcItem.bottom,&MemDC,0,0,SRCCOPY);   
    //��ͼ��ɺ������   
    MemBitmap.DeleteObject();   
    MemDC.DeleteDC();   
    //////////////////////////////////////////////////////////////////////////
}

void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
    CButton::OnMouseMove(nFlags, point);

    if (m_bMouseOver==FALSE)//���һ��ʼ��FALSE,����˵��û��
    {
        m_bMouseOver = TRUE;//Ȼ��͸��޸�ΪTRUE
        Invalidate(FALSE);//����ˢ��
    }

    //////////////////////////////////////////////////////////////////////////
    //���ô�������뿪
    TRACKMOUSEEVENT et = {0};
    et.cbSize = sizeof(et);
    et.hwndTrack = m_hWnd;
    et.dwFlags = TME_LEAVE;//����뿪ʱ֪ͨ
    et.dwHoverTime = HOVER_DEFAULT;//Ĭ��ʱ��
    _TrackMouseEvent(&et);
}

LRESULT CMyButton::OnMouseLeave(WPARAM wParam,LPARAM lParam)
{
    //��������뿪
    m_bMouseOver = FALSE;
    Invalidate(FALSE);//���ñ������
    return TRUE;
} 
