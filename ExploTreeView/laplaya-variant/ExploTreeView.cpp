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

// ExploTreeView.cpp : implementation of the CExploTreeView class
//

#include "stdafx.h"
#include "LaPlaya.h"

#include "LaPlayaDoc.h"
#include "ExploTreeView.h"
#include "PidlMgr.h"
#include "itemdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CExploTreeView

IMPLEMENT_DYNCREATE(CExploTreeView, CTreeView)

BEGIN_MESSAGE_MAP(CExploTreeView, CTreeView)
	//{{AFX_MSG_MAP(CExploTreeView)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, OnItemExpanding)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CExploTreeView construction/destruction

CExploTreeView::CExploTreeView()
{
	m_bInitialized = FALSE;

}

CExploTreeView::~CExploTreeView()
{
	while(!m_ptrList.IsEmpty()) {
		LPITEMDATA pData = (LPITEMDATA)m_ptrList.RemoveHead();
		if (pData) {
			delete pData;
		}
	}
}

BOOL CExploTreeView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_DISABLEDRAGDROP;

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CExploTreeView drawing

void CExploTreeView::OnDraw(CDC* pDC)
{
	CLaPlayaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CExploTreeView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
	InitializeTree();
}



/////////////////////////////////////////////////////////////////////////////
// CExploTreeView diagnostics

#ifdef _DEBUG
void CExploTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CExploTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CLaPlayaDoc* CExploTreeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLaPlayaDoc)));
	return (CLaPlayaDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CExploTreeView message handlers

BOOL CExploTreeView::InsertFolder(HTREEITEM hParentItem,IShellFolder* pParentFolder, LPITEMIDLIST pidlParent)
{
	IEnumIDList* pEnum;
	if(SUCCEEDED(pParentFolder->EnumObjects(NULL, SHCONTF_FOLDERS | SHCONTF_INCLUDEHIDDEN, &pEnum)))
	{
		LPITEMIDLIST pidl;
		DWORD  dwFetched = 1;
		TV_ITEM tvItem={0};
		TV_INSERTSTRUCT   tvInsert={0};
		LPMALLOC pMalloc = NULL;
		SHGetMalloc(&pMalloc);
		pidl = (LPITEMIDLIST)pMalloc->Alloc(sizeof(ITEMIDLIST));
		CPidlMgr mgr(pMalloc);
		while(SUCCEEDED(pEnum->Next(1, &pidl, &dwFetched)) && dwFetched)
		{
			LPITEMDATA pItemInfo = new _ITEMDATA;
			m_ptrList.AddHead(pItemInfo);
			pItemInfo->pidlSelf = pidl;
			pItemInfo->pidlFullyQual = mgr.Concatenate(pidlParent, pidl);
			PIDLTEST(pItemInfo->pidlFullyQual);
			pParentFolder->AddRef();
			pItemInfo->pParentFolder = pParentFolder;
			ZeroMemory(&tvItem, sizeof(tvItem));
			tvItem.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;

			STRRET strDispName;	
			pParentFolder->GetDisplayNameOf(pidl, SHGDN_INFOLDER, &strDispName);
			TCHAR psName[_MAX_PATH] = "";
			GetFriendlyName(psName, pidl, &strDispName);
			tvItem.pszText = psName;
			tvItem.cchTextMax = MAX_PATH;
			tvItem.iImage = GetIcon(pItemInfo->pidlFullyQual, FALSE);
			tvItem.iSelectedImage = GetIcon(pItemInfo->pidlFullyQual, TRUE);

			tvItem.lParam= (LPARAM)pItemInfo;
			//TRACE("PARAM: %s, %x, %x\n", psName, *pItemInfo->pidlSelf, *pItemInfo->pidlFullyQual);
			DWORD dwAttribs = SFGAO_FILESYSTEM  | SFGAO_HASSUBFOLDER | SFGAO_FOLDER | SFGAO_DISPLAYATTRMASK | SFGAO_CANRENAME;
			pParentFolder->GetAttributesOf(1, (LPCITEMIDLIST*)&pidl, &dwAttribs);
			tvItem.cChildren = (dwAttribs & SFGAO_HASSUBFOLDER);
			if(dwAttribs & SFGAO_SHARE)
			{
				tvItem.mask |= TVIF_STATE;
				tvItem.stateMask |= TVIS_OVERLAYMASK;
				tvItem.state |= INDEXTOOVERLAYMASK(1);
			}
			tvInsert.item = tvItem;
			tvInsert.hInsertAfter = TVI_LAST;
			tvInsert.hParent = hParentItem;
			GetTreeCtrl().InsertItem(&tvInsert);
			dwFetched = 0;
		}
		pEnum->Release();
		pParentFolder->Release();
		pMalloc->Release();
		return true;
	}
	return false;
}

int CExploTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

void CExploTreeView::OnItemExpanding(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	
	IShellFolder *pParentFolder;
	CTreeCtrl &treeCtrl = GetTreeCtrl();
	if(pNMTreeView->action == TVE_COLLAPSE) {
        treeCtrl.Expand(pNMTreeView->itemNew.hItem, TVE_COLLAPSE | TVE_COLLAPSERESET);
	}
    else if(pNMTreeView->action == TVE_EXPAND)
	{
		HCURSOR	 hCursor;
		TVITEM   tvItem = {0};
		tvItem.mask = TVIF_PARAM;
		tvItem.hItem = pNMTreeView->itemNew.hItem;
		if(!treeCtrl.GetItem(&tvItem))
			return;
		LPITEMDATA pItemInfo = (LPITEMDATA)tvItem.lParam;
		hCursor = SetCursor(LoadCursor(NULL, IDC_WAIT));
		
		if(pItemInfo->pParentFolder == 0)
		{
			if(FAILED(SHGetDesktopFolder(&pParentFolder)))
				return;
		}
		else if(FAILED(pItemInfo->pParentFolder->BindToObject(pItemInfo->pidlSelf, NULL, IID_IShellFolder, (void**)&pParentFolder)))
			return;
	
		treeCtrl.SetRedraw(FALSE);
		InsertFolder(pNMTreeView->itemNew.hItem, pParentFolder, pItemInfo->pidlFullyQual);
		TVSORTCB tvsort;
		tvsort.hParent = pNMTreeView->itemNew.hItem;
		tvsort.lParam = NULL;
		tvsort.lpfnCompare = &CompareFunc;
		treeCtrl.SortChildrenCB(&tvsort);
		treeCtrl.SetRedraw(TRUE);
		pParentFolder->Release();
		SetCursor(hCursor);
	}
}

int CALLBACK CExploTreeView::CompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	IShellFolder * pParentFolder = ((LPITEMDATA)lParam1)->pParentFolder;
	HRESULT nRet = pParentFolder->CompareIDs(0, ((LPITEMDATA)lParam1)->pidlSelf, ((LPITEMDATA)lParam2)->pidlSelf);
	
	if (FAILED (nRet))
		return 0;

	return (short)nRet;
}

BOOL CExploTreeView::InitializeTree()
{
	if (!m_bInitialized) {
		CTreeCtrl &treeCtrl = GetTreeCtrl();

		LPITEMIDLIST   pidl;

		if(SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl)))
		{
			IShellFolder* pDesktop;
			TV_ITEM tvItem={0};
			TV_INSERTSTRUCT   tvInsert={0};

			if(FAILED(SHGetDesktopFolder(&pDesktop)))
			{
			   //TODO: free the pidl through IMalloc
			   return false;
			}

			LPITEMDATA pItemInfo = new _ITEMDATA;
			m_ptrList.AddHead(pItemInfo);
			if(pItemInfo == NULL)
			{
			   //TODO: free the pidl through IMalloc
			   pDesktop->Release();
			   return false;
			}
			pItemInfo->pidlSelf = pidl;
			pItemInfo->pidlFullyQual = pidl;
			pItemInfo->pParentFolder = NULL;

			tvItem.mask = TVIF_PARAM | TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
			tvItem.lParam= (LPARAM)pItemInfo;
			STRRET strDispName;
			pDesktop->GetDisplayNameOf(pidl, SHGDN_INFOLDER, &strDispName);
			TCHAR psName[_MAX_PATH] = "";
			GetFriendlyName(psName, pidl, &strDispName);
			tvItem.pszText = psName;
			tvItem.cchTextMax = MAX_PATH;
			tvItem.iImage = GetIcon(pidl, FALSE);
			tvItem.iSelectedImage = GetIcon(pidl, TRUE);


			tvItem.cChildren = TRUE;
			tvInsert.item = tvItem;
			tvInsert.hInsertAfter = TVI_LAST;
			HTREEITEM hItem = treeCtrl.InsertItem(&tvInsert);
			treeCtrl.SelectItem(hItem);
			treeCtrl.Expand(hItem, TVE_EXPAND);
			pDesktop->Release();
			m_bInitialized = TRUE;
			return true;
		}

	}

	return false;
}

int CExploTreeView::GetIcon(LPITEMIDLIST pidl, bool bSelected)
{
	SHFILEINFO sfi;
	DWORD dwAttrib = SHGFI_PIDL | SHGFI_SYSICONINDEX | SHGFI_SMALLICON;
	if (bSelected) {
		dwAttrib |= SHGFI_OPENICON;
	}

	SHGetFileInfo((LPCTSTR)pidl, 0, &sfi, sizeof (SHFILEINFO), dwAttrib);

	return sfi.iIcon;
}

void CExploTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NMTREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	CTreeCtrl &TreeCtrl = GetTreeCtrl();

	HTREEITEM hTI = pNMTreeView->itemNew.hItem;
	if (!hTI) {
		return;
	}
	LPITEMDATA pItemInfo = (LPITEMDATA)TreeCtrl.GetItemData(hTI);
	if (pItemInfo && pItemInfo->pParentFolder) {
		CLaPlayaDoc * pDoc = GetDocument();
		CString sPath;
		SHGetPathFromIDList(pItemInfo->pidlFullyQual, sPath.GetBuffer(_MAX_PATH));
		sPath.ReleaseBuffer();
		if (sPath.IsEmpty()) {
			*pResult = 1;
			return;
		}
		pDoc->SetPathName(sPath, FALSE);
		pDoc->UpdateAllViews(this, NEW_DIR);
		*pResult = 0;
	}
	else {
		*pResult = 1;
	}
}

BOOL CExploTreeView::GetFriendlyName(TCHAR pzDisplayName[_MAX_PATH], LPITEMIDLIST pidl, STRRET * strDispName)
{
	switch (strDispName->uType)
	{
		case STRRET_WSTR: {
			int nLen = WideCharToMultiByte (CP_ACP, // code page
				0, // dwFlags
				strDispName->pOleStr, // lpWideCharStr
				-1, // cchWideChar
				pzDisplayName, // lpMultiByteStr
				0, // cchMultiByte
				NULL, // lpDefaultChar
				NULL); // lpUsedDefaultChar
			
			nLen = WideCharToMultiByte (CP_ACP, // code page
				0, // dwFlags
				strDispName->pOleStr, // lpWideCharStr
				-1, // cchWideChar
				pzDisplayName, // lpMultiByteStr
				nLen, // cchMultiByte
				NULL, // lpDefaultChar
				NULL); // lpUsedDefaultChar
			break;
		}
		case STRRET_OFFSET:
			lstrcpy (pzDisplayName, (LPSTR)pidl + strDispName->uOffset);
			break;

		case STRRET_CSTR:
			lstrcpy (pzDisplayName, (LPSTR) strDispName->cStr);
			break;

		default:
			return FALSE;
			break;
	}            

	return TRUE;
}

BOOL CExploTreeView::OpenFolder(LPCTSTR szPath)
{
	ITEMIDLIST* pidl;

	if(SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl)))
	{
		IShellFolder* pDesktop;

		if(FAILED(SHGetDesktopFolder(&pDesktop)))
		{
		   //TODO: free the pidl through IMalloc
		   return FALSE;
		}


		TCHAR tchPath[MAX_PATH];
		WCHAR wchPath[MAX_PATH];    
	    
	    GetFullPathName (szPath, sizeof (tchPath) / sizeof (TCHAR), tchPath, NULL);

		if (IsTextUnicode (tchPath, lstrlen (tchPath), NULL))
		    lstrcpy ((char *) wchPath, tchPath);
		else
			MultiByteToWideChar (CP_ACP, 0, tchPath, -1, wchPath, sizeof (wchPath) / sizeof (WCHAR));


		ULONG ulEaten = 0, ulAttributes = 0;

		if (SUCCEEDED (pDesktop->ParseDisplayName(m_hWnd, NULL, wchPath, &ulEaten, &pidl, &ulAttributes))) {
			pDesktop->Release();
			// Now traverse the tree to find the pidl
			OpenPidl(pidl);
		}

		pDesktop->Release();
		LPMALLOC pMalloc = NULL;
		SHGetMalloc(&pMalloc);
		pMalloc->Free(pidl);
		pMalloc->Release();
	}

	return TRUE;
}

void CExploTreeView::OpenPidl(const LPITEMIDLIST pidl)
{
	CTreeCtrl &tree = GetTreeCtrl();

	tree.SetRedraw(FALSE);
	tree.SelectItem(NULL);
	HTREEITEM hTI = tree.GetRootItem();
	HTREEITEM hTIold = NULL;
	while (pidl && hTI) {
		LPITEMDATA data = (LPITEMDATA)tree.GetItemData(hTI);
#ifdef _DEBUG
		TRACE("TRAVERSING: %s\n", tree.GetItemText(hTI));
#endif
		if (PidlIsParentOf(data->pidlFullyQual, pidl)) {
			// We found the next level. Expand the branch
			tree.Expand(hTI, TVE_EXPAND);
			tree.SetItemState(hTIold, 0, TVIS_SELECTED);
			tree.SetItemState(hTI, TVIS_SELECTED, TVIS_SELECTED);
			hTIold = hTI;
			hTI = tree.GetChildItem(hTI);
			continue;
		}

		hTI = tree.GetNextSiblingItem(hTI);
	}
	tree.EnsureVisible(hTIold);
	tree.SetRedraw(TRUE);
}

void CExploTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	if (lHint == NEW_DIR) {
		CLaPlayaDoc * pDoc = GetDocument();
		CString sPath = pDoc->GetPathName();
		OpenFolder(sPath);
	}
}

void CExploTreeView::PIDLTEST(LPITEMIDLIST pidl)
{
	CTreeCtrl &tree = GetTreeCtrl();
	
	while(pidl) {
		CString sPath;
		SHGetPathFromIDList(pidl, sPath.GetBuffer(_MAX_PATH));
		sPath.ReleaseBuffer();

		TRACE("NAME: %s\n", sPath);
		
		USHORT nLen;

		if ((nLen = pidl->mkid.cb) == 0) {
			pidl = NULL;
		}
		else {
			pidl = (LPITEMIDLIST) (((LPBYTE) pidl) + nLen);
		}
	}

	TRACE("==================\n");
}

BOOL CExploTreeView::PidlIsParentOf(LPITEMIDLIST parent, LPITEMIDLIST child)
{
	LPMALLOC pMalloc = NULL;
	SHGetMalloc(&pMalloc);
	if (!pMalloc) {
		return FALSE;
	}
	CPidlMgr mgr(pMalloc);

	UINT nParent = mgr.GetCount(parent);

	LPITEMIDLIST pidlChildLevel = mgr.CopyFirst(child, nParent + 1);

	IShellFolder * pFolder;
	HRESULT hr = 1;

	if (SUCCEEDED(SHGetDesktopFolder(&pFolder))) {
#ifdef _DEBUG
		CString sChild;
		CString sParent;
		SHGetPathFromIDList(parent, sParent.GetBuffer(_MAX_PATH));
		sParent.ReleaseBuffer();
		SHGetPathFromIDList(pidlChildLevel, sChild.GetBuffer(_MAX_PATH));
		sChild.ReleaseBuffer();
		TRACE("PARENT: %s\nCHILD:  %s\n", sParent, sChild);
#endif
		hr = pFolder->CompareIDs(0, parent, pidlChildLevel);
		if (FAILED(hr)) {
			DWORD dwError = GetLastError();
			pMalloc->Free(pidlChildLevel);
			pMalloc->Release();
			return FALSE;
		}
	}
	//mgr.Restore(nParent, child, uOldLen);
	pMalloc->Free(pidlChildLevel);
	pMalloc->Release();

	return hr == 0;
}

