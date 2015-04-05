// ReliefPP.cpp : implementation file
//

#include "stdafx.h"
#include "Bigle 3D.h"
#include "ReliefPP.h"
#include "FondPP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBigle3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CReliefPP property page

IMPLEMENT_DYNCREATE(CReliefPP, CPropertyPage)

CReliefPP::CReliefPP() : CPropertyPage(CReliefPP::IDD)
{
	//{{AFX_DATA_INIT(CReliefPP)
#ifdef _DEBUG
	m_strFile = _T("I:\\Mes Projets\\Bigle 3D\\Install\\Reliefs\\Exemple 2.png");
#else
	m_strFile = _T("");
#endif
	m_nProfondeurMax = 30;
	//}}AFX_DATA_INIT
}

CReliefPP::~CReliefPP()
{
}

void CReliefPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CReliefPP)
	DDX_Text(pDX, IDC_FILE_EDIT, m_strFile);
	DDV_MaxChars(pDX, m_strFile, MAX_PATH);
	DDX_Text(pDX, IDC_PROFONDEURMAX_EDIT, m_nProfondeurMax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CReliefPP, CPropertyPage)
	//{{AFX_MSG_MAP(CReliefPP)
	ON_EN_CHANGE(IDC_FILE_EDIT, OnChange)
	ON_EN_CHANGE(IDC_PROFONDEURMAX_EDIT, OnChange)
	ON_BN_CLICKED(IDC_FILE_BUTTON, OnFileButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CReliefPP message handlers

BOOL CReliefPP::OnSetActive() 
{
	OnChange();
	
	return CPropertyPage::OnSetActive();
}

void CReliefPP::OnChange() 
{
	FIBITMAP *dibFond;
	FIBITMAP *dibRelief;
	WIN32_FIND_DATA	fd;
	HANDLE		hFind;

	UpdateData(TRUE);

	// Check si l'img existe
	hFind = FindFirstFile(m_strFile, &fd);

	// Disable "Next" button ?
	if (hFind != INVALID_HANDLE_VALUE)
		FindClose(hFind);
	else
	{
		theApp.m_ps.SetWizardButtons( PSWIZB_BACK );
		return;
	}
	
	// Charge l'img avec relief
	dibFond = theApp.LoadFile( theApp.m_strFondFile );
	dibRelief = theApp.LoadFile( theApp.m_strReliefFile );
	if (FreeImage_GetHeight(dibFond) < FreeImage_GetHeight(dibRelief))
	{
		MessageBox("L'image contenant les informations de reliefs doit-être moins haute que le fond.", "Bigle 3D", MB_ICONWARNING);
		theApp.m_ps.SetWizardButtons( PSWIZB_BACK );
	}
	else if (m_nProfondeurMax > 0 &&
			 m_nProfondeurMax <= (UINT) FreeImage_GetWidth(dibFond) )
	{
		theApp.m_ps.SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );
		theApp.m_strReliefFile = m_strFile;
		theApp.m_nProfondeurMax = m_nProfondeurMax;
	}
	else
		theApp.m_ps.SetWizardButtons( PSWIZB_BACK );
	FreeImage_Unload(dibFond);
	FreeImage_Unload(dibRelief);
}

void CReliefPP::OnFileButton() 
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
