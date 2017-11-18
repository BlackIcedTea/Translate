// TranslateView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Translate.h"
#include "TranslateView.h"
#include "TranslateDlg.h"
CEdit* g_pEdit;
// ��Ҫ������ַ���
CString CTranslateView::strText;
// ��Ҫ�����ַ���������
CString  CTranslateView::strPreLanguage;
// utf8 ת Unicode
CString UTF8ToUnicode(char* UTF8);
// ��������
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream);


// CTranslateView

IMPLEMENT_DYNCREATE(CTranslateView, CFormView)
CTranslateView::CTranslateView() : CFormView(CTranslateView::IDD)
{

	// ��ʾ������
	m_strTitle = _T("");
	// ��Ҫ���������
	m_strLanguage = _T("");
	// �Ƿ������������
	m_bIsWrite = FALSE;

	// ��Ҫ������ַ���
	CTranslateView::strText = _T("");
	// ��Ҫ�����ַ���������
	CTranslateView::strPreLanguage = _T("");




}

CTranslateView::CTranslateView(CString Title, CString Language, BOOL IsWrite) : CFormView(CTranslateView::IDD)
{
	// ��ʾ������
	m_strTitle = Title;
	// ��Ҫ���������
	m_strLanguage = Language;
	// �Ƿ������������
	m_bIsWrite = IsWrite;

	// ��Ҫ������ַ���
	CTranslateView::strText = _T("");
	// ��Ҫ�����ַ���������
	CTranslateView::strPreLanguage = _T("");




}

CTranslateView::~CTranslateView()
{
}

void CTranslateView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTranslateView, CFormView)
END_MESSAGE_MAP()


// CTranslateView ���

#ifdef _DEBUG
void CTranslateView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CTranslateView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTranslateView ��Ϣ�������

BOOL CTranslateView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CTranslateView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// ���ñ���
	GetDlgItem(IDC_TYPE)->SetWindowText(m_strTitle);
	// ��EDIT���浽ȫ�ֱ�����
	g_pEdit = (CEdit*)GetDlgItem(IDC_EDIT);
	// ����EDIT�Ƿ��������
	g_pEdit->SetReadOnly(!m_bIsWrite);
}
// ���ֽ��ַ���ת���ֽ��ַ���(ʹ�����ڴ����Ҫ�ͷ�)
char* WToM(CString strWText)
{
	// ���ڱ�������ĵ�ַ
	char* strMText = NULL;
	// ��ȡת������Ҫ�����ֽ�
	int len = WideCharToMultiByte(CP_ACP, 0, strWText, wcslen(strWText), NULL, 0, NULL, NULL);
	// ����ռ�
	strMText = (char*)malloc(len + 1);
	// ����ڴ�
	memset(strMText, 0, len + 1);
	// ת���ַ���
	len = WideCharToMultiByte(CP_ACP, 0, strWText, wcslen(strWText), strMText, len, NULL, NULL);
	// �����ַ�����β
	strMText[len] = 0;
	return strMText;
}
size_t CTranslateView::g_f_wctou8(char * dest_str, const wchar_t src_wchar)
{
	int count_bytes = 0;
	wchar_t byte_one = 0, byte_other = 0x3f; // ����λ����������ȡλֵ0x3f--->00111111
	unsigned char utf_one = 0, utf_other = 0x80; // ����"λ��"�ñ�UTF-8����0x80--->1000000
	wchar_t tmp_wchar = L'0'; // ���ڿ��ַ�λ����ȡ��λ��(����λ)
	unsigned char tmp_char = L'0';
	if (!src_wchar)//
		return (size_t)-1;
	for (;;) // ����ֽ����г���
	{
		if (src_wchar <= 0x7f){ // <=01111111
			count_bytes = 1; // ASCII�ַ�: 0xxxxxxx( ~ 01111111)
			byte_one = 0x7f; // ����λ������, ��ȡ��Чλֵ, ��ͬ
			utf_one = 0x0;
			break;
		}
		if ((src_wchar > 0x7f) && (src_wchar <= 0x7ff)){ // <=0111,11111111
			count_bytes = 2; // 110xxxxx 10xxxxxx[1](����λ, ��дΪ*1)
			byte_one = 0x1f; // 00011111, ������(1λ�������ݼ�)
			utf_one = 0xc0; // 11000000
			break;
		}
		if ((src_wchar > 0x7ff) && (src_wchar <= 0xffff)){ //0111,11111111<=11111111,11111111
			count_bytes = 3; // 1110xxxx 10xxxxxx[2](MaxBits: 16*1)
			byte_one = 0xf; // 00001111
			utf_one = 0xe0; // 11100000
			break;
		}
		if ((src_wchar > 0xffff) && (src_wchar <= 0x1fffff)){ //��UCS-4��֧��..
			count_bytes = 4; // 11110xxx 10xxxxxx[3](MaxBits: 21*1)
			byte_one = 0x7; // 00000111
			utf_one = 0xf0; // 11110000
			break;
		}
		if ((src_wchar > 0x1fffff) && (src_wchar <= 0x3ffffff)){
			count_bytes = 5; // 111110xx 10xxxxxx[4](MaxBits: 26*1)
			byte_one = 0x3; // 00000011
			utf_one = 0xf8; // 11111000
			break;
		}
		if ((src_wchar > 0x3ffffff) && (src_wchar <= 0x7fffffff)){
			count_bytes = 6; // 1111110x 10xxxxxx[5](MaxBits: 31*1)
			byte_one = 0x1; // 00000001
			utf_one = 0xfc; // 11111100
			break;
		}
		return (size_t)-1; // ���ϽԲ�������Ϊ�Ƿ�����
	}
	// ���¼�����ȡ���ֽ��е���Ӧλ, ������ΪUTF-8����ĸ����ֽ�
	tmp_wchar = src_wchar;
	for (int i = count_bytes; i > 1; i--)
	{ // һ�����ַ��Ķ��ֽڽ���ֵ
		tmp_char = (unsigned char)(tmp_wchar & byte_other);///��λ��byte_other 00111111
		dest_str[i - 1] = (tmp_char | utf_other);/// ��ǰ���----����
		tmp_wchar >>= 6;//����λ
	}
	//���ʱ��i=1
	//��UTF-8��һ���ֽ�λ����
	//��һ���ֽڵĿ�ͷ"1"����Ŀ�������������ֽڵ���Ŀ
	tmp_char = (unsigned char)(tmp_wchar & byte_one);//�������渽ֵ��������Чλ����
	dest_str[0] = (tmp_char | utf_one);//�������渽ֵ����1�ĸ���
	// λֵ��ȡ����__End!
	return count_bytes;
}
int UniToUTF8(CString strUnicode, char *szUtf8)
{
	//MessageBox(strUnicode);
	int ilen = WideCharToMultiByte(CP_UTF8, 0, (LPCTSTR)strUnicode, -1, NULL, 0, NULL, NULL);
	char *szUtf8Temp = new char[ilen + 1];
	memset(szUtf8Temp, 0, ilen + 1);
	WideCharToMultiByte(CP_UTF8, 0, (LPCTSTR)strUnicode, -1, szUtf8Temp, ilen, NULL, NULL);
	//size_t a = strlen(szUtf8Temp);
	sprintf(szUtf8, "%s", szUtf8Temp);// 
	delete[] szUtf8Temp;
	return ilen;
}


// ���벢��ʾ��EDIT��
void CTranslateView::Translate()
{

	// ��Ҫ������ı�
	char* pstrTextstrM = WToM(CTranslateView::strText);

	char pstrTextM[4096] = { 0 };

	UniToUTF8(CTranslateView::strText, pstrTextM);


	// ��������ı�����
	char* pstrPreLanguageM = WToM(CTranslateView::strPreLanguage);
	// ��Ҫ�����ʲô����
	char* pstrLanguageM = WToM(m_strLanguage);

	// �û���Ϣ�ַ���
	char szInfo[4096] = { 0 }; // �����ܵ���Ϣ
	// ��ʱ�����ַ���
	unsigned  char  md[16] = { 0 };
	// ���ܺ���ַ���
	char szkey[36] = { 0 }, tmp[3] = { 0 };
	int salt = rand() % 0xFFFF;
	// �������
	sprintf(szInfo, "%s%s%d%s", "20160206000011344", pstrTextM, salt, "8I6r6BYVO4uH5GOnvR38");

	// ����ժҪ

	md5_state_s md5data = { 0 };
	md5_init(&md5data);
	md5_append(&md5data, (md5_byte_t*)szInfo, strlen(szInfo));
	md5_finish(&md5data, md);
	//MD5((unsigned char*)szInfo, strlen (szInfo),md);
	// ���м���ת��
	for (int i = 0; i < 16; i++)
	{
		sprintf(tmp, "%2.2x", md[i]);
		strcat(szkey, tmp);
	}
	// ����URL�ַ���
	CStringA strURL;
	strURL.Format("http://api.fanyi.baidu.com/api/trans/vip/translate?q=%s&from=%s&to=%s&appid=%s&salt=%d&sign=%s", pstrTextstrM, pstrPreLanguageM, pstrLanguageM, "20160206000011344", salt, szkey);
	// ׷�ӵ���β
	// �����ַ���
	// �ͷ��ڴ�
	//free(pstrTextM);
	free(pstrPreLanguageM);
	free(pstrLanguageM);

	free(pstrTextstrM);

	HRESULT hRef = m_pHttpReq.CreateInstance(__uuidof(WinHttpRequest));
	if (FAILED(hRef))
	{
		AfxMessageBox(_T("��Ϣ�����ӿڴ���ʧ��!"));
		return;
	}

	hRef = m_pHttpReq->Open(_T("GET"), strURL.AllocSysString());
	if (FAILED(hRef))
		return;

	hRef = m_pHttpReq->Send();
	if (FAILED(hRef))
		return;

	// �����ַ���
	CString strRef = m_pHttpReq->ResponseText;

	
	USES_CONVERSION;
	char* pszRefData = W2A(strRef);

	write_data(pszRefData, 0, strlen(pszRefData),NULL);
}


// ��������
size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{

	// ���붯̬�ռ�
	char* szBody = (char*)malloc(nmemb + 1);
	memset(szBody, 0, nmemb + 1);
	// �����ַ���
	strncpy(szBody, (char*)ptr, nmemb);
	// ���ַ�����β
	szBody[nmemb] = 0;

	// JSON����������
	cJSON * pJson = cJSON_Parse(szBody);
	if (NULL == pJson)
	{
		// parse faild, return
		return 0;
	}
	// ��ȡһ����Ϣ
	cJSON * pSub = cJSON_GetObjectItem(pJson, "trans_result");
	if (NULL != pSub)
	{
		// ��ȡ����
		cJSON* pArray = cJSON_GetArrayItem(pSub, 0);
		if (NULL != pArray)
		{
			// ��ȡ�����еĳ�Ա
			cJSON * pValue = cJSON_GetObjectItem(pArray, "dst");
			if (NULL != pValue)
			{
				CString str = UTF8ToUnicode(pValue->valuestring);
				// ��ӵ�EDIT����
				g_pEdit->SetWindowText(str);
			}
		}
	}

	// �ͷ��ڴ�Body
	free(szBody);
	return size;
}

// utf8 ת Unicode
CString UTF8ToUnicode(char* UTF8)
{

	DWORD dwUnicodeLen;        //ת����Unicode�ĳ���
	TCHAR *pwText;            //����Unicode��ָ��
	CString strUnicode;        //����ֵ
	//���ת����ĳ��ȣ��������ڴ�
	dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, NULL, 0);
	pwText = new TCHAR[dwUnicodeLen];
	if (!pwText)
	{
		return strUnicode;
	}
	//תΪUnicode
	MultiByteToWideChar(CP_UTF8, 0, UTF8, -1, pwText, dwUnicodeLen);
	//תΪCString
	strUnicode.Format(_T("%s"), pwText);
	//����ڴ�
	delete[]pwText;
	//����ת���õ�Unicode�ִ�
	return strUnicode;
}

