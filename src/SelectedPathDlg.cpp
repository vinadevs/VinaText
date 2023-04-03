/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "Resource.h"
#include "SelectedPathDlg.h"
#include "MainFrm.h"
#include "FileUtil.h"
#include "AppSettings.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif //#ifdef _DEBUG

#pragma warning(suppress: 26455)

IMPLEMENT_DYNAMIC(CSelectedPathDlg, CDlgBase)

CSelectedPathDlg::CSelectedPathDlg(CWnd* pParent) 
	: CDlgBase(CSelectedPathDlg::IDD, pParent)
{
}

void CSelectedPathDlg::OnCancel()
{
	SaveDialogState();
	CDlgBase::OnCancel();
}

void CSelectedPathDlg::DoDataExchange(CDataExchange* pDX)
{
  //Let the base class do its thing
  CDlgBase::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_COMBO_GOTO_PATH, m_ComboEditPath);
  DDX_Check(pDX, IDC_EXPANDED, m_bExpandChildPath);
}

void CSelectedPathDlg::SaveSearchPath(const CString & strSearchPath)
{
	if (strSearchPath.IsEmpty()) return;
	for (int i = 0; i < m_SearchPathArr.GetSize(); i++)
	{
		if (m_SearchPathArr.GetAt(i) == strSearchPath) return;
	}
	m_SearchPathArr.Add(strSearchPath);
	m_ComboEditPath.InsertString(0, strSearchPath);
}

void CSelectedPathDlg::SaveDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("gotopath-dialog-state.json");
	JSonWriter jsonWriter(strJsonFilePath, "VinaText Goto Path Dialog Saved States");
	int nLimitData = 0;
	CString strSearchCBData;
	for (int i = 0; i < m_ComboEditPath.GetCount(); ++i)
	{
		if (nLimitData > AppSettingMgr.m_nDialogComboboxLimitSave) break;
		CString strCurText;
		m_ComboEditPath.GetLBText(i, strCurText);
		strSearchCBData += strCurText + SAPERATOR_JSON_DATA;
		nLimitData++;
	}
	jsonWriter.AddValue("combobox-path-data", AppUtils::CStringToStd(strSearchCBData));
	jsonWriter.SaveFile();
}

void CSelectedPathDlg::LoadDialogState()
{
	CString strJsonFilePath = PathUtils::GetVinaTextAppDataPath() + _T("gotopath-dialog-state.json");
	if (!PathFileExists(strJsonFilePath))
	{
		return;
	}
	JSonReader jsonReader(strJsonFilePath, "VinaText Goto Path Dialog Saved States");
	if (!jsonReader.LoadFile()) return;
	CString strSearchCBData;
	jsonReader.ReadCString("combobox-path-data", strSearchCBData);
	m_ComboEditPath.ResetContent();
	CStringArray arrLine;
	AppUtils::SplitCString(strSearchCBData, SAPERATOR_JSON_DATA, arrLine);
	for (auto i = arrLine.GetSize() - 1; i >= 0; --i)
	{
		CString strText = arrLine[i];
		if (strText.IsEmpty()) continue;
		if (m_ComboEditPath.FindString(0, strText) < 0)
		{
			m_ComboEditPath.InsertString(0, strText);
			m_SearchPathArr.Add(strText);
		}
	}
}

BOOL CSelectedPathDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Please enter the path to go...");
	CDlgBase::OnInitDialog();
	LoadDialogState();
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (pFrame)
	{
		CString strSelectedPath = pFrame->GetFileExplorerCtrl().GetSelectedPath();
		if (PathUtils::IsDirectory(strSelectedPath))
		{
			strSelectedPath += _T("\\");
		}
		m_ComboEditPath.SetWindowTextW(strSelectedPath);
		SaveSearchPath(strSelectedPath);
	}
	UpdateData(FALSE);
	SET_FOCUS_ON_CHILD_DLG_CONTROL(m_ComboEditPath);
	return FALSE;
}

#pragma warning(suppress: 26433 26440)
BEGIN_MESSAGE_MAP(CSelectedPathDlg, CDlgBase) 
	ON_BN_CLICKED(IDOK, &CSelectedPathDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CSelectedPathDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strPath;
	m_ComboEditPath.GetWindowText(strPath);
	SaveSearchPath(strPath);
	CMainFrame* pFrame = DYNAMIC_DOWNCAST(CMainFrame, AfxGetMainWnd());
	ASSERT(pFrame);
	if (!pFrame) return;
	if (PathIsRelative(strPath))
	{
		strPath = PathUtils::GetAbsolutePath(strPath);
	}
	HTREEITEM hItemFound = pFrame->GetFileExplorerCtrl().SetSelectedPath(strPath, m_bExpandChildPath);
	if (hItemFound)
	{
		pFrame->GetFileExplorerCtrl().EnsureVisibleCenter(hItemFound);
	}
	else
	{
		AfxMessageBox(_T("[Path Error] Input path does not exist!"));
	}
}
