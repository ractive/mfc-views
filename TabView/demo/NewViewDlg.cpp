// NewViewDlg.cpp : implementation file
//

#include "stdafx.h"
#include "tabviewtest.h"
#include "NewViewDlg.h"
#include "TestHTMLView.h"
#include "MyTreeView.h"
#include "MyListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNewViewDlg dialog


CNewViewDlg::CNewViewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewViewDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNewViewDlg)
	m_nPosition = 0;
	m_sTabLabel = _T("");
	//}}AFX_DATA_INIT
}


void CNewViewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNewViewDlg)
	DDX_Control(pDX, IDC_VIEWLIST, m_ViewList);
	DDX_Text(pDX, IDC_POSITION, m_nPosition);
	DDX_Text(pDX, IDC_TABLABEL, m_sTabLabel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNewViewDlg, CDialog)
	//{{AFX_MSG_MAP(CNewViewDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewViewDlg message handlers

BOOL CNewViewDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// To make it as easy as possible we add the runtimeclass pointer of
	// the views as item data to the listitems
	int nInserted = m_ViewList.AddString("Browser window");
	m_ViewList.SetItemData(nInserted, (DWORD)RUNTIME_CLASS(CTestHtmlView));

	nInserted = m_ViewList.AddString("Tree view");
	m_ViewList.SetItemData(nInserted, (DWORD)RUNTIME_CLASS(CMyTreeView));

	nInserted = m_ViewList.AddString("List view");
	m_ViewList.SetItemData(nInserted, (DWORD)RUNTIME_CLASS(CMyListView));

	m_ViewList.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CNewViewDlg::OnOK() 
{
	// Get the selected runtime class
	m_pRuntimeClass = (CRuntimeClass *)m_ViewList.GetItemData(m_ViewList.GetCurSel());	
	CDialog::OnOK();
}
