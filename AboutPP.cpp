// AboutPP.cpp : implementation file
//

#include "stdafx.h"
#include "Bigle 3D.h"
#include "AboutPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBigle3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAboutPP property page

IMPLEMENT_DYNCREATE(CAboutPP, CPropertyPage)

CAboutPP::CAboutPP() : CPropertyPage(CAboutPP::IDD)
{
	//{{AFX_DATA_INIT(CAboutPP)
	m_strEMail = _T("werner@beroux.com");
	m_strICQ = _T("14542366");
	m_strWeb = _T("www.beroux.com");
	//}}AFX_DATA_INIT
}

CAboutPP::~CAboutPP()
{
}

void CAboutPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutPP)
	DDX_Text(pDX, IDC_EMAIL_EDIT, m_strEMail);
	DDX_Text(pDX, IDC_ICQ_EDIT, m_strICQ);
	DDX_Text(pDX, IDC_WEB_EDIT, m_strWeb);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAboutPP, CPropertyPage)
	//{{AFX_MSG_MAP(CAboutPP)
	ON_WM_CTLCOLOR()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAboutPP message handlers

BOOL CAboutPP::OnSetActive() 
{
	theApp.m_ps.SetWizardButtons( PSWIZB_BACK | PSWIZB_FINISH );
	
	return CPropertyPage::OnSetActive();
}

BOOL CAboutPP::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Lien
	fontLien.CreateFont(-8, NULL,
						NULL,
						NULL,
						FW_NORMAL, FALSE, TRUE, FALSE,
						DEFAULT_CHARSET,
						OUT_DEFAULT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						DEFAULT_QUALITY,
						DEFAULT_PITCH | FF_SWISS,
						"MS Sans Serif");
	GetDlgItem(IDC_WEB_EDIT)->SetFont(&fontLien, FALSE);
	GetDlgItem(IDC_EMAIL_EDIT)->SetFont(&fontLien, FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CAboutPP::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// Change la couleur
	int nWndID = pWnd->GetDlgCtrlID();
	if (nWndID == IDC_WEB_EDIT || nWndID == IDC_EMAIL_EDIT)
		pDC->SetTextColor(RGB(0,0,255));

	// TODO: Return a different brush if the default is not desired
	return hbr;
}

BOOL CAboutPP::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// Change le curseur
	int nWndID = pWnd->GetDlgCtrlID();
	if (nWndID == IDC_WEB_EDIT || nWndID == IDC_EMAIL_EDIT)
	{
		::SetCursor(AfxGetApp()->LoadCursor(IDC_LIEN_CURSOR));
		return TRUE;
	}
	else
		return CDialog::OnSetCursor(pWnd, nHitTest, message);	
}

BOOL CAboutPP::PreTranslateMessage(MSG* pMsg) 
{
	// Site Web
	if (pMsg->hwnd == GetDlgItem(IDC_WEB_EDIT)->m_hWnd &&
		pMsg->message == WM_LBUTTONDOWN)
		ShellExecute(GetActiveWindow()->m_hWnd,
					 "open",
					 m_strWeb,
					 NULL,
					 NULL,
					 SW_SHOWNORMAL);

	// E-Mail
	if (pMsg->hwnd == GetDlgItem(IDC_EMAIL_EDIT)->m_hWnd &&
		pMsg->message == WM_LBUTTONDOWN)
		ShellExecute(GetActiveWindow()->m_hWnd,
					 "open",
					 "mailto:" + m_strEMail,
					 NULL,
					 NULL,
					 SW_SHOWNORMAL);

	return CDialog::PreTranslateMessage(pMsg);
}

LRESULT CAboutPP::OnWizardBack() 
{
	// Va au début
	theApp.m_ps.SetActivePage( 2 );
	
	return CPropertyPage::OnWizardBack();
}
