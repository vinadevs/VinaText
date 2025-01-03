/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "FindDlg.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"
#include "Editor.h"
#include "ScrollHelper.h"
#include "ComboboxRegexHelper.h"
#include "MainFrm.h"
#include "VinaTextProgressBar.h"
#include "AppSettings.h"
#include "FileUtil.h"
#include "GuiUtils.h"
#include "SearchAndReplaceDlg.h"

#pragma warning(disable : 4244)

IMPLEMENT_DYNAMIC(CFindDlg, CDialogEx)

CFindDlg::CFindDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindDlg::IDD, pParent)
{
	m_bMatchcase = FALSE;
	m_bMatchregex = FALSE;
	m_bMatchwords = FALSE;
	m_bAppendResult = FALSE;
	m_bShowFileNameOnly = FALSE;
	m_bExcludeSubFolder = FALSE;
	m_strFileFilter = _T("*.*;");
	m_pScrollHelper = std::make_unique<CScrollHelper>();
	m_pScrollHelper->AttachWnd(this);
	m_pScrollHelper->SetDisplaySize(200, 560);
}

CFindDlg::~CFindDlg() {}

UINT CFindDlg::FindBackgroundThreadProc(LPVOID pParam)
{
	CFindTextWorker* pFinder = reinterpret_cast<CFindTextWorker*>(pParam);
	if (pFinder == NULL)
	{
		return 1;
	}
	pFinder->FindInFolder();
	return 0; // thread completed successfully
}

void CFindDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, ID_EDITOR_SEARCH_FILE_FILTER_EDIT, m_EditFilter);
	DDX_Control(pDX, ID_EDITOR_SEARCH_PATH_SPECIFIC_EDIT, m_EditSpecialPath);
	DDX_Control(pDX, ID_EDITOR_SEARCH_COMBO, m_comboSearchWhat);
	DDX_Control(pDX, ID_EDITOR_SEARCH_SCOPE_COMBO, m_comboSearchScope);
	DDX_Check(pDX, ID_EDITOR_SEARCH_CHECK_MATCH_CASE, m_bMatchcase);
	DDX_Check(pDX, ID_EDITOR_SEARCH_CHECK_REGEX, m_bMatchregex);
	DDX_Check(pDX, ID_EDITOR_SEARCH_CHECK_MATCH_WHOLE, m_bMatchwords);	
	DDX_Check(pDX, ID_EDITOR_SEARCH_CHECK_APPEND_SEACH_RESULT, m_bAppendResult);
	DDX_Check(pDX, ID_EDITOR_SEARCH_CHECK_SHOW_FILE_NAME, m_bShowFileNameOnly);
	DDX_Check(pDX, ID_EDITOR_SEARCH_CHECK_EXCLUDE_SUB_FOLDER, m_bExcludeSubFolder);
	DDX_Text(pDX, ID_EDITOR_SEARCH_FILE_FILTER_EDIT, m_strFileFilter);
	DDX_Text(pDX, ID_EDITOR_SEARCH_PATH_SPECIFIC_EDIT, m_strSpecificPath);
	DDX_Control(pDX, ID_EDITOR_SEARCH_REGEX_COMBO, m_combRegexPattern);
}

BEGIN_MESSAGE_MAP(CFindDlg, CDialogEx)
	ON_CBN_EDITCHANGE(ID_EDITOR_SEARCH_COMBO, OnSearchEditChange)
	ON_EN_CHANGE(ID_EDITOR_SEARCH_FILE_FILTER_EDIT, OnFilterEditChange)
	ON_BN_CLICKED(ID_EDITOR_SEARCH_NEXT, OnSearchNext)
	ON_BN_CLICKED(ID_EDITOR_SEARCH_PREVIOUS, OnSeachPrevious)
	ON_BN_CLICKED(ID_EDITOR_SEARCH_ALL, OnSearchAll)
	ON_BN_CLICKED(ID_EDITOR_SEARCH_CHECK_REGEX, OnClickCheckBoxRegex)
	ON_CBN_SELCHANGE(ID_EDITOR_SEARCH_COMBO, OnCbnSelchangeSearchEditCombo)
	ON_CBN_SELCHANGE(ID_EDITOR_SEARCH_SCOPE_COMBO, OnCbnSelchangeSearchScope)
	ON_CBN_SELCHANGE(ID_EDITOR_SEARCH_REGEX_COMBO, OnCbnSelchangeRegexPattern)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

BOOL CFindDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitComboSearchScope();
	InitComboRegexPattern();

	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_GROUPBOX)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_CHECK_MATCH_CASE)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_CHECK_REGEX)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_CHECK_EXCLUDE_SUB_FOLDER)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_CHECK_MATCH_WHOLE)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_FILE_FILTER_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_SCOPE_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_FILE_SPECIFIC_PATH_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_CHECK_APPEND_SEACH_RESULT)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_CHECK_SHOW_FILE_NAME)->GetSafeHwnd(), L"wstr", L"wstr");
	SetWindowTheme(GetDlgItem(ID_EDITOR_SEARCH_PATTERN_STATIC)->GetSafeHwnd(), L"wstr", L"wstr");
	
	OnCbnSelchangeSearchScope();

	// enable the browse button and put the control in file browse mode
	m_EditSpecialPath.EnableFolderBrowseButton();

	m_comboSearchWhat.SetCueBanner(_T("target..."));

	OnClickCheckBoxRegex();

	LoadDialogState();

	OnSearchEditChange();

	UpdateData(FALSE);

	::DragAcceptFiles(m_hWnd, TRUE);

	RegisterResizingControls();

	return TRUE;
}

BOOL CFindDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			auto pActiveDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			if (pActiveDoc && pActiveDoc->GetEditorCtrl())
			{
				pActiveDoc->GetEditorCtrl()->SetFocus();
			}
			return TRUE;
		}
		else if (pMsg->wParam == 'H')
		{
			if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
			{
				auto const pParent = GetParent()->GetParent();
				auto const pQSDialog = dynamic_cast<CSearchAndReplaceWindowDlg*>(pParent);
				if (pQSDialog)
				{
					CString strSearchWhat;
					m_comboSearchWhat.GetWindowText(strSearchWhat);
					pQSDialog->InitSearchReplaceFromEditor(strSearchWhat, SEARCH_REPLACE_GOTO_DLG_TYPE::REPLACE);
					return TRUE;
				}
			}
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CFindDlg::InitSearchReplaceFromEditor(const CString& strSearchWhat, BOOL bSelectEditbox)
{
	m_comboSearchWhat.SetWindowTextW(strSearchWhat);
	if (bSelectEditbox)
		m_comboSearchWhat.SetFocus();
	else
		m_comboSearchWhat.SetFocusEx();
	OnCbnSelchangeSearchScope();
	SaveSearchString(strSearchWhat);
	if (strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		EnableButtons(TRUE);
	}
}

void CFindDlg::SearchFromEditor(const CString& strSearchWhat, SEARCH_TYPE searchType,
	BOOL bSeacrhNext, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	// reset flags
	m_bMatchcase = FALSE;
	m_bMatchregex = FALSE;
	m_bMatchwords = FALSE;

	if (searchType == SEARCH_TYPE::MACTCH_CASE)
	{
		m_bMatchcase = TRUE;
	}
	else if (searchType == SEARCH_TYPE::MACTCH_WORD)
	{
		m_bMatchwords = TRUE;
	}
	else if (searchType == SEARCH_TYPE::REGEX)
	{
		m_bMatchregex = TRUE;
	}

	if (bSeacrhNext)
	{
		DoSearchNext(strSearchWhat, bHideMessageBox, bSaveSearchWord);
	}
	else
	{
		DoSeachPrevious(strSearchWhat);
	}
}

void CFindDlg::SetFocusComboSearchWhat()
{
	m_comboSearchWhat.SetFocus();
}

void CFindDlg::InitSearchReplaceFromExplorer(const CString& strFolderPath)
{
	m_comboSearchScope.SetCurSel(3);
	OnCbnSelchangeSearchScope();
	m_strSpecificPath = strFolderPath;
	m_comboSearchWhat.SetFocus();
	UpdateData(FALSE);
}

void CFindDlg::OnSearchNext()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	DoSearchNext(strSearchWhat, FALSE);
}

void CFindDlg::DoSearchNext(CString strSearchWhat, BOOL bHideMessageBox, BOOL bSaveSearchWord)
{
	if (strSearchWhat.IsEmpty()) return;
	UpdateSearchOptions();
	auto const pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		auto pEditor = pView->GetEditorCtrl();
		if (pEditor != NULL)
		{
			if (bSaveSearchWord)
			{
				SaveSearchString(strSearchWhat);
			}
			CFindTextWorker::SearchForwardOnEditor(pEditor, strSearchWhat, m_nSearchOptions, bHideMessageBox);
		}
	}
}

void CFindDlg::DoSeachPrevious(CString strSearchWhat)
{
	if (strSearchWhat.IsEmpty()) return;
	UpdateSearchOptions();
	auto const pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
	if (pView)
	{
		auto pEditor = pView->GetEditorCtrl();
		if (pEditor != NULL)
		{
			SaveSearchString(strSearchWhat);
			CFindTextWorker::SearchBackwardOnEditor(pEditor, strSearchWhat, m_nSearchOptions);
		}
	}
	m_comboSearchWhat.SetFocusEx();
}

void CFindDlg::OnSeachPrevious()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	DoSeachPrevious(strSearchWhat);
}

void CFindDlg::SearchAllInDocument(CDocument* pDoc,
	TEXT_RESULT_SEARCH_REPLACE_DATA& ResultSearchData,
	const CString& strSearchWhat,
	unsigned int nSearchOptions)
{
	auto const pEditorDoc = dynamic_cast<CEditorDoc*>(pDoc);
	if (pEditorDoc)
	{
		auto pEditor = pEditorDoc->GetEditorCtrl();
		if (pEditor != NULL)
		{
			CString strFilePath = pEditorDoc->GetPathName();
			if (strFilePath.IsEmpty())
			{
				strFilePath = pEditorDoc->GetTitle();
			}
			if (CFindTextWorker::SearchAllInEditor(strFilePath, pEditor, ResultSearchData, strSearchWhat, nSearchOptions))
			{
				ResultSearchData._nMatchedFiles++;
			}
		}
	}
}

void CFindDlg::RegisterResizingControls()
{
	BOOL bOk = FALSE;
	bOk = m_resizer.Hook(this);
	ASSERT(bOk);

	bOk = m_resizer.SetAnchor(ID_EDITOR_SEARCH_FILE_FILTER_EDIT, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_SEARCH_PATH_SPECIFIC_EDIT, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_SEARCH_REGEX_COMBO, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_SEARCH_COMBO, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_SEARCH_SCOPE_COMBO, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
	bOk = m_resizer.SetAnchor(ID_EDITOR_SEARCH_GROUPBOX, ANCHOR_HORIZONTALLY);
	ASSERT(bOk);
}

void CFindDlg::OnSearchAll()
{
	UpdateData(TRUE);

	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	if (m_bAppendResult == FALSE)
	{
		pFrame->ClearDataOnDockPane(DOCKABLE_PANE_TYPE::SEARCH_RESULT_PANE);
	}

	if (m_hThreadFindBackground) // if find background is running, allow to stop thread...
	{
		DWORD dwExitCode = 0;
		if (::GetExitCodeThread(m_hThreadFindBackground, &dwExitCode))
		{
			if (dwExitCode == STILL_ACTIVE)
			{
				dwExitCode = 0;
				::TerminateThread(m_hThreadFindBackground, dwExitCode);
				m_hThreadFindBackground = NULL;
			}
		}
		GetDlgItem(ID_EDITOR_SEARCH_ALL)->SetWindowTextW(_T("Search All"));
		GetDlgItem(ID_EDITOR_SEARCH_NEXT)->EnableWindow(TRUE);
		GetDlgItem(ID_EDITOR_SEARCH_PREVIOUS)->EnableWindow(TRUE);
		m_pFindProgressBar.reset();
		return;
	}

	UpdateSearchOptions();

	TEXT_RESULT_SEARCH_REPLACE_DATA ResultSearchData;
	
	auto startMeasure = OSUtils::StartBenchmark();

	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	if (strSearchWhat.IsEmpty()) return;

	SaveSearchString(strSearchWhat);

	CString strSearchScope;
	m_comboSearchScope.GetWindowText(strSearchScope);
	if (strSearchScope == _T("Current File"))
	{
		ResultSearchData._nTotalSearchFile = 1;
		SearchAllInDocument(AppUtils::GetMDIActiveDocument(), ResultSearchData, strSearchWhat, m_nSearchOptions);
	}
	else if (strSearchScope == _T("All Opened Files"))
	{
		auto vecDocs = AppUtils::GetAllDocuments();
		ResultSearchData._nTotalSearchFile = (unsigned int)vecDocs.size();
		for (auto const& doc : vecDocs)
		{
			SearchAllInDocument(doc, ResultSearchData, strSearchWhat, m_nSearchOptions);
		}
	}
	else if (strSearchScope == _T("Container Folder"))
	{
		auto const pDoc = AppUtils::GetMDIActiveDocument();
		if (pDoc)
		{
			CString strFilePath = pDoc->GetPathName();
			if (PathFileExists(strFilePath))
			{
				CString strContainerFoler = PathUtils::GetContainerPath(strFilePath);
				GetDlgItem(ID_EDITOR_SEARCH_ALL)->SetWindowTextW(_T("Stop"));
				GetDlgItem(ID_EDITOR_SEARCH_NEXT)->EnableWindow(FALSE);
				GetDlgItem(ID_EDITOR_SEARCH_PREVIOUS)->EnableWindow(FALSE);
				// background search start...
				CString strMessageProgressbar;
				strMessageProgressbar.Format(_T("Searching text..."));
				m_pFindProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, strMessageProgressbar, PROGRESS_BAR_TYPE::TYPE_SEARCH);
				m_pFindProgressBar->SetPos(0);
				std::unique_ptr<CFindTextWorker> pFinder = std::make_unique<CFindTextWorker>();
				pFinder->SetTargetSearchFolder(strContainerFoler);
				pFinder->SetSearchWhat(strSearchWhat);
				pFinder->SetSearchOptions(m_nSearchOptions);
				pFinder->SetIncludeSubFolder(!m_bExcludeSubFolder);
				pFinder->SetFileFilter(m_strFileFilter);
				pFinder->SetParentWindow(this);
				DWORD dwExitCode = 0;
				CWinThread* pThread = ::AfxBeginThread(FindBackgroundThreadProc, (LPVOID)pFinder.get(), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | THREAD_TERMINATE, NULL);
				if (pThread)
				{
					m_hThreadFindBackground = pThread->m_hThread;
					pThread->m_bAutoDelete = TRUE;
					pThread->ResumeThread();
				}
				while (TRUE)
				{
					if (!::GetExitCodeThread(m_hThreadFindBackground, &dwExitCode))
					{
						break;
					}
					if (dwExitCode != STILL_ACTIVE)
					{
						break;
					}
					USE_THREAD_PUMP_UI;
					if (m_pFindProgressBar && pFinder)
					{
						int nCurPos = pFinder->GetCurrentFindProgress();
						m_pFindProgressBar->SetPos(nCurPos);
						CString strMessageProgressbar;
						strMessageProgressbar.Format(_T("%s - %d%% completed..."), pFinder->GetCurrentSearchPath(), nCurPos);
						m_pFindProgressBar->SetText(strMessageProgressbar);
					}
				}
				m_hThreadFindBackground = NULL;
				m_pFindProgressBar.reset();
				ResultSearchData = pFinder->m_ResultSearchData;
				GetDlgItem(ID_EDITOR_SEARCH_ALL)->SetWindowTextW(_T("Search All"));
				GetDlgItem(ID_EDITOR_SEARCH_NEXT)->EnableWindow(TRUE);
				GetDlgItem(ID_EDITOR_SEARCH_PREVIOUS)->EnableWindow(TRUE);
			}
			else
			{
				AfxMessageBox(_T("[Search In Container Folder Error] current file path does not exist."));
				return;
			}
		}
	}
	else if (strSearchScope == _T("Specific Path"))
	{
		if (m_strSpecificPath.IsEmpty())
		{
			AfxMessageBox(_T("[Search In Path Error] specific path is empty."));
			return;
		}
		if (PathFileExists(m_strSpecificPath))
		{
			if (!PathUtils::IsDirectory(m_strSpecificPath))
			{
				CFindTextWorker finder;
				finder.SetFileFilter(m_strFileFilter);
				if (finder.CheckFileFilter(m_strFileFilter))
				{
					CRect rectEditor;
					rectEditor.SetRectEmpty();
					std::unique_ptr<CEditorCtrl> pEditor = std::make_unique<CEditorCtrl>();
					pEditor->Create(_T("Search Editor"), WS_CHILD | WS_CLIPCHILDREN | WS_EX_RTLREADING, rectEditor, this, ID_EDITOR_CTRL_SEARCH);
					if (::IsWindow(pEditor->GetSafeHwnd()))
					{
						pEditor->LoadFile(m_strSpecificPath);
						ResultSearchData._nTotalSearchFile = 1;
						if (CFindTextWorker::SearchAllInEditor(m_strSpecificPath, pEditor.get(), ResultSearchData, strSearchWhat, m_nSearchOptions))
						{
							ResultSearchData._nMatchedFiles = 1;
						}
					}
				}
			}
			else
			{
				GetDlgItem(ID_EDITOR_SEARCH_ALL)->SetWindowTextW(_T("Stop"));
				GetDlgItem(ID_EDITOR_SEARCH_NEXT)->EnableWindow(FALSE);
				GetDlgItem(ID_EDITOR_SEARCH_PREVIOUS)->EnableWindow(FALSE);
				// background search start...
				CString strMessageProgressbar;
				strMessageProgressbar.Format(_T("Searching text..."), strSearchWhat, m_strSpecificPath);
				m_pFindProgressBar = std::make_unique<CVinaTextProgressBar>(0, 100, strMessageProgressbar, PROGRESS_BAR_TYPE::TYPE_SEARCH);
				m_pFindProgressBar->SetPos(0);
				std::unique_ptr<CFindTextWorker> pFinder = std::make_unique<CFindTextWorker>();
				pFinder->SetTargetSearchFolder(m_strSpecificPath);
				pFinder->SetSearchWhat(strSearchWhat);
				pFinder->SetSearchOptions(m_nSearchOptions);
				pFinder->SetIncludeSubFolder(!m_bExcludeSubFolder);
				pFinder->SetFileFilter(m_strFileFilter);
				pFinder->SetParentWindow(this);
				DWORD dwExitCode = 0;
				CWinThread* pThread = ::AfxBeginThread(FindBackgroundThreadProc, (LPVOID)pFinder.get(), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED | THREAD_TERMINATE, NULL);
				if (pThread)
				{
					m_hThreadFindBackground = pThread->m_hThread;
					pThread->m_bAutoDelete = TRUE;
					pThread->ResumeThread();
				}
				while (TRUE)
				{
					if (!::GetExitCodeThread(m_hThreadFindBackground, &dwExitCode))
					{
						break;
					}
					if (dwExitCode != STILL_ACTIVE)
					{
						break;
					}
					USE_THREAD_PUMP_UI;
					if (m_pFindProgressBar && pFinder) // avoid crashing when stop searching
					{
						int nCurPos = pFinder->GetCurrentFindProgress();
						m_pFindProgressBar->SetPos(nCurPos);
						CString strMessageProgressbar;
						strMessageProgressbar.Format(_T("%s - %d%% completed..."), pFinder->GetCurrentSearchPath(), nCurPos);
						m_pFindProgressBar->SetText(strMessageProgressbar);
					}
				}
				m_hThreadFindBackground = NULL;
				m_pFindProgressBar.reset();
				// update result to main thread...
				ResultSearchData = pFinder->m_ResultSearchData;
				GetDlgItem(ID_EDITOR_SEARCH_ALL)->SetWindowTextW(_T("Search All"));
				GetDlgItem(ID_EDITOR_SEARCH_NEXT)->EnableWindow(TRUE);
				GetDlgItem(ID_EDITOR_SEARCH_PREVIOUS)->EnableWindow(TRUE);
			}
		}
		else
		{
			AfxMessageBox(_T("[Search In Path Error] specific path does not exist."));
			return;
		}
	}
	ResultSearchData._TimeMeasured = OSUtils::StopBenchmark(startMeasure);
	ResultSearchData._strSearchWhat = strSearchWhat;
	ResultSearchData._bAppendResult = m_bAppendResult;
	ResultSearchData._bShowFileNameOnly = m_bShowFileNameOnly;
	ResultSearchData._strScope = strSearchScope;
	// send data to log window
	pFrame->AddSearchResultDataToPane(ResultSearchData);
	m_comboSearchWhat.SetFocusEx();
}

void CFindDlg::OnClickCheckBoxRegex()
{
	UpdateData(TRUE);
	if (m_bMatchregex)
	{
		GetDlgItem(ID_EDITOR_SEARCH_REGEX_COMBO)->EnableWindow(TRUE);
		if (GetSearchWhat().IsEmpty())
		{
			OnCbnSelchangeRegexPattern();
		}
	}
	else
	{
		GetDlgItem(ID_EDITOR_SEARCH_REGEX_COMBO)->EnableWindow(FALSE);
	}
}

void CFindDlg::OnCbnSelchangeSearchScope()
{
	int iSel = m_comboSearchScope.GetCurSel();
	if (iSel == 3)
	{
		GetDlgItem(ID_EDITOR_SEARCH_PATH_SPECIFIC_EDIT)->EnableWindow(TRUE);
		GetDlgItem(ID_EDITOR_SEARCH_PATH_SPECIFIC_EDIT)->SetFocus();
	}
	else
	{
		GetDlgItem(ID_EDITOR_SEARCH_PATH_SPECIFIC_EDIT)->EnableWindow(FALSE);
	}

	if (iSel != 0)
	{
		GetDlgItem(ID_EDITOR_SEARCH_FILE_FILTER_EDIT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(ID_EDITOR_SEARCH_FILE_FILTER_EDIT)->EnableWindow(FALSE);
	}
}

void CFindDlg::OnCbnSelchangeRegexPattern()
{
	ComboboxRegexHelper::SetSearchFields(m_comboSearchWhat, m_combRegexPattern);
	OnSearchEditChange();
}

BOOL CFindDlg::OnEraseBkgnd(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);
	CBrush myBrush(AppSettingMgr.m_AppThemeColor); 
	CBrush *pOld = pDC->SelectObject(&myBrush);
	BOOL bRes = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
	pDC->SelectObject(pOld); 
	return bRes;
}

HBRUSH CFindDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_GROUPBOX
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_CHECK_MATCH_WHOLE
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_CHECK_MATCH_CASE
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_CHECK_REGEX
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_CHECK_EXCLUDE_SUB_FOLDER
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_SCOPE_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_FILE_FILTER_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_FILE_SPECIFIC_PATH_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_CHECK_APPEND_SEACH_RESULT
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_CHECK_SHOW_FILE_NAME
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_PATTERN_STATIC
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_NEXT
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_PREVIOUS
		|| pWnd->GetDlgCtrlID() == ID_EDITOR_SEARCH_ALL)
	{
		pDC->SetTextColor(IS_LIGHT_THEME ? BasicColors::black : BasicColors::white);
		pDC->SetBkMode(TRANSPARENT);
		return CreateSolidBrush(AppSettingMgr.m_AppThemeColor);
	}
	return hbr;
}

void CFindDlg::SaveSearchString(const CString& strSearch)
{
	if (strSearch.IsEmpty()) return;
	for (int i = 0; i < m_strSearchWhats.GetSize(); i++)
	{
		if (m_strSearchWhats.GetAt(i) == strSearch) return;
	}
	m_strSearchWhats.Add(strSearch);
	m_comboSearchWhat.InsertString(0, strSearch);
}

void CFindDlg::InitComboSearchScope()
{
	m_comboSearchScope.ResetContent();
	m_comboSearchScope.AddString(_T("Current File"));
	m_comboSearchScope.AddString(_T("All Opened Files"));
	m_comboSearchScope.AddString(_T("Container Folder"));
	m_comboSearchScope.AddString(_T("Specific Path"));
	//m_comboSearchScope.AddString(_T("Current Project"));
	m_comboSearchScope.SetCurSel(0);
}

void CFindDlg::InitComboRegexPattern()
{
	ComboboxRegexHelper::PopulateRegexFields(m_combRegexPattern);
}

// for scrolling //////////////////////////////////////////////////////////////

void CFindDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFindDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pScrollHelper->OnVScroll(nSBCode, nPos, pScrollBar);
}

BOOL CFindDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	BOOL wasScrolled = m_pScrollHelper->OnMouseWheel(nFlags, zDelta, pt);

	return wasScrolled;
}

void CFindDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	m_pScrollHelper->OnSize(nType, cx, cy);

	const std::vector<int> buttonIDs = { ID_EDITOR_SEARCH_NEXT, ID_EDITOR_SEARCH_PREVIOUS, ID_EDITOR_SEARCH_ALL };
	CRect rect; GetClientRect(&rect);
	GuiUtils::ResizeControlsHorizontally(this, buttonIDs, rect.Width(), rect.Height());
}

void CFindDlg::OnFilterEditChange()
{
	CString strSearchFilter;
	m_EditFilter.GetWindowText(strSearchFilter);
	if (strSearchFilter.IsEmpty())
	{
		m_EditFilter.SetWindowText(_T("*.*;"));
		m_EditFilter.SetFocusEx();
	}
}

void CFindDlg::SaveDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("advancesearch-dialog-state.json");
	JSonWriter jsonWriter(strJsonFilePath, "VinaText Advance Search Text Dialog Saved States");
	int nLimitData = 0;
	CString strSearchCBData;
	for (int i = 0; i < m_comboSearchWhat.GetCount(); ++i)
	{
		if (nLimitData > AppSettingMgr.m_nDialogComboboxLimitSave) break;
		CString strCurText;
		m_comboSearchWhat.GetLBText(i, strCurText);
		strSearchCBData += strCurText + SAPERATOR_JSON_DATA;
		nLimitData++;
	}
	jsonWriter.AddValue("combobox-search-data", AppUtils::CStringToStd(strSearchCBData));
	jsonWriter.SaveFile();
}

void CFindDlg::LoadDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("advancesearch-dialog-state.json");
	if (!PathFileExists(strJsonFilePath))
	{
		return;
	}
	JSonReader jsonReader(strJsonFilePath, "VinaText Advance Search Text Dialog Saved States");
	if (!jsonReader.LoadFile()) return;
	CString strSearchCBData;
	jsonReader.ReadCString("combobox-search-data", strSearchCBData);
	m_comboSearchWhat.ResetContent();
	CStringArray arrLine;
	AppUtils::SplitCString(strSearchCBData, SAPERATOR_JSON_DATA, arrLine);
	for (int i = arrLine.GetSize() - 1; i >= 0; --i)
	{
		CString strText = arrLine[i];
		if (strText.IsEmpty()) continue;
		if (m_comboSearchWhat.FindString(0, strText) < 0)
		{
			m_comboSearchWhat.InsertString(0, strText);
		}
	}
}

void CFindDlg::ClearAll()
{
	m_comboSearchWhat.ResetContent();
}

void CFindDlg::UpdateSearchOptions()
{
	UpdateData(TRUE);
	m_nSearchOptions = 0;
	if (m_bMatchwords)
		m_nSearchOptions |= SCFIND_WHOLEWORD;
	if (m_bMatchcase)
		m_nSearchOptions |= SCFIND_MATCHCASE;
	if (m_bMatchregex)
		m_nSearchOptions |= SCFIND_REGEXP;
}

CString CFindDlg::GetSearchWhat()
{
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	return strSearchWhat;
}

unsigned int CFindDlg::GetSearchOption()
{
	UpdateSearchOptions();
	return m_nSearchOptions;
}

void CFindDlg::EnableButtons(BOOL bEnable)
{
	GetDlgItem(ID_EDITOR_SEARCH_NEXT)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_SEARCH_PREVIOUS)->EnableWindow(bEnable);
	GetDlgItem(ID_EDITOR_SEARCH_ALL)->EnableWindow(bEnable);
}

ADVANCED_SEARCH_DATA CFindDlg::GetSycnFindReplaceSettings()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	ADVANCED_SEARCH_DATA dataSync;
	dataSync._strSearchWhat = strSearchWhat;
	dataSync._strSpecificPath = m_strSpecificPath;
	dataSync._bAppendResult = m_bAppendResult;
	dataSync._bExcludeSubFolder = m_bExcludeSubFolder;
	dataSync._bMacthregex = m_bMatchregex;
	dataSync._bMatchcase = m_bMatchcase;
	dataSync._bMatchwords = m_bMatchwords;
	dataSync._bShowFileNameOnly = m_bShowFileNameOnly;
	dataSync._strFileFilter = m_strFileFilter;
	dataSync._nRegexPattern = m_combRegexPattern.GetCurSel();
	dataSync._nSearchScope = m_comboSearchScope.GetCurSel();
	return dataSync;
}

void CFindDlg::SyncSearchReplaceSettings(const ADVANCED_SEARCH_DATA & settings)
{
	m_comboSearchWhat.SetWindowTextW(settings._strSearchWhat);
	m_comboSearchWhat.SetFocusEx();
	m_comboSearchScope.SetCurSel(settings._nSearchScope);
	m_combRegexPattern.SetCurSel(settings._nRegexPattern);
	OnCbnSelchangeSearchScope();
	SaveSearchString(settings._strSearchWhat);
	m_strSpecificPath = settings._strSpecificPath;
	m_bAppendResult = settings._bAppendResult;
	m_bExcludeSubFolder = settings._bExcludeSubFolder;
	m_bMatchregex = settings._bMacthregex;
	m_bMatchcase = settings._bMatchcase;
	m_bMatchwords = settings._bMatchwords;
	m_bShowFileNameOnly = settings._bShowFileNameOnly;
	m_strFileFilter = settings._strFileFilter;
	if (settings._strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		EnableButtons(TRUE);
	}
	UpdateData(FALSE);
	OnClickCheckBoxRegex();
}

void CFindDlg::UpdateUIVisual()
{
	GuiUtils::ForceRedrawCWnd(this);
}

void CFindDlg::OnSearchEditChange()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	m_comboSearchWhat.GetWindowText(strSearchWhat);
	if (strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		if (AppSettingMgr.m_bEnableAutoSearchWhenTyping)
		{
			DoSearchNext(strSearchWhat, TRUE, FALSE);
		}
		EnableButtons(TRUE);
	}
}

void CFindDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialogEx::OnDropFiles(hDropInfo);
	int nCntFiles = DragQueryFile(hDropInfo, -1, 0, 0);
	if (nCntFiles == 1)
	{
		TCHAR szPath[_MAX_PATH];
		szPath[0] = 0;
		::DragQueryFile(hDropInfo, 0, szPath, _MAX_PATH);
		if (PathUtils::IsDirectory(szPath))
		{
			InitSearchReplaceFromExplorer(szPath);
		}
		else
		{
			InitSearchReplaceFromExplorer(PathUtils::GetContainerPath(szPath));
		}
	}
	DragFinish(hDropInfo);
}

void CFindDlg::OnCbnSelchangeSearchEditCombo()
{
	UpdateData(TRUE);
	CString strSearchWhat;
	int index = m_comboSearchWhat.GetCurSel();
	if (index != CB_ERR)
	{
		m_comboSearchWhat.GetLBText(index, strSearchWhat);
	}
	if (strSearchWhat.IsEmpty())
	{
		EnableButtons(FALSE);
	}
	else
	{
		CEditorView* pView = dynamic_cast<CEditorView*>(AppUtils::GetMDIActiveView());
		if (AppSettingMgr.m_bEnableAutoSearchWhenTyping)
		{
			DoSearchNext(strSearchWhat, TRUE, FALSE);
		}
		EnableButtons(TRUE);
	}
}