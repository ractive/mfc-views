// TestTabView.cpp : implementation file
//

#include "stdafx.h"
#include "tabviewtest.h"
#include "TestTabView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestTabView

IMPLEMENT_DYNCREATE(CTestTabView, CTabView)

CTestTabView::CTestTabView()
{
}

CTestTabView::~CTestTabView()
{
}


BEGIN_MESSAGE_MAP(CTestTabView, CTabView)
	//{{AFX_MSG_MAP(CTestTabView)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestTabView drawing

void CTestTabView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTestTabView diagnostics

#ifdef _DEBUG
void CTestTabView::AssertValid() const
{
	CTabView::AssertValid();
}

void CTestTabView::Dump(CDumpContext& dc) const
{
	CTabView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestTabView message handlers

int CTestTabView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CTabView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetFontHeight(9);

	return 0;
}

BOOL CTestTabView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= TCS_BOTTOM | TCS_HOTTRACK;
	return CTabView::PreCreateWindow(cs);
}
