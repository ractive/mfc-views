// ViewBar.h: interface for the CViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWBAR_H__382BB16E_7D59_4F68_9BBE_E5C621AE94CB__INCLUDED_)
#define AFX_VIEWBAR_H__382BB16E_7D59_4F68_9BBE_E5C621AE94CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "scbarcf.h"

class CViewBar : public CSizingControlBarCF  
{
public:
	CViewBar();
	virtual ~CViewBar();

	BOOL CreateView(CRuntimeClass *pViewClass, CCreateContext *pContext, UINT nID);

private:
	CTreeCtrl m_wndChild;
	CFont	m_font;
	CView *m_pView;
	// Generated message map functions
protected:
	//{{AFX_MSG(CMyBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_VIEWBAR_H__382BB16E_7D59_4F68_9BBE_E5C621AE94CB__INCLUDED_)
