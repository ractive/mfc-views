#if !defined(AFX_NEWVIEWDLG_H__A8FAE155_0ADA_4FF2_82FD_FAD284041609__INCLUDED_)
#define AFX_NEWVIEWDLG_H__A8FAE155_0ADA_4FF2_82FD_FAD284041609__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NewViewDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNewViewDlg dialog

class CNewViewDlg : public CDialog
{
// Construction
public:
	CRuntimeClass * m_pRuntimeClass;
	CNewViewDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNewViewDlg)
	enum { IDD = IDD_NEWVIEW };
	CListBox	m_ViewList;
	UINT	m_nPosition;
	CString	m_sTabLabel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNewViewDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNewViewDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NEWVIEWDLG_H__A8FAE155_0ADA_4FF2_82FD_FAD284041609__INCLUDED_)
