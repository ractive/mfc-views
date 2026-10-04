# mfc-views

Three reusable MFC view classes written in 2001 for the Windows programs
**AGStreme / JAGS** (an Audiogalaxy client, <https://github.com/ractive/agstreme>)
and **LaPlaya** (a small movie player), and published at the time on
`http://www.ractive.ch/gpl/`. Visual C++ 6.0, MFC, Windows 2000/XP era.

| Directory | Class | Purpose | Licence |
|---|---|---|---|
| `TabView/` | `CTabView` | Tabbed doc/view container with dynamic creation and deletion of views | Own permissive notice (below) |
| `DockViewWnd/` | `CDockViewWnd`, `CViewBar` | Host any `CView` inside a docking, resizable control bar | GPL-2.0 |
| `ExploTreeView/` | `CExploTreeView`, `CPidlMgr` | Explorer-like shell folder tree with drag and drop and shell context menus | GPL-2.0 |

No screenshots of the demo programs have survived.

## CTabView (`TabView/TabView.h`, `TabView/TabView.cpp`)

A `CView`-derived class that owns a `CTabCtrl` and shows one child view (or
dialog) per tab. Unlike Jeff Prosise's `CTabView` from MSDN Magazine (June 2000),
which only accepts dialog templates, this one creates real views through
`CRuntimeClass` and `CCreateContext`, so the hosted views take part in the
document/view mechanism (`OnUpdate`, command routing via `OnCmdMsg`). Tabs can
be inserted, removed, hidden and activated at run time; the tab control is
owner-drawn (`DrawItem`) and the tab font height is adjustable.

Public operations (from the header):

```cpp
int     Insert(int nPage, LPCTSTR lpszItemText, CRuntimeClass* pNewWnd, CCreateContext* pContext = NULL);
int     Insert(LPCTSTR lpszItemText, CRuntimeClass* pNewWnd, CCreateContext* pContext = NULL); // append
void    RemoveView(int nItem);
void    RemoveView(CView* pView);
void    HidePage(int nPage);
void    ActivateView(int nItem);
CView*  GetView(int nView);
UINT    GetPageID(int nPage);
void    SetFontHeight(int nHeight);   // 9 is a good value
CTabCtrl& GetTabCtrl() const;
```

### How to use this class

Quoted from the header comment of `TabView.h`:

> - Create your application with class wizard (i.e. an SDI app).
>   Use CView as the base class or your view for now
>
> - Put TabView.h and TabView.cpp in your project directory
>
> - Derive your own class from CTabView (i.e. CMyTabView):
>   To make it as comfortable as possible, use class wizard and derive your
>   class from CTreeView. Change every occurence of "CTreeView" in the newly
>   created files to "CTabView"
>   #include "TabView.h" in the new headerfile (MyTabView.h)
>
> - Change in CYourApp::InitInstance the CYourView to CMyTabView in
>   pDocTemplate = new CSingleDocTemplate(...)
>
> - Override the virtual method CMainFrame::OnCreateClient()
>   change
>
>   ```cpp
>   return CFrameWnd::OnCreateClient(lpcs, pContext);
>   ```
>
>   to something like
>
>   ```cpp
>   if (!CFrameWnd::OnCreateClient(lpcs, pContext)) {
>       return FALSE;
>   }
>
>   CWnd* pWnd = GetDescendantWindow(AFX_IDW_PANE_FIRST, TRUE);
>   if (pWnd != NULL && pWnd->IsKindOf(pContext->m_pNewViewClass))
>   {
>       CTestTabView* pView = (CTestTabView*)pWnd;
>       m_pTabView = pView;
>
>       // Here you can add your dialogs and views and whatever you like....
>       if (pView->Insert(0, "Browser", RUNTIME_CLASS(CTestHtmlView), pContext) == -1) {
>           return FALSE;
>       }
>       if (pView->Insert(1, "Bookmarks", RUNTIME_CLASS(CMyTreeView), pContext) == -1) {
>           return FALSE;
>       }
>       if (pView->Insert(2, "Useless", RUNTIME_CLASS(CMyDialog), IDD_MYDIALOG) == -1) {
>           return FALSE;
>       }
>   }
>
>   return TRUE;
>   ```
>
> - I recommend:
>   Keep a pointer to your tabview in the main frame (as above m_pTabView = pView)
>   CTabView * m_pTabView;
>   Otherwise it's hard to get the tabview

The header also credits fragments of MFC's `WINSPLIT.CPP` and `CTreeView`
implementation and Chris Maunder's `CTabCtrlEx` (CodeGuru).

**Demo:** `TabView/demo/` is the `TabViewTest` SDI project (`TabViewTest.dsw`):
a tab view with a `CHtmlView` browser tab, a tree view and a list view, plus a
"New view" dialog that inserts further views at run time. The demo folder
contains its own copy of `TabView.h/.cpp`, as the project file expects them in
the same directory.

**Dependencies:** MFC only (`<afxtempl.h>`, `<afxpriv.h>`).

## CDockViewWnd and CViewBar (`DockViewWnd/`)

`CViewBar` derives from Cristi Posea's `CSizingControlBarCF` (a resizable,
dockable control bar with a caption) and creates one `CView` of a given
`CRuntimeClass` inside the bar, forwarding size changes and offering a
context menu on the caption. `CDockViewWnd` is an invisible `CWnd` owned by
the main frame that keeps a map of `CViewBar`s, creates them with a shared
`CCreateContext` so that the hosted views are attached to the document, sends
the initial update and routes commands (`OnCmdMsg`) to the active view. This
was the basis of the dockable "Shares", "MP3 files", "MP3 info" and browser
panes in AGStreme.

Usage as in the demo's `CMainFrame::OnCreate` (July 2001 API):

```cpp
m_wndDockView.Create(this, (CCreateContext*)lpCreateStruct->lpCreateParams);
m_wndDockView.CreateView(RUNTIME_CLASS(CMyTreeView));

POSITION pos = m_wndDockView.GetFirstBar();
while (pos) {
    CViewBar* pBar = m_wndDockView.GetNextBar(pos);
    pBar->EnableDocking(CBRS_ALIGN_ANY);
}
EnableDocking(CBRS_ALIGN_ANY);
// then DockControlBar(pBar) for each bar
```

The AGStreme version (second commit) changed the signature to
`CreateView(UINT nView, LPCTSTR lpszBarTitle, CRuntimeClass* pViewClass)`,
added `GetBar(nView)` / `GetView(nView)` lookups and a caption context menu
loaded from the resource `IDR_BARS`, which the host application must provide.

**Dependencies:** `DockViewWnd/third_party/` contains CSizingControlBar 2.43
(`sizecbar.*`, `scbarcf.*`, `scbarg.*`) by Cristi Posea, www.datamekanix.com,
whose notice reads: "This code is free for personal and commercial use,
providing this notice remains intact in the source files and all eventual
changes are clearly marked with comments. You must obtain the author's consent
before you can include this code in a software library."

**Demo:** `DockViewWnd/demo/` is the `DockView` SDI project (`DockView.dsw`)
with its own copies of the classes and of CSizingControlBar; it docks a
`CTreeView` next to the main view.

## CExploTreeView (`ExploTreeView/`)

A `CTreeView` that shows the Windows shell namespace like the left pane of
Explorer: folders are enumerated through `IShellFolder::EnumObjects`, each item
stores its PIDL (`itemdata.h`, managed by `CPidlMgr`), icons come from the
system image list, and the view supports:

- lazy expansion and refresh of folders, `OpenFolder(path)` and
  `GetPath(hItem)`;
- OLE drag and drop as source and target (`COleDropTarget`,
  `CF_HDROP`, copy/move via `SHFileOperation`), including auto-scroll while
  dragging;
- the real shell context menu (`IContextMenu`/`IContextMenu2`, with a window
  procedure hook for owner-drawn menu items) plus own commands for delete,
  delete-without-recycle-bin, rename, new folder and refresh;
- in-place label editing with the renamed folder reflected on disk.

This is the version used in AGStreme 2.22 (October 2001). It is **not fully
standalone**: it includes the application's `resource.h` (command IDs
`ID_DELETE`, `ID_DELETEERASE`, `ID_RENAME`, `ID_NEWDIR`, `ID_REFRESH`, menu
`IDR_TREECONTEXTMENU`), `JAGSDoc.h`/`JAGS.h`, and in the drop handler it
updates the AGStreme music database through `CSongsSet` (a DAO recordset).
Remove that block and supply the resource IDs to reuse it elsewhere.

`ExploTreeView/laplaya-variant/` holds the earlier, much smaller variant from
LaPlaya 1.1 (June 2001): enumeration, icons and selection only, no drag and
drop or context menus, coupled to `CLaPlayaDoc` instead.

## Building

All code targets Microsoft Visual C++ 6.0 with MFC (ANSI builds). Open the
`.dsw` workspace in a `demo/` directory to build a demo; copy the class files
into your own project otherwise. Line endings are CRLF and the files are
Windows-1252 encoded; they are stored byte-for-byte.

## History

1. `Import CTabView 1.0 and CDockViewWnd as published on ractive.ch (2001)`:
   contents of `TabViewTest.zip` (29 August 2001) and `DockViewWnd.zip`
   (15 July 2001).
2. `Update to the versions used in AGStreme 2.22`: the class files from the
   AGStreme source tree (September/October 2001), the later `TabViewTest` and
   `DockView` demo folders, CSizingControlBar, and `CExploTreeView` with its
   LaPlaya predecessor.
3. This README and licence files.

## Licences

- `CTabView` (`TabView/TabView.h`, `TabView/TabView.cpp`, and the copies in
  `TabView/demo/`) is distributed under the author's own notice, quoted from the
  header:

  > This program is free software; you can redistribute it and/or
  > modify it under the following terms
  >
  > 1. The author is not responsible for the consequences of use of
  >    this software, no matter if you, your computer or your cat
  >    get damaged by it.
  >
  > 2. Do whatever you want with it.
  >
  > 3. This notice must not be removed or altered.

- `CDockViewWnd`, `CViewBar`, `CExploTreeView`, `CPidlMgr`, `itemdata.h` and
  the demo projects carry the GNU General Public License v2 header of JAGS;
  the full text is in `LICENSE`.
- CSizingControlBar (`DockViewWnd/third_party/`, and the copies in
  `DockViewWnd/demo/`) is Copyright (C) 1998-2000 Cristi Posea under the terms
  quoted above.

Author: Jean-Pierre Bergamin <james@ractive.ch>.
