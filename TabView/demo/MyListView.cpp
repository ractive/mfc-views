// MyListView.cpp : implementation file
//

#include "stdafx.h"
#include "tabviewtest.h"
#include "MyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyListView

IMPLEMENT_DYNCREATE(CMyListView, CListView)

CMyListView::CMyListView()
{
}

CMyListView::~CMyListView()
{
}


BEGIN_MESSAGE_MAP(CMyListView, CListView)
	//{{AFX_MSG_MAP(CMyListView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyListView drawing

void CMyListView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CMyListView diagnostics

#ifdef _DEBUG
void CMyListView::AssertValid() const
{
	CListView::AssertValid();
}

void CMyListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyListView message handlers

void CMyListView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	// Add some stupid stuff
	CListCtrl &listCtrl = GetListCtrl();
	listCtrl.InsertColumn(0, "Item", LVCFMT_LEFT, 300);
	listCtrl.InsertItem(0, "Item 1", 0);
	listCtrl.InsertItem(1, "Item 2", 0);
	listCtrl.InsertItem(2, "Item 3", 0);
	listCtrl.InsertItem(3, "Item 4", 0);
}

BOOL CMyListView::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= LVS_EDITLABELS | LVS_REPORT;	
	return CListView::PreCreateWindow(cs);
}

int CMyListView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CListView::OnCreate(lpCreateStruct) == -1)
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

	GetListCtrl().SetImageList(&m_ImageList, LVSIL_SMALL);
	
	return 0;
}
