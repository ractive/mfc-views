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


// ViewBar.cpp: implementation of the CViewBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "ViewBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CViewBar::CViewBar()
{
	m_pView = NULL;
}

CViewBar::~CViewBar()
{


}

BEGIN_MESSAGE_MAP(CViewBar, baseClass)
	//{{AFX_MSG_MAP(CMyBar)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CViewBar::CreateView(CRuntimeClass *pViewClass, CCreateContext *pContext, UINT nID)
{
#ifdef _DEBUG
	ASSERT_VALID(this);
	ASSERT(pViewClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)));
	ASSERT(AfxIsValidAddress(pViewClass, sizeof(CRuntimeClass), FALSE));
#endif

	BOOL bSendInitialUpdate = FALSE;

	CWnd* pWnd;
	TRY
	{
		// Create the view object dynamically
		pWnd = (CWnd*)pViewClass->CreateObject();
		if (pWnd == NULL)
			AfxThrowMemoryException();
	}
	CATCH_ALL(e)
	{
		TRACE0("Out of memory creating a splitter pane.\n");
		// Note: DELETE_EXCEPTION(e) not required
		return FALSE;
	}
	END_CATCH_ALL

	ASSERT_KINDOF(CWnd, pWnd);
	ASSERT(pWnd->m_hWnd == NULL);       // not yet created

	DWORD dwStyle = AFX_WS_DEFAULT_VIEW;
	dwStyle |= WS_CHILD | WS_VISIBLE;
	CRect rect(0, 0, 0, 0);

	// Now we can create the view window
	if (!pWnd->Create(NULL, NULL, dwStyle, rect, this, nID, pContext))
	{
		TRACE0("Warning: couldn't create client pane for splitter.\n");
			// pWnd will be cleaned up by PostNcDestroy
		return FALSE;
	}

	//SetParent(GetParentFrame());

	SetOwner(AfxGetMainWnd());
	
	m_pView = (CView *)pWnd;

	return TRUE;
}

void CViewBar::OnSize(UINT nType, int cx, int cy) 
{
	baseClass::OnSize(nType, cx, cy);

	// Move the view if it's already created
	if (m_pView->GetSafeHwnd()) {
		CRect rc;

		GetClientRect(rc);
		//m_pView->SetWindowPos(NULL, rc.left, rc.top, rc.Width(), rc.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
		m_pView->MoveWindow(rc);
	}
}

CView * CViewBar::GetView()
{
	return m_pView;
}

BOOL CViewBar::CaptionHitTest(CPoint point)
{
    CRect rcBar, rcClient;
    GetWindowRect(rcBar);
	GetClientRect(rcClient);
	ClientToScreen(rcClient);

    if (!IsFloating()) {
		if (IsHorzDocked()) {
		
		}
		else if (IsVertDocked()) {
			rcBar.bottom = rcClient.top;

			if (rcBar.PtInRect(point)) {
				return TRUE;
			}
		}
	}

	return FALSE;
}

void CViewBar::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if (CaptionHitTest(point)) {
		CMenu menu;
		menu.LoadMenu(IDR_BARS);

		menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, m_pDockSite);
		return;
	}

	// The treeview does not receive the WM_CONTEXTMENU message any more (why?)
	// We just send it to the destination window (again?)
	pWnd->SendMessage(WM_CONTEXTMENU, (WPARAM)pWnd->m_hWnd, MAKELPARAM(point.x, point.y));

	baseClass::OnContextMenu(pWnd, point);
}

BOOL CViewBar::IsActive()
{
    CWnd* pFocus = GetFocus();

    return (pFocus->GetSafeHwnd() && IsChild(pFocus));
}



