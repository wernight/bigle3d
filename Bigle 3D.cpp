// Bigle 3D.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Bigle 3D.h"

#include "StartPP.h"
#include "FondPP.h"
#include "ReliefPP.h"
#include "AboutPP.h"
#include "CreateImgPP.h"
#include <cderr.h>			// Common Dialog Errors

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBigle3DApp

BEGIN_MESSAGE_MAP(CBigle3DApp, CWinApp)
	//{{AFX_MSG_MAP(CBigle3DApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBigle3DApp construction

CBigle3DApp::CBigle3DApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBigle3DApp object

CBigle3DApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBigle3DApp initialization


/*	FreeImage error handler
	@param fif Format / Plugin responsible for the error 
	@param message Error message
*/
void CBigle3DApp::MyMessageFunc(FREE_IMAGE_FORMAT fif, const char *message)
{
	AfxMessageBox(message, MB_ICONERROR);
}

BOOL CBigle3DApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// call this ONLY when linking with FreeImage as a static library
	//FreeImage_Initialise();

	// initialize your own FreeImage error handler
	FreeImage_SetOutputMessage(MyMessageFunc);

	CStartPP pp1;
	CFondPP pp2;
	CReliefPP pp3;
	CCreateImgPP pp4;
	CAboutPP pp5;
	pp1.m_psp.dwFlags -= PSP_HASHELP;
	pp2.m_psp.dwFlags -= PSP_HASHELP;
	pp3.m_psp.dwFlags -= PSP_HASHELP;
	pp4.m_psp.dwFlags -= PSP_HASHELP;
	pp5.m_psp.dwFlags -= PSP_HASHELP;
	m_ps.AddPage( &pp1 );
	m_ps.AddPage( &pp2 );
	m_ps.AddPage( &pp3 );
	m_ps.AddPage( &pp4 );
	m_ps.AddPage( &pp5 );
	m_ps.SetWizardMode();
	m_pMainWnd = &m_ps;
	int nResponse = (int)m_ps.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	FreeImage_DeInitialise();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

FIBITMAP* CBigle3DApp::LoadFile(CString strFile)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	// check the file signature and deduce its format
	// (the second argument is currently not used by FreeImage)
	fif = FreeImage_GetFileType(strFile, 0);
	if(fif == FIF_UNKNOWN) {
		// no signature ?
		// try to guess the file format from the file extension
		fif = FreeImage_GetFIFFromFilename(strFile);
	}
	// check that the plugin has reading capabilities ...
	if((fif != FIF_UNKNOWN) && FreeImage_FIFSupportsReading(fif)) {
		// ok, let's load the file
		FIBITMAP *dib = FreeImage_Load(fif, strFile, 0);
		// unless a bad file format, we are done !
		return dib;
	}
	return NULL;
}

void CBigle3DApp::ShowOFNError()
{
	TCHAR	szError[256];
	DWORD	nError = CommDlgExtendedError();
	CString	strMsg;

	if (nError == 0)
		return;		// no error

	// Error string
	switch (nError)
	{
	case CDERR_DIALOGFAILURE:
		_tcscpy(szError, _T("The function could not open the dialog box."));
		break;
	case CDERR_FINDRESFAILURE:
		_tcscpy(szError, _T("The function failed to find the desired resource."));
		break;
	case CDERR_INITIALIZATION:
		_tcscpy(szError, _T("The function failed during initialization (probably insufficient memory)."));
		break;
	case CDERR_LOADRESFAILURE:
		_tcscpy(szError, _T("The function failed to load the desired resource."));
		break;
	case CDERR_LOADSTRFAILURE:
		_tcscpy(szError, _T("The function failed to load the desired string."));
		break;
	case CDERR_LOCKRESFAILURE:
		_tcscpy(szError, _T("The function failed to lock the desired resource."));
		break;
	case CDERR_MEMALLOCFAILURE:
		_tcscpy(szError, _T("The function failed to allocate sufficient memory."));
		break;
	case CDERR_MEMLOCKFAILURE:
		_tcscpy(szError, _T("The function failed to lock the desired memory."));
		break;
	case CDERR_NOHINSTANCE:
		_tcscpy(szError, _T("The function was not provided with a valid instance handle (if one was required)."));
		break;
	case CDERR_NOHOOK:
		_tcscpy(szError, _T("The function was not provided with a valid hook function handle (if one was required)."));
		break;
	case CDERR_NOTEMPLATE:
		_tcscpy(szError, _T("The function was not provided with a valid template (if one was required)."));
		break;
	case CDERR_REGISTERMSGFAIL:
		_tcscpy(szError, _T("The function failed to successfully register a window message."));
		break;
	case CDERR_STRUCTSIZE:
		_tcscpy(szError, _T("The function was provided with an invalid structure size."));
		break;
	case FNERR_BUFFERTOOSMALL:
		_tcscpy(szError, _T("Buffer too small."));
		break;
	case FNERR_INVALIDFILENAME:
		_tcscpy(szError, _T("A file name is invalid."));
		break;
	case FNERR_SUBCLASSFAILURE:
		_tcscpy(szError, _T("An attempt to subclass a list box failed because sufficient memory was not available."));
		break;
	default:
		_tcscpy(szError, _T("Unknown."));
	}

	strMsg.Format("The common dialog box function failed.\nError %d: %s", nError, szError);
	AfxMessageBox(strMsg, 0, 0);
}
