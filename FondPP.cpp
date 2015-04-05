// FondPP.cpp : implementation file
//

#include "stdafx.h"
#include "Bigle 3D.h"
#include "FondPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBigle3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFondPP property page

IMPLEMENT_DYNCREATE(CFondPP, CPropertyPage)

CFondPP::CFondPP() : CPropertyPage(CFondPP::IDD)
{
	//{{AFX_DATA_INIT(CFondPP)
#ifdef _DEBUG
	m_strFile = _T("I:\\Mes Projets\\Bigle 3D\\Install\\Fonds\\Point vert foncé 114x800.png");
#else
	m_strFile = _T("");
#endif
	//}}AFX_DATA_INIT
}

CFondPP::~CFondPP()
{
}

void CFondPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFondPP)
	DDX_Text(pDX, IDC_FILE_EDIT, m_strFile);
	DDV_MaxChars(pDX, m_strFile, MAX_PATH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFondPP, CPropertyPage)
	//{{AFX_MSG_MAP(CFondPP)
	ON_EN_CHANGE(IDC_FILE_EDIT, OnChange)
	ON_BN_CLICKED(IDC_FILE_BUTTON, OnFileButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFondPP message handlers

BOOL CFondPP::OnSetActive() 
{
	OnChange();
	
	return CPropertyPage::OnSetActive();
}

void CFondPP::OnChange() 
{
	UpdateData(TRUE);

	WIN32_FIND_DATA	fd;
	HANDLE		hFind;

	// Check si l'img existe
	hFind = FindFirstFile(m_strFile, &fd);

	// Set "Next" button enabled state
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		theApp.m_ps.SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );
		theApp.m_strFondFile = m_strFile;
	}
	else
		theApp.m_ps.SetWizardButtons( PSWIZB_BACK );
}

void CFondPP::OnFileButton() 
{
	const char szFilters[] = "\
All Images Files|*.bmp;*.jpg;*.pbm;*.pcd;*.pcx;*.pgm;*.png;*.ppm;*.res;*.tif;*.tiff|\
Windows / OS/2 Bitmap  (*.bmp)|*.bmp|\
JPEG/JIF (*.jpg)|*.jpg|\
Portable Bitmap (*.pbm)|*.pbm|\
Kodak PhotoCD (*.pcd)|*.pcd|\
PCX (*.pcx)|*.pcx|\
Portable Greymap (*.pgm)|*.pgm|\
Portable Network Graphics (*.png)|*.png|\
Portable Pixmap (*.ppm)|*.ppm|\
Sun Rasterfile (*.ras)|*.ras|\
Targa (*.tga)|*.tga|\
TIFF (*.tif,*.tiff)|*.tif;*.tiff|\
All files (*.*)|*.*||";

	if (!UpdateData(TRUE))
		return;

	// Demande le fichier
	CFileDialog	dlgOFN(
		TRUE, 
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER,  
		szFilters,
		this);
    if (dlgOFN.DoModal() == IDOK)
	{
        m_strFile = dlgOFN.GetPathName();
		UpdateData(FALSE);
		OnChange();
	}
	else
		theApp.ShowOFNError();
}
