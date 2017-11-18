
// TranslateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "LanguageDialog.h"
#include "MyButton.h"
#include "TranslateView.h"

// CTranslateDlg �Ի���
class CTranslateDlg : public CDialog
{
// ����
public:
	CTranslateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TRANSLATE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
public:

    // ����ǰ����ͼ
    CTranslateView* m_pFrontView;
    // ��������ͼ
    CTranslateView* m_pArrayView[26];

    CLanguageDialog* m_pFrontLonguage;
    CLanguageDialog* m_pBehindLonguage;

    // ����ǰ����ѡ��ť
    CButton m_wndFront;
    // ��ť����ѡ��
    CButton m_wndBehind;
    
    

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
    virtual BOOL OnInitDialog() ;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    
    afx_msg void OnBnClickedFront();
    afx_msg void OnMove(int x, int y);
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedTranslate();

protected:
    virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
public:
    
    afx_msg void OnBnClickedBehind();
};
