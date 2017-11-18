#pragma once

#include "PreButton.h"
#include "TranslateView.h"
// CLanguageDialog �Ի���

class CLanguageDialog : public CDialog
{
	DECLARE_DYNAMIC(CLanguageDialog)
    CBrush   m_brush;
public:
	CLanguageDialog(CWnd* pParent = NULL);   // ��׼���캯��
    CLanguageDialog(CButton* pButton,CTranslateView* pView ,BOOL bIsFront,  CWnd* pParent = NULL);
	virtual ~CLanguageDialog();
    // ���δ���
    CRgn m_rgn;
    // ����ѡ��ť
    CButton* m_pButton;
    // �Ƿ�Ϊ����ǰ�Ĵ�������
    BOOL m_bIsFront;
    // �Զ����
    CPreButton m_wndAutoBut;
    // ��������
    CPreButton m_wndBut[27];
    // �ɻ���ID
    UINT m_nOldID;

    CLanguageDialog* m_pMutexObject;

    // ����ǰ����ͼ
    CTranslateView* m_pView;
    wchar_t* GetLanguagText(UINT nID);
public:
    
// �Ի�������
	enum { IDD = IDD_TRANSLATEDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnKillFocus(CWnd* pNewWnd);
public:
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
    afx_msg void OnPaint();
    // ����ǰ�����Դ�����
    afx_msg void OnCommand(UINT nID);

    afx_msg void OnSetFocus(CWnd* pOldWnd);
    afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
    afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
};
