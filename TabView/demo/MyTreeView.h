#if !defined(AFX_MYTREEVIEW_H__425A3F70_F967_4245_9CFC_3ACE05B6C88F__INCLUDED_)
#define AFX_MYTREEVIEW_H__425A3F70_F967_4245_9CFC_3ACE05B6C88F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTreeView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView view

class CMyTreeView : public CTreeView
{
protected:
	CMyTreeView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CMyTreeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyTreeView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMyTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	void InsertUrl(HTREEITEM hParent, LPCTSTR lpszUrl);
	//{{AFX_MSG(CMyTreeView)
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CImageList m_ImageList;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTREEVIEW_H__425A3F70_F967_4245_9CFC_3ACE05B6C88F__INCLUDED_)
