#if !defined(AFX_RELIEFPP_H__C29EC211_3B25_11D4_B5FF_444553540000__INCLUDED_)
#define AFX_RELIEFPP_H__C29EC211_3B25_11D4_B5FF_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ReliefPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CReliefPP dialog

class CReliefPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CReliefPP)

// Construction
public:
	CReliefPP();
	~CReliefPP();

// Dialog Data
	//{{AFX_DATA(CReliefPP)
	enum { IDD = IDD_RELIEF };
	CString	m_strFile;
	UINT	m_nProfondeurMax;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CReliefPP)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CReliefPP)
	afx_msg void OnChange();
	afx_msg void OnFileButton();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELIEFPP_H__C29EC211_3B25_11D4_B5FF_444553540000__INCLUDED_)
