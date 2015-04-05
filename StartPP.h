#if !defined(AFX_STARTPP_H__C29EC212_3B25_11D4_B5FF_444553540000__INCLUDED_)
#define AFX_STARTPP_H__C29EC212_3B25_11D4_B5FF_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StartPP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CStartPP dialog

class CStartPP : public CPropertyPage
{
	DECLARE_DYNCREATE(CStartPP)

// Construction
public:
	CStartPP();
	~CStartPP();

// Dialog Data
	//{{AFX_DATA(CStartPP)
	enum { IDD = IDD_START };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStartPP)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStartPP)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STARTPP_H__C29EC212_3B25_11D4_B5FF_444553540000__INCLUDED_)
