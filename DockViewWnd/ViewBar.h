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


// ViewBar.h: interface for the CViewBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEWBAR_H__382BB16E_7D59_4F68_9BBE_E5C621AE94CB__INCLUDED_)
#define AFX_VIEWBAR_H__382BB16E_7D59_4F68_9BBE_E5C621AE94CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define baseClass CSizingControlBarCF

class CViewBar : public baseClass
{
public:
	BOOL IsActive();
	CView * GetView();
	CViewBar();
	virtual ~CViewBar();

	BOOL CreateView(CRuntimeClass *pViewClass, CCreateContext *pContext, UINT nID);

private:
	CView *m_pView;

	// Generated message map functions
protected:
	BOOL CaptionHitTest(CPoint point);
	//{{AFX_MSG(CMyBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

#endif // !defined(AFX_VIEWBAR_H__382BB16E_7D59_4F68_9BBE_E5C621AE94CB__INCLUDED_)
