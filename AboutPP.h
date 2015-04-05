#if !defined(AFX_ABOUTPP_H__C29EC213_3B25_11D4_B5FF_444553540000__INCLUDED_)
#define AFX_ABOUTPP_H__C29EC213_3B25_11D4_B5FF_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AboutPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAboutPP dialog

class CAboutPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CAboutPP)

// Construction
public:
	CAboutPP();
	~CAboutPP();

// Dialog Data
	//{{AFX_DATA(CAboutPP)
	enum { IDD = IDD_ABOUTBOX };
	CString	m_strEMail;
	CString	m_strICQ;
	CString	m_strWeb;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAboutPP)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAboutPP)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CFont fontLien;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ABOUTPP_H__C29EC213_3B25_11D4_B5FF_444553540000__INCLUDED_)
