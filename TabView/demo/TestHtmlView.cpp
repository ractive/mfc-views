// TestHtmlView.cpp : implementation file
//

#include "stdafx.h"
#include "tabviewtest.h"
#include "TabViewTestDoc.h"
#include "TestHtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestHtmlView

IMPLEMENT_DYNCREATE(CTestHtmlView, CHtmlView)

CTestHtmlView::CTestHtmlView()
{
	//{{AFX_DATA_INIT(CTestHtmlView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CTestHtmlView::~CTestHtmlView()
{
}

void CTestHtmlView::DoDataExchange(CDataExchange* pDX)
{
	CHtmlView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestHtmlView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestHtmlView, CHtmlView)
	//{{AFX_MSG_MAP(CTestHtmlView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestHtmlView diagnostics

#ifdef _DEBUG
void CTestHtmlView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CTestHtmlView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestHtmlView message handlers

void CTestHtmlView::OnInitialUpdate() 
{
	//Change the code to go where you'd like.
	Navigate2(_T("http://www.ractive.ch/gpl/TabView.html"), NULL, NULL);
}


void CTestHtmlView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// Get the URL from the document
	CTabViewTestDoc * pDoc = (CTabViewTestDoc *)GetDocument();

	Navigate2(pDoc->m_sUrl, NULL, NULL);	
}
