/*************************************************************************
                     JAGS
**************************************************************************

Copyright (C) July, 2001 Jean-Pierre Bergamin, james@ractive.ch

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

class CExploTreeView : public CTreeView
{
protected: // create from serialization only
	CExploTreeView();
	DECLARE_DYNCREATE(CExploTreeView)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExploTreeView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void NoItemContextMenu(CWnd * pWnd, CPoint point);
	virtual DROPEFFECT OnDragOver(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual DROPEFFECT OnDragEnter(COleDataObject* pDataObject, DWORD dwKeyState, CPoint point);
	virtual void OnDragLeave();
	virtual BOOL OnDrop(COleDataObject* pDataObject, DROPEFFECT dropEffect, CPoint point);
	virtual DROPEFFECT OnDragScroll(DWORD dwKeyState, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
	BOOL HandleKeyDownMsg(MSG* pMsg);

// Implementation
public:
	CString GetPath(HTREEITEM hTI);
	BOOL OpenFolder(LPCTSTR szPath);
	int GetIcon(LPITEMIDLIST pidl, bool bSelected);
	virtual ~CExploTreeView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	void PIDLTEST(LPITEMIDLIST pidl);
	void ENUMFOLDER(IShellFolder * pFolder, LPCITEMIDLIST pidlParent);
#endif

protected:
	BOOL GetFriendlyName(TCHAR pzDisplayName[_MAX_PATH], LPITEMIDLIST pidl, STRRET * strDispName);
	HTREEITEM AddRootItem(LPCTSTR szPath);
	HTREEITEM m_hOldSelection;
	HTREEITEM m_hMenuItem;
	CEdit * m_pEdit;

// Generated message map functions
protected:
	void RefreshAll();
	void Refresh(HTREEITEM hItem);
	void Expand(HTREEITEM hItem);
	BOOL m_bNewDir;
	BOOL DeleteDir(BOOL bKeepInBin);
	DROPEFFECT GetDropEffect(HTREEITEM hTI, DWORD dwKeyState);
	BOOL HandleFileDrop(HTREEITEM hTI, BOOL bCopy, HDROP hDrop);
	BOOL DoFileTransfer(HTREEITEM hTI, BOOL bForClipboard);
	void ShowContextMenu(IShellFolder * pFolder, LPCITEMIDLIST pidlItem, CPoint point);
	void OpenPidl(const LPITEMIDLIST pidl);
	//{{AFX_MSG(CExploTreeView)
	afx_msg void OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnBeginLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnDeleteErase();
	afx_msg void OnRename();
	afx_msg void OnNewDir();
	afx_msg void OnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CString m_sOldName;
	HTREEITEM m_hItemButton;
	CString m_sDraggedFile;
	enum {InitialScrollWait = 400};
	enum {ScrollRange = 15};
	int m_nScrollWait;


	HRESULT GetSHContextMenu(LPSHELLFOLDER psfFolder, LPCITEMIDLIST localPidl, void** ppCM, int* pcmType);
	HRESULT ProcessCMCommand(LPCONTEXTMENU pCM, UINT idCmdOffset);

	static LRESULT CALLBACK HookWndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
	static LPCONTEXTMENU2 m_pIContext2;
	static WNDPROC m_pOldWndProc; 

	BOOL PidlIsParentOf(LPITEMIDLIST parent, LPITEMIDLIST child);

	BOOL InsertFolder(HTREEITEM hParentItem,IShellFolder* pParentFolder, LPITEMIDLIST pidlParent);
	static int CALLBACK CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort); 
	CPtrList m_ptrList;

	COleDropTarget m_OleDropTarget;


	HACCEL m_hAccel;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXPLOTREEVIEW_H__B633F04B_A914_49EA_B7EB_4E3D264E0D93__INCLUDED_)
