// DockViewDoc.cpp : implementation of the CDockViewDoc class
//

#include "stdafx.h"
#include "DockView.h"

#include "DockViewDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDockViewDoc

IMPLEMENT_DYNCREATE(CDockViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CDockViewDoc, CDocument)
	//{{AFX_MSG_MAP(CDockViewDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDockViewDoc construction/destruction

CDockViewDoc::CDockViewDoc()
{
	// TODO: add one-time construction code here

}

CDockViewDoc::~CDockViewDoc()
{
}

BOOL CDockViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CDockViewDoc serialization

void CDockViewDoc::Serialize(CArchive& ar)
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
// CDockViewDoc diagnostics

#ifdef _DEBUG
void CDockViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDockViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDockViewDoc commands
