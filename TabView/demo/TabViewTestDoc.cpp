// TabViewTestDoc.cpp : implementation of the CTabViewTestDoc class
//

#include "stdafx.h"
#include "TabViewTest.h"

#include "TabViewTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabViewTestDoc

IMPLEMENT_DYNCREATE(CTabViewTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTabViewTestDoc, CDocument)
	//{{AFX_MSG_MAP(CTabViewTestDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabViewTestDoc construction/destruction

CTabViewTestDoc::CTabViewTestDoc()
{
	// TODO: add one-time construction code here

}

CTabViewTestDoc::~CTabViewTestDoc()
{
}

BOOL CTabViewTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTabViewTestDoc serialization

void CTabViewTestDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTabViewTestDoc diagnostics

#ifdef _DEBUG
void CTabViewTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTabViewTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTabViewTestDoc commands
