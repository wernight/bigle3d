// CreateImgPP.cpp : implementation file
//

#include "stdafx.h"
#include "Bigle 3D.h"
#include "CreateImgPP.h"
#include "FondPP.h"
#include "ReliefPP.h"
#include "Stereogen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CBigle3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCreateImgPP property page

IMPLEMENT_DYNCREATE(CCreateImgPP, CPropertyPage)

CCreateImgPP::CCreateImgPP() : CPropertyPage(CCreateImgPP::IDD)
{
	//{{AFX_DATA_INIT(CCreateImgPP)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCreateImgPP::~CCreateImgPP()
{
}

void CCreateImgPP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCreateImgPP)
	DDX_Control(pDX, IDC_PROGRESS1, m_ctlProgress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCreateImgPP, CPropertyPage)
	//{{AFX_MSG_MAP(CCreateImgPP)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCreateImgPP message handlers

BOOL CCreateImgPP::OnSetActive() 
{
	// Enlève le "Next"
	theApp.m_ps.SetWizardButtons( 0 );
	
	// 0% de progression
	m_ctlProgress.SetPos( 0 );

	// Lance le calcul
	AfxBeginThread(ThreadCalc, this);
	
	return CPropertyPage::OnSetActive();
}

// DDBToDIB             - Creates a DIB from a DDB
// bitmap               - Device dependent bitmap
// dwCompression        - Type of compression - see BITMAPINFOHEADER
// pPal                 - Logical palette
HANDLE CCreateImgPP::DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal )
{
	BITMAP                  bm;
	BITMAPINFOHEADER        bi;
	LPBITMAPINFOHEADER      lpbi;
	DWORD                   dwLen;
	HANDLE                  hDIB;
	HANDLE                  handle;
	HDC                     hDC;
	HPALETTE                hPal;


	ASSERT( bitmap.GetSafeHandle() );

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	// If a palette has not been supplied use defaul palette
	hPal = (HPALETTE) pPal->GetSafeHandle();
	if (hPal==NULL)
		hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	bitmap.GetObject(sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize               = sizeof(BITMAPINFOHEADER);
	bi.biWidth              = bm.bmWidth;
	bi.biHeight             = bm.bmHeight;
	bi.biPlanes             = 1;
	bi.biBitCount           = bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression        = dwCompression;
	bi.biSizeImage          = 0;
	bi.biXPelsPerMeter      = 0;
	bi.biYPelsPerMeter      = 0;
	bi.biClrUsed            = 0;
	bi.biClrImportant       = 0;

	// Compute the size of the  infoheader and the color table
	int nColors = 0;
	if(bi.biBitCount <= 8)
		nColors = (1 << bi.biBitCount);
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = ::GetDC(NULL);
	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, (HBITMAP)bitmap.GetSafeHandle(), 0L, (DWORD)bi.biHeight,
				   (LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
									   * bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else
	{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, (HBITMAP)bitmap.GetSafeHandle(),
						   0L,                             // Start scan line
						   (DWORD)bi.biHeight,             // # of scan lines
						   (LPBYTE)lpbi                    // address for bitmap bits
						   + (bi.biSize + nColors * sizeof(RGBQUAD)),
						   (LPBITMAPINFO)lpbi,             // address of bitmapinfo
						   (DWORD)DIB_RGB_COLORS);         // Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);

		SelectPalette(hDC,hPal,FALSE);
		::ReleaseDC(NULL,hDC);
		return NULL;
	}

	// we'll force this here, because GetDIBits clears these to 0 
	lpbi->biClrUsed = nColors; 
	lpbi->biClrImportant = nColors; 

	SelectPalette(hDC,hPal,FALSE);
	::ReleaseDC(NULL,hDC);
	return hDIB;
}

// WriteDIB		- Writes a DIB to file
// Returns		- TRUE on success
// szFile		- Name of file to write to
// hDIB			- Handle of the DIB
BOOL CCreateImgPP::WriteDIB( LPTSTR szFile, HANDLE hDIB)
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

	// Fill in the fields of the file header 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= (DWORD) GlobalSize(hDIB) + sizeof( hdr );
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	if (lpbi->biBitCount > 0 && lpbi->biBitCount <= 8)
        hdr.bfOffBits = (DWORD)(sizeof(hdr) + lpbi->biSize + 
						(1 << lpbi->biBitCount) * sizeof(RGBQUAD));
	else
	{
		unsigned long cmapsize = 0;

		switch (lpbi->biBitCount)
		{
		case 16: 
		case 32:
			if (lpbi->biCompression == BI_BITFIELDS)
				cmapsize = 3*sizeof(DWORD);
			break;
		case 24:
			cmapsize = lpbi->biClrUsed*sizeof(RGBQUAD);
			break;
		default:	// no colormap
			break;
		}
		hdr.bfOffBits = (DWORD)(sizeof(hdr) + 
						lpbi->biSize + cmapsize);
	}

	// Write the file header 
	file.Write( &hdr, sizeof(hdr) );

	// Write the DIB header and the bits 
	file.Write( lpbi, (UINT)GlobalSize(hDIB) );

	return TRUE;
}

UINT CCreateImgPP::ThreadCalc(LPVOID pParam)
{
	CCreateImgPP	*pDlg = (CCreateImgPP*) pParam;

	// Generate the stereogram
	CStereogen	stereogen;
	stereogen.SetPatternImage( theApp.m_strFondFile );
	stereogen.SetReliefImage( theApp.m_strReliefFile );
	stereogen.SetDepth( theApp.m_nProfondeurMax );
	stereogen.SetProcessCallback(OnProgressCallback, pDlg);
	FIBITMAP* fiStereogram = stereogen.GenerateStereogram();
	if (fiStereogram == NULL)
	{
		AfxMessageBox(stereogen.GetLastError(), MB_ICONERROR);

		// Next...
		theApp.m_ps.PressButton( PSBTN_NEXT );
		return 0;
	}

	// Demande le nom du fichier où enregistrer
	// Infos pour demander le fichier
	const char szFilters[] = "\
Windows / OS/2 Bitmap  (*.bmp)|*.bmp|\
Portable Network Graphics (*.png)|*.png|\
JPEG (*.jpg, *.jpeg)|*.jpg|\
Targged Image File Format (*.tif,*.tiff)|*.tiff;*.tif|\
All files (*.*)|*.*||";
	CFileDialog	dlgOFN(FALSE, "bmp", NULL, OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_EXPLORER, szFilters, pDlg);
    if (dlgOFN.DoModal() == IDOK)
	{
		// Try to guess the file format from the file extension
		FREE_IMAGE_FORMAT fif;
		if ((fif = FreeImage_GetFIFFromFilename(dlgOFN.GetPathName())) == FIF_UNKNOWN)
			AfxMessageBox(IDS_UNKNOWN_IMAGE_FORMAT, MB_ICONERROR);
		else
		{
			// check that the plugin has sufficient writing and export capabilities ...
			WORD nBPP = FreeImage_GetBPP(fiStereogram);
			if (!FreeImage_FIFSupportsWriting(fif) || !FreeImage_FIFSupportsExportBPP(fif, nBPP))
				AfxMessageBox(IDS_UNSUPPORTED_IMAGE_FORMAT, MB_ICONERROR);
			else
			{
				// ok, we can save the file
				if (!FreeImage_Save(fif, fiStereogram, dlgOFN.GetPathName(), 0))
					AfxMessageBox(IDS_COULD_NOT_SAVE_FILE, MB_ICONERROR);
			}
		}
	}
	else
		theApp.ShowOFNError();

	FreeImage_Unload(fiStereogram);

	// Next...
	theApp.m_ps.PressButton( PSBTN_NEXT );
	return 0;
}

void CCreateImgPP::OnProgressCallback(int nPercents, void* pParam)
{
	CCreateImgPP	*pDlg = (CCreateImgPP*) pParam;
	pDlg->m_ctlProgress.SetPos( nPercents );
}
