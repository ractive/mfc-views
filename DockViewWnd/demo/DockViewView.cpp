// DockViewView.cpp : implementation of the CDockViewView class
//

#include "stdafx.h"
#include "DockView.h"

#include "DockViewDoc.h"
#include "DockViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockViewView

IMPLEMENT_DYNCREATE(CDockViewView, CView)

BEGIN_MESSAGE_MAP(CDockViewView, CView)
	//{{AFX_MSG_MAP(CDockViewView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockViewView construction/destruction

CDockViewView::CDockViewView()
{
	// TODO: add construction code here

}

CDockViewView::~CDockViewView()
{
}

BOOL CDockViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDockViewView drawing

void CDockViewView::OnDraw(CDC* pDC)
{
	CDockViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDockViewView diagnostics

#ifdef _DEBUG
void CDockViewView::AssertValid() const
{
	CView::AssertValid();
}

void CDockViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDockViewDoc* CDockViewView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDockViewDoc)));
	return (CDockViewDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDockViewView message handlers
