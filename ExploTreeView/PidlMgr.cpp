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

// PidlMgr.cpp: implementation of the CPidlMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PidlMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPidlMgr::CPidlMgr(LPMALLOC pMalloc)
{
	m_pMalloc = pMalloc;
}

CPidlMgr::~CPidlMgr()
{
	if (m_pMalloc) {
		m_pMalloc->Release();
	}
}

LPITEMIDLIST CPidlMgr::Concatenate(LPCITEMIDLIST pidlBase, LPCITEMIDLIST pidlAdd) 
{ 
    if(pidlBase == NULL)
        return NULL;
    if(pidlAdd == NULL)
        return (LPITEMIDLIST)pidlBase;
    
    LPITEMIDLIST pidlNew;

    UINT cb1 = GetSize(pidlBase) - sizeof(pidlBase->mkid.cb);
    UINT cb2 = GetSize(pidlAdd);

    pidlNew = (LPITEMIDLIST)m_pMalloc->Alloc(cb1 + cb2);
    if (pidlNew)
    {
        CopyMemory(pidlNew, pidlBase, cb1);
        CopyMemory(((LPSTR)pidlNew) + cb1, pidlAdd, cb2);
    }
    return pidlNew;

} 

UINT CPidlMgr::GetSize(LPCITEMIDLIST pidl) 
{ 

    UINT cbTotal = 0;
    if (pidl)
    {
        cbTotal += sizeof(pidl->mkid.cb);    // Null terminator
        while (pidl)
        {
            cbTotal += pidl->mkid.cb;
            pidl = GetNextItem(pidl);
        }
    }
    return cbTotal;

} 

LPITEMIDLIST CPidlMgr::Copy(LPCITEMIDLIST pidl) 
{ 
    UINT cb = 0;
	
	// Calculate size of list.
    cb = GetSize(pidl);

    LPITEMIDLIST pidlRet = (LPITEMIDLIST)m_pMalloc->Alloc(cb);
    if (pidlRet)
        CopyMemory(pidlRet, pidl, cb);
    return pidlRet;
}

LPITEMIDLIST CPidlMgr::GetNextItem(LPCITEMIDLIST pidl) 
{ 
   // Check for valid pidl.
   if(pidl == NULL)
      return NULL;

   // Get the size of the specified item identifier. 
   int cb = pidl->mkid.cb; 

   // If the size is zero, it is the end of the list. 
   if (cb == 0) 
      return NULL; 

   // Add cb to pidl (casting to increment by bytes). 
   pidl = (LPITEMIDLIST) (((LPBYTE) pidl) + cb); 

   // Return NULL if it is null-terminating, or a pidl otherwise. 
   return (pidl->mkid.cb == 0) ? NULL : (LPITEMIDLIST) pidl; 
} 


UINT CPidlMgr::GetCount(LPITEMIDLIST pidl)
{
   int cnt = 0;
   int cb = pidl->mkid.cb; // size of the first item in list

   while(cb != 0) {
      cnt++;
      pidl = (LPITEMIDLIST)(((LPBYTE) pidl) + cb); // point to the next one
      cb = pidl->mkid.cb;
   }

   return cnt;
}

BOOL CPidlMgr::GetParentID(LPITEMIDLIST pidl)
{
    BOOL fRemoved = FALSE;

	// Make sure it's a valid PIDL.
    if (pidl == NULL)
        return(FALSE);

    if (pidl->mkid.cb)
    {
		LPITEMIDLIST pidlNext = pidl;
        while (pidlNext)
        {
           pidl = pidlNext;
		   pidlNext = GetNextItem(pidl);
        }
		// Remove the last one, insert null-terminator.
        pidl->mkid.cb = 0; 
        fRemoved = TRUE;
    }

    return fRemoved;
}


LPITEMIDLIST CPidlMgr::CopyFirst(const LPITEMIDLIST pidl, short n)
{
    UINT cb = 0;
	short c = n + 1;
	LPITEMIDLIST cursor = pidl;
    if (pidl)
    {
		cb += sizeof(cursor->mkid.cb);

		// Calculate the size of the new pidl
        while (cursor && c--)
        {
            cb += cursor->mkid.cb;
            cursor = GetNextItem(pidl);
        }
    }

    LPITEMIDLIST pidlRet = (LPITEMIDLIST)m_pMalloc->Alloc(cb);

    if (pidlRet) {
		ZeroMemory(pidlRet, cb);
		// Copy the content to the new pidl
        CopyMemory(pidlRet, pidl, cb);
		cursor = pidlRet;
		
		// Walk to the last item and set it's size member to 0
		// to terminate the list
		while (cursor && n--) {
			cursor = GetNextItem(cursor);
		}
		if (cursor) {
			cursor->mkid.cb = 0;
		}
	}
    return pidlRet;

}

