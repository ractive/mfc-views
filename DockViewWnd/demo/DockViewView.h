// DockViewView.h : interface of the CDockViewView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOCKVIEWVIEW_H__0216FFA2_F373_4AE9_84EF_700DDC3AB5EA__INCLUDED_)
#define AFX_DOCKVIEWVIEW_H__0216FFA2_F373_4AE9_84EF_700DDC3AB5EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CDockViewView : public CView
{
protected: // create from serialization only
	CDockViewView();
	DECLARE_DYNCREATE(CDockViewView)

// Attributes
public:
	CDockViewDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDockViewView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDockViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDockViewView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DockViewView.cpp
inline CDockViewDoc* CDockViewView::GetDocument()
   { return (CDockViewDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKVIEWVIEW_H__0216FFA2_F373_4AE9_84EF_700DDC3AB5EA__INCLUDED_)
