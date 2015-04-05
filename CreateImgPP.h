#if !defined(AFX_CREATEIMGPP_H__C29EC20F_3B25_11D4_B5FF_444553540000__INCLUDED_)
#define AFX_CREATEIMGPP_H__C29EC20F_3B25_11D4_B5FF_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CreateImgPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCreateImgPP dialog

class CCreateImgPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CCreateImgPP)

// Construction
public:
	CCreateImgPP();
	~CCreateImgPP();

// Dialog Data
	//{{AFX_DATA(CCreateImgPP)
	enum { IDD = IDD_CREATE_IMG };
	CProgressCtrl	m_ctlProgress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCreateImgPP)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCreateImgPP)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HANDLE DDBToDIB( CBitmap& bitmap, DWORD dwCompression, CPalette* pPal );
	BOOL WriteDIB( LPTSTR szFile, HANDLE hDIB);
	static void OnProgressCallback(int nPercents, void* pParam);
	static UINT ThreadCalc(LPVOID pParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CREATEIMGPP_H__C29EC20F_3B25_11D4_B5FF_444553540000__INCLUDED_)
