// StartPP.cpp : implementation file
//

#include "stdafx.h"
#include "Bigle 3D.h"
#include "StartPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBigle3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CStartPP property page

IMPLEMENT_DYNCREATE(CStartPP, CPropertyPage)

CStartPP::CStartPP() : CPropertyPage(CStartPP::IDD)
{
	//{{AFX_DATA_INIT(CStartPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CStartPP::~CStartPP()
{
}

void CStartPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStartPP)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CStartPP, CPropertyPage)
	//{{AFX_MSG_MAP(CStartPP)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStartPP message handlers

BOOL CStartPP::OnSetActive() 
{
	theApp.m_ps.SetWizardButtons( PSWIZB_NEXT );
	
	return CPropertyPage::OnSetActive();
}
