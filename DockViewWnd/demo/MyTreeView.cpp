// MyTreeView.cpp : implementation file
//

#include "stdafx.h"
#include "DockView.h"
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
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyTreeView drawing

void CMyTreeView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

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
	
	CTreeCtrl &tree	= GetTreeCtrl();

	tree.InsertItem("Root");
	ShowWindow(SW_SHOW);
}

int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
