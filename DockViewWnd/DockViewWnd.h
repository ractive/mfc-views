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
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CViewBar * GetBar(UINT nBar);
	CView * GetView(UINT nView);
	CViewBar * GetNextBar(POSITION& pos);
	POSITION GetFirstBar();
	virtual ~CDockViewWnd();
	BOOL CreateView(UINT nView, LPCTSTR lpszBarTitle, CRuntimeClass *pViewClass);

	// Generated message map functions
protected:
	CView * GetActiveView();
	//{{AFX_MSG(CDockViewWnd)
	//}}AFX_MSG
	afx_msg void OnInitialUpdate();

	DECLARE_MESSAGE_MAP()
private:
	CCreateContext* m_pCreateContext;
	BOOL RegisterAsMDI(LONG fToRegister);

	CMapWordToPtr m_aBars;
	CMap<int, int, UINT, UINT> m_aPageIDs;

	UINT m_uLastID;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOCKVIEWWND_H__682006F9_81DA_45E3_A5C2_8D79A5698851__INCLUDED_)
