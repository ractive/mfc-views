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

// PidlMgr.h: interface for the CPidlMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PIDLMGR_H__D59DE82C_3DE1_4418_A1E7_2709B1132035__INCLUDED_)
#define AFX_PIDLMGR_H__D59DE82C_3DE1_4418_A1E7_2709B1132035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CPidlMgr  
{
public:
	LPITEMIDLIST CopyFirst(const LPITEMIDLIST pidl, short n);
	BOOL GetParentID(LPITEMIDLIST pidl);
	UINT GetCount(LPITEMIDLIST pidl);
	LPITEMIDLIST Copy(LPCITEMIDLIST pidlSource);
	LPITEMIDLIST Concatenate(LPCITEMIDLIST pidl1, LPCITEMIDLIST pidl2);
	UINT GetSize(LPCITEMIDLIST pidl);
	LPITEMIDLIST GetNextItem(LPCITEMIDLIST pidl);

	CPidlMgr(LPMALLOC pMalloc);
	virtual ~CPidlMgr();
private:
	LPMALLOC m_pMalloc;
};

#endif // !defined(AFX_PIDLMGR_H__D59DE82C_3DE1_4418_A1E7_2709B1132035__INCLUDED_)
