/*************************************************************************
                     LaPlaya
**************************************************************************

Copyright (C) June, 2001 Jean-Pierre Bergamin, james@ractive.ch

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
***************************************************************************/

// ExploTreeView.h : interface of the CExploTreeView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXPLOTREEVIEW_H__B633F04B_A914_49EA_B7EB_4E3D264E0D93__INCLUDED_)
#define AFX_EXPLOTREEVIEW_H__B633F04B_A914_49EA_B7EB_4E3D264E0D93__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLaPlayaDoc;

class CExploTreeView : public CTreeView
{
protected: // create from serialization only
	CExploTreeView();
	DECLARE_DYNCREATE(CExploTreeView)

// Attributes
public:
	CLaPlayaDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExploTreeView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL OpenFolder(LPCTSTR szPath);
	int GetIcon(LPITEMIDLIST pidl, bool bSelected);
	virtual ~CExploTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL GetFriendlyName(TCHAR pzDisplayName[_MAX_PATH], LPITEMIDLIST pidl, STRRET * strDispName);

// Generated message map functions
protected:
	void OpenPidl(const LPITEMIDLIST pidl);
	//{{AFX_MSG(CExploTreeView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	BOOL PidlIsParentOf(LPITEMIDLIST parent, LPITEMIDLIST child);
	void PIDLTEST(LPITEMIDLIST pidl);

	BOOL InsertFolder(HTREEITEM hParentItem,IShellFolder* pParentFolder, LPITEMIDLIST pidlParent);
	BOOL InitializeTree();
	BOOL m_bInitialized;
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort); 
	CPtrList m_ptrList;
};

#ifndef _DEBUG  // debug version in ExploTreeView.cpp
inline CLaPlayaDoc* CExploTreeView::GetDocument()
   { return (CLaPlayaDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLOTREEVIEW_H__B633F04B_A914_49EA_B7EB_4E3D264E0D93__INCLUDED_)
