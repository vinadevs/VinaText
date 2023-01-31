// MisspelledReplaceWithDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "MisspelledReplaceWithDlg.h"
#include "afxdialogex.h"
#include "AppUtil.h"
#include "EditorDoc.h"
#include "EditorView.h"

// MisspelledReplaceWithDlg dialog

IMPLEMENT_DYNAMIC(MisspelledReplaceWithDlg, CDlgBase)

MisspelledReplaceWithDlg::MisspelledReplaceWithDlg(CWnd* pParent /*=NULL*/)
	: CDlgBase(IDD_DIALOG_MISSPELLED_REPLACE, pParent)
	, m_strTartgetWord(_T(""))
{
}

MisspelledReplaceWithDlg::~MisspelledReplaceWithDlg()
{
}

void MisspelledReplaceWithDlg::SetSuggestionList(const std::vector<std::wstring>& suggestionList)
{
	m_suggestionList = suggestionList;
}

void MisspelledReplaceWithDlg::SetTargetWord(const CString & strTartgetWord)
{
	m_strTartgetWord = strTartgetWord;
}

void MisspelledReplaceWithDlg::DoDataExchange(CDataExchange* pDX)
{
	CDlgBase::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MISSPELLED_REPLACE, m_ListSuggestion);
	DDX_Text(pDX, IDC_EDIT_MISSPELLED_REPLACE, m_strTartgetWord);
}

BOOL MisspelledReplaceWithDlg::OnInitDialog()
{
	m_strDlgCaption = _T("Misspelled replace with...");

	CDlgBase::OnInitDialog();

	for (const auto& word : m_suggestionList)
	{
		m_ListSuggestion.AddString(AppUtils::WStdToCString(word));
	}

	UpdateData(FALSE);

	return TRUE;
}

BEGIN_MESSAGE_MAP(MisspelledReplaceWithDlg, CDlgBase)
	ON_BN_CLICKED(IDOK, &MisspelledReplaceWithDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &MisspelledReplaceWithDlg::OnBnClickedCancel)
	ON_LBN_DBLCLK(IDC_LIST_MISSPELLED_REPLACE, &MisspelledReplaceWithDlg::OnLbnDblclkListMisspelledReplace)
END_MESSAGE_MAP()

// MisspelledReplaceWithDlg message handlers

void MisspelledReplaceWithDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	DoReplace();
	CDlgBase::OnOK();
}

void MisspelledReplaceWithDlg::DoReplace()
{
	if (m_ListSuggestion.GetCount() == 0) return;
	int iSel = m_ListSuggestion.GetCurSel();
	if (iSel != LB_ERR)
	{
		CString strSelectedItem;
		m_ListSuggestion.GetText(iSel, strSelectedItem);
		if (!strSelectedItem.IsEmpty())
		{
			auto pEditorDoc = dynamic_cast<CEditorDoc*>(AppUtils::GetMDIActiveDocument());
			if (pEditorDoc)
			{
				auto pEditor = pEditorDoc->GetEditorCtrl();
				if (pEditor)
				{
					pEditor->ReplaceCurrentWord(strSelectedItem);
				}
			}
		}
	}
}

void MisspelledReplaceWithDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDlgBase::OnCancel();
}

void MisspelledReplaceWithDlg::OnLbnDblclkListMisspelledReplace()
{
	// TODO: Add your control notification handler code here
	DoReplace();
	CDlgBase::OnCancel();
}
