// Bigle 3D.h : main header file for the BIGLE 3D application
//

#if !defined(AFX_BIGLE3D_H__C29EC205_3B25_11D4_B5FF_444553540000__INCLUDED_)
#define AFX_BIGLE3D_H__C29EC205_3B25_11D4_B5FF_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBigle3DApp:
// See Bigle 3D.cpp for the implementation of this class
//

class CBigle3DApp : public CWinApp
{
public:
	FIBITMAP* LoadFile(CString strFile);
	void ShowOFNError();

	CBigle3DApp();
	CString m_strFondFile;
	CString m_strReliefFile;
	int m_nProfondeurMax;
	CPropertySheet m_ps;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBigle3DApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	static void MyMessageFunc(FREE_IMAGE_FORMAT fif, const char *message);

	//{{AFX_MSG(CBigle3DApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BIGLE3D_H__C29EC205_3B25_11D4_B5FF_444553540000__INCLUDED_)
