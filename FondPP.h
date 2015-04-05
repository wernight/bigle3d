#if !defined(AFX_FONDPP_H__C29EC210_3B25_11D4_B5FF_444553540000__INCLUDED_)
#define AFX_FONDPP_H__C29EC210_3B25_11D4_B5FF_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FondPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFondPP dialog

class CFondPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CFondPP)

// Construction
public:
	CFondPP();
	~CFondPP();

// Dialog Data
	//{{AFX_DATA(CFondPP)
	enum { IDD = IDD_FOND };
	CString	m_strFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CFondPP)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CFondPP)
	afx_msg void OnChange();
	afx_msg void OnFileButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FONDPP_H__C29EC210_3B25_11D4_B5FF_444553540000__INCLUDED_)
