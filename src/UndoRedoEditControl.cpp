/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "UndoRedoEditControl.h"

//////////////////////////////////////////////////////////////////////////
// CUndoRedoEditControl::CInsertTextCommand

CUndoRedoEditControl::CInsertTextCommand::CInsertTextCommand(CUndoRedoEditControl* const pEditControl, const CString& text) 
	: CUndoRedoEditControlCommand(pEditControl)
	, m_text(text)
{
	int nEnd;
	pEditControl->GetSel(m_nStart, nEnd);
}

void CUndoRedoEditControl::CInsertTextCommand::DoUndo()
{
	m_pEditControl->DeleteText(m_nStart, m_text.GetLength());
	m_pEditControl->SetSel(m_nStart, m_nStart);
}

void CUndoRedoEditControl::CInsertTextCommand::DoExecute()
{
	m_pEditControl->InsertText(m_text, m_nStart);
	int nEnd = m_nStart + m_text.GetLength();
	m_pEditControl->SetSel(nEnd, nEnd);
}

//////////////////////////////////////////////////////////////////////////
// CUndoRedoEditControl::CDeleteSelectionCommand

CUndoRedoEditControl::CDeleteSelectionCommand::CDeleteSelectionCommand(CUndoRedoEditControl* const pEditControl, CursorOnUndo cursorOnUndo) 
	: CUndoRedoEditControlCommand(pEditControl)
	, m_textDeleted(pEditControl->GetSelectionText())
{
	m_pEditControl->GetSel(m_nStart, m_nEnd);
	m_cursorOnUndo = cursorOnUndo;
}

void CUndoRedoEditControl::CDeleteSelectionCommand::DoUndo()
{
	m_pEditControl->InsertText(m_textDeleted, m_nStart);
	switch (m_cursorOnUndo)
	{
	case Selection:
		m_pEditControl->SetSel(m_nStart, m_nEnd);
		break;
	case End:
		m_pEditControl->SetSel(m_nEnd, m_nEnd);
		break;
	case Start:
		m_pEditControl->SetSel(m_nStart, m_nStart);
		break;
	default:
		ASSERT(FALSE);
		break;
	}
}

void CUndoRedoEditControl::CDeleteSelectionCommand::DoExecute()
{
	m_pEditControl->DeleteText(m_nStart, m_nEnd - m_nStart);
	m_pEditControl->SetSel(m_nStart, m_nStart);
}

//////////////////////////////////////////////////////////////////////////
// CUndoRedoEditControl::CDeleteCharacterCommand

CUndoRedoEditControl::CDeleteCharacterCommand::CDeleteCharacterCommand(CUndoRedoEditControl* pEditControl, bool isBackspace) 
	: CUndoRedoEditControlCommand(pEditControl)
	, m_isBackspace(isBackspace)
{
	ASSERT(m_pEditControl->IsSelectionEmpty());
	m_pEditControl->GetSel(m_nStart, m_nStart);
	CString text;
	m_pEditControl->GetWindowText(text);
	if (m_isBackspace)
		--m_nStart;
	m_charDeleted = text[m_nStart];
}

void CUndoRedoEditControl::CDeleteCharacterCommand::DoUndo()
{
	m_pEditControl->InsertChar(m_charDeleted, m_nStart);
	if (m_isBackspace)
		m_pEditControl->SetSel(m_nStart + 1, m_nStart + 1);
	else
		m_pEditControl->SetSel(m_nStart, m_nStart);
}

void CUndoRedoEditControl::CDeleteCharacterCommand::DoExecute()
{
	m_pEditControl->DeleteText(m_nStart, 1);
	m_pEditControl->SetSel(m_nStart, m_nStart);
}

//////////////////////////////////////////////////////////////////////////
// CUndoRedoEditControl::CReplaceSelectionCommand

CUndoRedoEditControl::CReplaceSelectionCommand::CReplaceSelectionCommand(CUndoRedoEditControl* const pEditControl, const CString& text) 
	: CUndoRedoEditControlCommand(pEditControl)
{
	ASSERT(pEditControl->IsSelectionEmpty() == false);
	m_pDeleteCommand = new CDeleteSelectionCommand(pEditControl, CDeleteSelectionCommand::Selection);
	m_pInsertCommand = new CInsertTextCommand(pEditControl, text);
	ASSERT(m_pDeleteCommand != NULL);
	ASSERT(m_pInsertCommand != NULL);
}

CUndoRedoEditControl::CReplaceSelectionCommand::~CReplaceSelectionCommand()
{
	DELETE_POINTER_CPP(m_pDeleteCommand);
	DELETE_POINTER_CPP(m_pInsertCommand);
}

void CUndoRedoEditControl::CReplaceSelectionCommand::DoUndo()
{
	m_pInsertCommand->Undo();
	m_pDeleteCommand->Undo();
}

void CUndoRedoEditControl::CReplaceSelectionCommand::DoExecute()
{
	m_pDeleteCommand->Execute();
	m_pInsertCommand->Execute();
}

//////////////////////////////////////////////////////////////////////////
// CUndoRedoEditControl::CSetTextCommand

CUndoRedoEditControl::CSetTextCommand::CSetTextCommand(CUndoRedoEditControl* const pEditControl) 
	: CUndoRedoEditControlCommand(pEditControl)
{
	pEditControl->GetWindowText(m_textReplaced);
}

CUndoRedoEditControl::CSetTextCommand::~CSetTextCommand()
{
}

void CUndoRedoEditControl::CSetTextCommand::DoUndo()
{
	DoExecute();
}

void CUndoRedoEditControl::CSetTextCommand::DoExecute()
{
	CString currentText;
	m_pEditControl->GetWindowText(currentText);
	m_pEditControl->SendMessage(WM_SETTEXT, (WPARAM)m_pEditControl->m_hWnd, (LPARAM)(m_textReplaced.GetBuffer()));
	m_pEditControl->SetSel(0, -1);
	m_textReplaced = currentText;
}

//////////////////////////////////////////////////////////////////////////
// CUndoRedoEditControl::CCommandHistory

CUndoRedoEditControl::CCommandHistory::CCommandHistory()
{
}

CUndoRedoEditControl::CCommandHistory::~CCommandHistory()
{
	DestroyUndoCommands();
	DestroyRedoCommands();
}

void CUndoRedoEditControl::CCommandHistory::AddCommand(CUndoRedoEditControlCommand* pCommand)
{
	m_undoCommands.push(pCommand);
	DestroyRedoCommands();
}

bool CUndoRedoEditControl::CCommandHistory::Undo()
{
	if (!IsAllowUndo())
		return false;
	CUndoRedoEditControlCommand* pCommand = m_undoCommands.top();
	pCommand->Undo();
	m_undoCommands.pop();
	m_redoCommands.push(pCommand);
	return true;
}

bool CUndoRedoEditControl::CCommandHistory::Redo()
{
	if (!IsAllowRedo())
		return false;
	CUndoRedoEditControlCommand* pCommand = m_redoCommands.top();
	pCommand->Execute();
	m_redoCommands.pop();
	m_undoCommands.push(pCommand);
	return true;
}

bool CUndoRedoEditControl::CCommandHistory::IsAllowUndo() const
{
	return m_undoCommands.empty() == false;
}

bool CUndoRedoEditControl::CCommandHistory::IsAllowRedo() const
{
	return m_redoCommands.empty() == false;
}

void CUndoRedoEditControl::CCommandHistory::DestroyCommands(CommandStack& stack)
{
	while (!stack.empty())
	{
		CUndoRedoEditControlCommand* pCommand = stack.top();
		delete pCommand;
		stack.pop();
	}
}

void CUndoRedoEditControl::CCommandHistory::DestroyUndoCommands()
{
	DestroyCommands(m_undoCommands);
}

void CUndoRedoEditControl::CCommandHistory::DestroyRedoCommands()
{
	DestroyCommands(m_redoCommands);
}


//////////////////////////////////////////////////////////////////////////
// CUndoRedoEditControl implementation

IMPLEMENT_DYNAMIC(CUndoRedoEditControl, CEdit)

CUndoRedoEditControl::CUndoRedoEditControl()
{
	m_contextMenuShownFirstTime = false;
}

CUndoRedoEditControl::~CUndoRedoEditControl()
{
}

// public methods

inline bool CUndoRedoEditControl::IsMultiLine() const
{
	return (GetStyle() & ES_MULTILINE) == ES_MULTILINE;
}

inline bool CUndoRedoEditControl::IsSelectionEmpty() const
{
	int nStart, nEnd;
	GetSel(nStart, nEnd);
	return nEnd == nStart;
}

int CUndoRedoEditControl::GetCursorPosition() const
{
	ASSERT(IsSelectionEmpty());
	return GetSel() & 0xFFFF;
}

CString CUndoRedoEditControl::GetSelectionText() const 
{
	CString text;
	GetWindowText(text);
	int nStart, nEnd;
	GetSel(nStart, nEnd);
	return text.Mid(nStart, nEnd - nStart);
}

void CUndoRedoEditControl::SetFocusEx(BOOL bSelectText)
{
	SetFocus();
	SetSel(0, -1); // select all text and move cursor at the end
	if (!bSelectText) {
		SetSel(-1); // remove selection
	}
}

void CUndoRedoEditControl::ReplaceSel(LPCTSTR lpszNewText, BOOL bIsAllowUndo /*= FALSE*/)
{
	if (bIsAllowUndo)
		CreateInsertTextCommand(lpszNewText);
	CEdit::ReplaceSel(lpszNewText, bIsAllowUndo);
}

BOOL CUndoRedoEditControl::Undo()
{
	return m_commandHistory.Undo();
}

BOOL CUndoRedoEditControl::Redo()
{
	return m_commandHistory.Redo();
}

BOOL CUndoRedoEditControl::IsAllowUndo() const
{
	return m_commandHistory.IsAllowUndo();
}

BOOL CUndoRedoEditControl::IsAllowRedo() const
{
	return m_commandHistory.IsAllowRedo();
}

// command pattern receiver methods

void CUndoRedoEditControl::InsertText(const CString& textToInsert, int nStart)
{
	ASSERT(nStart <= GetWindowTextLength());
	CString text;
	GetWindowText(text);
	text.Insert(nStart, textToInsert);
	SendMessage(WM_SETTEXT, (WPARAM)m_hWnd, (LPARAM)text.GetString());
}

void CUndoRedoEditControl::InsertChar(TCHAR charToInsert, int nStart)
{
	ASSERT(nStart <= GetWindowTextLength());
	CString text;
	GetWindowText(text);
	text.Insert(nStart, charToInsert);
	SendMessage(WM_SETTEXT, (WPARAM)m_hWnd, (LPARAM)text.GetString());
}

void CUndoRedoEditControl::DeleteText(int nStart, int nLen)
{
	ASSERT(nLen > 0);
	ASSERT(GetWindowTextLength() > 0);
	CString text;
	GetWindowText(text);
	text.Delete(nStart, nLen);
	SendMessage(WM_SETTEXT, (WPARAM)m_hWnd, (LPARAM)text.GetString());
}

// CUndoRedoEditControl overrides

// intercept commands to add them to the history
BOOL CUndoRedoEditControl::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		if (PreTranslateKeyDownMessage(pMsg->wParam) == TRUE)
			return TRUE;
		break;
	case WM_SYSCHAR:
		// Alt + Back
		if (pMsg->wParam == VK_BACK)
		{
			// for single-line Alt + Back generates WM_UNDO message but not for multiline!
			// Therefore we need to capture this keyboard shortcut for multiline control
			if (IsMultiLine())
				DoUndo();
			return TRUE;
		}
		break;
	}
	return CEdit::PreTranslateMessage(pMsg);
}

// intercept commands to add them to the history
LRESULT CUndoRedoEditControl::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CHAR:
		{
			wchar_t wChar = static_cast<wchar_t>(wParam);
			int nCount = lParam & 0xFF;
			if (iswprint(wChar))
			{
				CString newText(wChar, nCount);
				CreateInsertTextCommand(newText);
			}
			// special case for Unicode control characters inserted from the context menu
			else if (nCount == 0)
			{
				CString newText(wChar);
				CreateInsertTextCommand(newText);
			}
		}
		break;
	case WM_PASTE:
		CreatePasteCommand();
		try 
		{
			ReplaceSel(m_pText);
		}
		catch (...) 
		{
			return FALSE;
		}
		return TRUE;
	case WM_CUT:
	case WM_CLEAR: // delete command from context menu
		if (!IsSelectionEmpty())
			m_commandHistory.AddCommand(new CDeleteSelectionCommand(this, CDeleteSelectionCommand::Selection));
		break;
	case WM_UNDO:
		DoUndo();
		return TRUE; // we did the undo and shouldn't pass the message to base class
	case ID_EDIT_REDO:
		Redo();
		return TRUE;
	case WM_SETTEXT:
		// add event to history only if control is already visible (to prevent 
		// initial call of DDX_Text to be added to command history) and 
		// if message has been sent from outside the control (i.e. wParam is NULL)
		if (IsWindowVisible() && (HWND)wParam != m_hWnd)
			m_commandHistory.AddCommand(new CSetTextCommand(this));
		break;
	}
	return CEdit::WindowProc(message, wParam, lParam);
}


BEGIN_MESSAGE_MAP(CUndoRedoEditControl, CEdit)
	ON_WM_CONTEXTMENU()
	ON_WM_ENTERIDLE()
END_MESSAGE_MAP()

// CUndoRedoEditControl message handlers

// sets the flag used to update context menu state
void CUndoRedoEditControl::OnContextMenu(CWnd* pWnd, CPoint point)
{
	m_contextMenuShownFirstTime = true;
	CEdit::OnContextMenu(pWnd, point);
}

void CUndoRedoEditControl::OnEnterIdle(UINT nWhy, CWnd* pWho)
{
	CEdit::OnEnterIdle(nWhy, pWho);
	if (nWhy == MSGF_MENU)
	{
		// update context menu only first time it is displayed
		if (m_contextMenuShownFirstTime)
		{
			m_contextMenuShownFirstTime = false;
			UpdateContextMenuItems(pWho);
		}
	}
}

// CUndoRedoEditControl private methods

BOOL CUndoRedoEditControl::PreTranslateKeyDownMessage(WPARAM wParam)
{
	switch (wParam) 
	{
	case _T('A'):
		// Ctrl + 'A'
		if ((GetKeyState(VK_CONTROL) & 0x8000) != 0)
		{
			SetSel(0, -1);
			return TRUE;
		}
		break;
	case _T('Z'):
		// Ctrl + 'Z'
		if ((GetKeyState(VK_CONTROL) & 0x8000) != 0)
		{
			Undo();
			return TRUE;
		}
		break;
	case _T('Y'):
		// Ctrl + 'Y'
		if ((GetKeyState(VK_CONTROL) & 0x8000) != 0)
		{
			Redo();
			return TRUE;
		}
		break;
	case VK_BACK:
		return DoBackspace();
	case VK_DELETE:
		return DoDelete();
	}
	return FALSE;
}

void CUndoRedoEditControl::CreateInsertTextCommand(const CString& newText)
{
	if (IsSelectionEmpty())
		m_commandHistory.AddCommand(new CInsertTextCommand(this, newText));
	else
		m_commandHistory.AddCommand(new CReplaceSelectionCommand(this, newText));
}

BOOL CUndoRedoEditControl::CreatePasteCommand()
{
	if (!OpenClipboard())
		return FALSE;

#ifdef UNICODE
	HANDLE hglb = ::GetClipboardData(CF_UNICODETEXT);
#else
	HANDLE hglb = ::GetClipboardData(CF_TEXT);
#endif
	if (hglb == NULL)
	{
		CloseClipboard(); 
		return FALSE;
	}
	m_pText = reinterpret_cast<LPTSTR>(::GlobalLock(hglb));
	if (m_pText != NULL)
	{
		CreateInsertTextCommand(m_pText);
		::GlobalUnlock(hglb);
	}
	CloseClipboard(); 
	return TRUE;
}

BOOL CUndoRedoEditControl::DoDelete()
{
	if ((GetKeyState(VK_CONTROL) & 0x8000) != 0)
	{
		// Ctrl + Delete + Shift
		if ((GetKeyState(VK_SHIFT) & 0x8000) != 0)
			DeleteToTheEnd();
		// Ctrl + Delete
		else
			DeleteToTheBeginningOfNextWord();
		return TRUE;
	}
	// simple delete
	if (IsSelectionEmpty() == false)
		m_commandHistory.AddCommand(new CDeleteSelectionCommand(this, CDeleteSelectionCommand::Selection));
	else
	{
		if (GetCursorPosition() < GetWindowTextLength())
			m_commandHistory.AddCommand(new CDeleteCharacterCommand(this, false));
	}
	return FALSE;
}

BOOL CUndoRedoEditControl::DoBackspace()
{
	if ((GetKeyState(VK_CONTROL) & 0x8000) != 0) 
	{
		if ((GetKeyState(VK_SHIFT) & 0x8000) != 0)
			// Ctrl + Shift + Back
			DeleteFromTheBeginning();
		else
			// Ctrl + Back
			DeleteFromTheBeginningOfWord();
		return TRUE;
	}
	// plain Back
	if (IsSelectionEmpty() == false)
		m_commandHistory.AddCommand(new CDeleteSelectionCommand(this, CDeleteSelectionCommand::Selection));
	else
	{
		if (GetCursorPosition() > 0)
			m_commandHistory.AddCommand(new CDeleteCharacterCommand(this, true));
	}
	return FALSE;
}

void CUndoRedoEditControl::DoUndo()
{
	// Alt + Shift + Back also generates WM_UNDO so we must distinguish it to execute redo operation
	if ((GetKeyState(VK_BACK) & 0x8000) & (GetKeyState(VK_SHIFT) & 0x8000))
	{
		ASSERT(GetKeyState(VK_MENU) & 0x8000);
		Redo();
	}
	else
		Undo();
}

// Deletes characters from the start of the content up
// to the end of selection
void CUndoRedoEditControl::DeleteFromTheBeginning()
{
	int nStart, nEnd;
	GetSel(nStart, nEnd);
	if (nEnd == 0)
		return;
	SetSel(0, nEnd);
	CUndoRedoEditControlCommand* pCommand = new CDeleteSelectionCommand(this, CDeleteSelectionCommand::End);
	m_commandHistory.AddCommand(pCommand);
	pCommand->Execute();
}

// Deletes characters from the start of the selection 
// to the end of content
void CUndoRedoEditControl::DeleteToTheEnd()
{
	int nStart, nEnd;
	GetSel(nStart, nEnd);
	nEnd = GetWindowTextLength();
	if (nStart == nEnd)
		return;
	SetSel(nStart, nEnd);
	CUndoRedoEditControlCommand* pCommand = new CDeleteSelectionCommand(this, CDeleteSelectionCommand::Start);
	m_commandHistory.AddCommand(pCommand);
	pCommand->Execute();
}

// Gets character category
CUndoRedoEditControl::CharCategory CUndoRedoEditControl::GetCharCategory(TCHAR ch)
{
	if (::_istspace(ch))
		return enumSpace;
	if (::_istpunct(ch))
		return enumPunctuation;
	return enumAlphaNum;
}

// Extends start of selection to include characters of the same category
void CUndoRedoEditControl::ExtendSelectionToStartOfCharacterBlock(int nStart, int nEnd) 
{
	ASSERT(nStart > 0);
	ASSERT(nEnd >= nEnd);
	CString text;
	GetWindowText(text);
	// skip trailing whitespaces
	while (--nStart > 0)
	{
		if (!_istspace(text[nStart]))
			break;
	}
	// find start of block with the same character category
	CharCategory blockCharCategory = GetCharCategory(text[nStart]);
	while (nStart > 0)
	{
		--nStart;
		if (blockCharCategory != GetCharCategory(text[nStart]))
		{
			++nStart;
			break;
		}
	}
	ASSERT(nStart >= 0 && nEnd >= nEnd);
	SetSel(nStart, nEnd, TRUE);
}

// Extends end of selection to include characters of the same category
void CUndoRedoEditControl::ExtendSelectionToEndOfCharacterBlock(int nStart, int nEnd) 
{
	CString text;
	GetWindowText(text);
	CharCategory blockCharCategory = GetCharCategory(text[nEnd]);
	int len = text.GetLength();
	while (++nEnd < len) 
	{
		if (blockCharCategory != GetCharCategory(text[nEnd]))
			break;
	}
	// skip trailing whitespaces
	while (nEnd < len) 
	{
		if (!_istspace(text[nEnd]))
			break;
		++nEnd;
	}
	ASSERT(nEnd >= nStart && nEnd <= len);
	SetSel(nStart, nEnd, TRUE);
}

// Deletes characters from the beginning of the block
// consisting of characters of the same category as
// the first character in the selection
void CUndoRedoEditControl::DeleteFromTheBeginningOfWord()
{
	int nStart, nEnd;
	GetSel(nStart, nEnd);
	ASSERT(nStart <= nEnd);
	if (nStart == 0)
		return;
	ExtendSelectionToStartOfCharacterBlock(nStart, nEnd);
	CUndoRedoEditControlCommand* pCommand = new CDeleteSelectionCommand(this, CDeleteSelectionCommand::End);
	m_commandHistory.AddCommand(pCommand);
	pCommand->Execute();
}

// Deletes characters to the end of the block
// consisting of characters of the same category as
// the last character in the selection
void CUndoRedoEditControl::DeleteToTheBeginningOfNextWord()
{
	int nStart, nEnd;
	GetSel(nStart, nEnd);
	ASSERT(nStart <= nEnd);
	if (GetWindowTextLength() <= nEnd)
		return;
	ExtendSelectionToEndOfCharacterBlock(nStart, nEnd);
	CUndoRedoEditControlCommand* pCommand = new CDeleteSelectionCommand(this, CDeleteSelectionCommand::Start);
	m_commandHistory.AddCommand(pCommand);
	pCommand->Execute();
}

// updates Undo menu item state, adds Redo command and
// displays keyboard shortcuts
void CUndoRedoEditControl::UpdateContextMenuItems(CWnd* pWnd)
{
	MENUBARINFO mbi = {0};
	mbi.cbSize = sizeof(MENUBARINFO);
	::GetMenuBarInfo(pWnd->m_hWnd, OBJID_CLIENT, 0, &mbi);
	ASSERT(::IsMenu(mbi.hMenu));
	HMENU hMenu = mbi.hMenu;
	CMenu* pMenu = CMenu::FromHandle(hMenu);
	if (m_commandHistory.IsAllowUndo())
		pMenu->EnableMenuItem(WM_UNDO, MF_BYCOMMAND | MF_ENABLED);
	else
		pMenu->EnableMenuItem(WM_UNDO, MF_BYCOMMAND | MF_GRAYED);

	int pos = FindMenuPos(pMenu, WM_UNDO);
	if (pos == -1)
		return;

	static TCHAR* strRedo = _T("&Redo");
	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_ID | MIIM_STATE | MIIM_STRING;
	mii.fType = MFT_STRING;
	mii.fState = m_commandHistory.IsAllowRedo() ? MF_ENABLED : MF_DISABLED;
	mii.wID = ID_EDIT_REDO;
	mii.dwTypeData = strRedo;
	mii.cch = static_cast<UINT>(_tclen(strRedo));
	VERIFY(pMenu->InsertMenuItem(pos + 1, &mii, TRUE));

	AppendKeyboardShortcuts(pMenu, WM_UNDO, _T("Ctrl+Z"));
	AppendKeyboardShortcuts(pMenu, ID_EDIT_REDO, _T("Ctrl+Y"));
	AppendKeyboardShortcuts(pMenu, WM_CUT, _T("Ctrl+X"));
	AppendKeyboardShortcuts(pMenu, WM_COPY, _T("Ctrl+C"));
	AppendKeyboardShortcuts(pMenu, WM_PASTE, _T("Ctrl+V"));
	AppendKeyboardShortcuts(pMenu, WM_CLEAR, _T("Del"));
	AppendKeyboardShortcuts(pMenu, EM_SETSEL, _T("Ctrl+A"));
}

UINT CUndoRedoEditControl::FindMenuPos(CMenu* pMenu, UINT myID)
{
	for (UINT pos = pMenu->GetMenuItemCount() - 1; pos >= 0; --pos)
	{
		MENUITEMINFO mii;
		mii.cbSize = sizeof(MENUITEMINFO);
		mii.fMask = MIIM_ID;
		if (pMenu->GetMenuItemInfo(pos, &mii, TRUE) == FALSE)
			return -1;

		if (mii.wID == myID)
			return pos;
	}
	return -1;
}

void CUndoRedoEditControl::AppendKeyboardShortcuts(CMenu* pMenu, UINT id, LPCTSTR shortcut)
{
	CString caption;
	if (pMenu->GetMenuString(id, caption, MF_BYCOMMAND) == 0)
		return;

	caption.AppendFormat(_T("\t%s"), shortcut);
	MENUITEMINFO mii;
	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_STRING;
	mii.fType = MFT_STRING;
	mii.dwTypeData = caption.GetBuffer();
	mii.cch = caption.GetLength();
	pMenu->SetMenuItemInfo(id, &mii);
}
