// MyTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "tabviewtest.h"
#include "TabViewTestDoc.h"
#include "MyTreeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{
}

CMyTreeView::~CMyTreeView()
{
}


BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
	//{{AFX_MSG_MAP(CMyTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnSelchanged)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_NOTIFY_REFLECT(TVN_BEGINLABELEDIT, OnBeginlabeledit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CMyTreeView diagnostics

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView message handlers

void CMyTreeView::OnInitialUpdate() 
{
	CTreeView::OnInitialUpdate();
	
	CTreeCtrl &tree = GetTreeCtrl();

	// Create kinda "Favorites" View

	HTREEITEM hRoot = tree.InsertItem("Bookmarks");
	HTREEITEM hTI = NULL;
	HTREEITEM hNews = tree.InsertItem("News", hRoot);

	// The data is 1 if it's a url and 0 if it's not...
	tree.SetItemData(hNews, 0);
	HTREEITEM hVC = tree.InsertItem("VisualC", hRoot);
	tree.SetItemData(hVC, 0);

	HTREEITEM hSearch = tree.InsertItem("Search", hRoot);
	tree.SetItemData(hSearch, 0);

	InsertUrl(hNews, "http://www.slashdot.org");
	InsertUrl(hNews, "http://www.heise.de/newsticker");

	InsertUrl(hVC, "http://msdn.microsoft.com/visualc");
	InsertUrl(hVC, "http://www.clipcode.com");
	InsertUrl(hVC, "http://www.codeguru.com");
	InsertUrl(hVC, "http://www.codeproject.com");
	InsertUrl(hVC, "http://www.eed.usv.ro/misc/doc/prog/c/mfc");
	InsertUrl(hVC, "http://www.ractive.ch/gpl");

	InsertUrl(hSearch, "http://www.google.com");
	InsertUrl(hSearch, "http://www.altavista.com");
	InsertUrl(hSearch, "http://astalavista.box.sk"); // ;-)


	tree.Expand(hRoot, TVE_EXPAND);
}

BOOL CMyTreeView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | TVS_EDITLABELS;	
	return CTreeView::PreCreateWindow(cs);
}

void CMyTreeView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// As an example we put the URL information into the tree view
	// I'm sure you find better examples :-)
}

void CMyTreeView::InsertUrl(HTREEITEM hParent, LPCTSTR lpszUrl)
{
	CTreeCtrl &tree = GetTreeCtrl();

	HTREEITEM hTI = tree.InsertItem(lpszUrl, hParent);
	tree.SetItemData(hTI, 1);
}

void CMyTreeView::OnSelchanged(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// Get the newly selected item
	HTREEITEM hTI = pNMTreeView->itemNew.hItem;

	if (!hTI) {
		return;
	}

	CTreeCtrl &tree = GetTreeCtrl();

	// Check if it's a url
	if (tree.GetItemData(hTI) == 0) {
		// This is not a URL
		return;
	}


	// Put the URL into the document
	CTabViewTestDoc * pDoc = (CTabViewTestDoc *)GetDocument();

	pDoc->m_sUrl = tree.GetItemText(hTI);

	// Tell the other views (esp. the HTML view) that someting changed
	pDoc->UpdateAllViews(this);

	*pResult = 0;
}

int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the image list
	m_ImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 1, 0);
	// Set the "windows" background color.
	m_ImageList.SetBkColor(GetSysColor(COLOR_WINDOW));
	// Add the "icons" to the image list.

	CBitmap bitmap;
	// Load the the bitmap
	if (!bitmap.LoadBitmap(IDB_EARTH)) {
		return 0;
	}

	// Add the bitmap to the image list
	m_ImageList.Add(&bitmap, m_ImageList.GetBkColor());

	GetTreeCtrl().SetImageList(&m_ImageList, TVSIL_NORMAL);

	return 0;
}

void CMyTreeView::OnDestroy() 
{
	CTreeView::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CMyTreeView::OnBeginlabeledit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
//	GetTreeCtrl().GetEditControl()->Dump(afxDump);
	*pResult = 0;
}
