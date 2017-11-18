#pragma once


// #import "c:\\windows\system32\\winhttp.dll" no_namespace 
#import "c:\\windows\system32\\winhttpcom.dll" no_namespace 

// CTranslateView ������ͼ

class CTranslateView : public CFormView
{
	DECLARE_DYNCREATE(CTranslateView)

public:
    CTranslateView( );
	CTranslateView( CString Title,CString Language,BOOL IsWrite = FALSE);           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTranslateView();
public:
    // ���벢��ʾ��EDIT��
    void Translate( );
public:

    // ��ʾ������ı���
    CString m_strTitle;
    // ��Ҫ���������
    CString m_strLanguage;
    // �Ƿ������������
    BOOL m_bIsWrite;
public:
    // ��Ҫ������ַ���
    static CString strText;
    // ��Ҫ�����ַ���������
    static CString strPreLanguage;
    
    size_t g_f_wctou8(char * dest_str, const wchar_t src_wchar);
public:
	enum { IDD = IDD_TEXT };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
    virtual void OnInitialUpdate();

private:
	IWinHttpRequestPtr m_pHttpReq;

};


