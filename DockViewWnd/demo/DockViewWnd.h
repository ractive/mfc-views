#if !defined(AFX_DOCKVIEWWND_H__682006F9_81DA_45E3_A5C2_8D79A5698851__INCLUDED_)
#define AFX_DOCKVIEWWND_H__682006F9_81DA_45E3_A5C2_8D79A5698851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DockViewWnd.h : header file
//

class CViewBar;

/////////////////////////////////////////////////////////////////////////////
// CDockViewWnd window

class CDockViewWnd : public CWnd
{
// Construction
public:
	CDockViewWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockViewWnd)
	public:
	virtual BOOL Create(CWnd* pParentWnd, CCreateContext* pContext = NULL, UINT nID = AFX_IDW_PANE_FIRST +64);
	//}}AFX_VIRTUAL

// Implementation
public:
	CViewBar * GetNextBar(POSITION& pos);
	POSITION GetFirstBar();
	virtual ~CDockViewWnd();
	BOOL CreateView(CRuntimeClass *pViewClass);

	// Generated message map functions
protected:
	CWnd * GetActiveView();
	//{{AFX_MSG(CDockViewWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CCreateContext* m_pCreateContext;
	BOOL RegisterAsMDI(LONG fToRegister);

	CMapWordToPtr m_aBars;

	UINT m_uLastID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKVIEWWND_H__682006F9_81DA_45E3_A5C2_8D79A5698851__INCLUDED_)
