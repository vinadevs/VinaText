/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

// CUndoRedoEditControl

class CUndoRedoEditControl : public CEdit
{
	// commands

	// abstract base class
	class CUndoRedoEditControlCommand
	{
	public:
		CUndoRedoEditControlCommand(CUndoRedoEditControl* const pEditControl) : m_pEditControl(pEditControl) {}
		virtual ~CUndoRedoEditControlCommand() {}

		void Undo() { DoUndo(); }
		void Execute() { DoExecute(); }

	protected:
		virtual void DoUndo() = 0;
		virtual void DoExecute() = 0;

		CUndoRedoEditControl* const m_pEditControl;
	};

	class CInsertTextCommand : public CUndoRedoEditControlCommand
	{
	public:
		CInsertTextCommand(CUndoRedoEditControl* const pEditControl, const CString& text);
	protected:
		virtual void DoUndo();
		virtual void DoExecute();
	private:
		CString m_text;
		int m_nStart;
	};

	class CDeleteSelectionCommand : public CUndoRedoEditControlCommand
	{
	public:
		enum CursorOnUndo {
			Start,
			End,
			Selection
		};

		CDeleteSelectionCommand(CUndoRedoEditControl* const pEditControl, CursorOnUndo cursorOnUndo);
	protected:
		virtual void DoUndo();
		virtual void DoExecute();
	private:
		int m_nStart;
		int m_nEnd;
		CString m_textDeleted;
		CursorOnUndo m_cursorOnUndo;
	};

	class CDeleteCharacterCommand : public CUndoRedoEditControlCommand
	{
	public:
		CDeleteCharacterCommand(CUndoRedoEditControl* pEditControl, bool isBackspace);
	protected:
		virtual void DoUndo();
		virtual void DoExecute();
	private:
		TCHAR m_charDeleted;
		int m_nStart;
		bool m_isBackspace;
	};

	class CReplaceSelectionCommand : public CUndoRedoEditControlCommand
	{
	public:
		CReplaceSelectionCommand(CUndoRedoEditControl* const pEditControl, const CString& text);
		virtual ~CReplaceSelectionCommand();
	protected:
		virtual void DoUndo();
		virtual void DoExecute();
	private:
		CDeleteSelectionCommand* m_pDeleteCommand;
		CInsertTextCommand* m_pInsertCommand;
	};

	class CSetTextCommand : public CUndoRedoEditControlCommand
	{
	public:
		CSetTextCommand(CUndoRedoEditControl* const pEditControl);
		virtual ~CSetTextCommand();
	protected:
		virtual void DoUndo();
		virtual void DoExecute();
	private:
		CString m_textReplaced;
	};

	// command history

	class CCommandHistory
	{
	public:
		CCommandHistory();
		~CCommandHistory();

		void AddCommand(CUndoRedoEditControlCommand* pCommand);
		bool Undo();
		bool Redo();

		bool IsAllowUndo() const;
		bool IsAllowRedo() const;

	private:
		typedef std::stack<CUndoRedoEditControlCommand*> CommandStack;

		CommandStack m_undoCommands;
		CommandStack m_redoCommands;

		void DestroyCommands(CommandStack& stack);
		void DestroyUndoCommands();
		void DestroyRedoCommands();
	};

	// CUndoRedoEditControl definition

	DECLARE_DYNAMIC(CUndoRedoEditControl)

public:
	CUndoRedoEditControl();
	virtual ~CUndoRedoEditControl();

public:
	bool IsMultiLine() const;
	bool IsSelectionEmpty() const;
	int GetCursorPosition() const;
	CString GetSelectionText() const;
	void SetFocusEx();

	void ReplaceSel(LPCTSTR lpszNewText, BOOL bIsAllowUndo = FALSE);

	BOOL Undo();
	BOOL Redo();
	BOOL IsAllowUndo() const;
	BOOL IsAllowRedo() const;

	// command pattern receiver methods
	void InsertText(const CString& textToInsert, int nStart);
	void InsertChar(TCHAR charToInsert, int nStart);
	void DeleteText(int nStart, int nLen);

public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnEnterIdle(UINT nWhy, CWnd* pWho);

protected:
	void CreateInsertTextCommand(const CString& newText);
	BOOL PreTranslateKeyDownMessage(WPARAM wParam);

	BOOL CreatePasteCommand();
	BOOL DoDelete();
	BOOL DoBackspace();
	void DoUndo();

	enum CharCategory
	{
		enumSpace,
		enumPunctuation,
		enumAlphaNum
	};

	void DeleteFromTheBeginning();
	void DeleteToTheEnd();

	CharCategory GetCharCategory(TCHAR ch);
	void ExtendSelectionToStartOfCharacterBlock(int nStart, int nEnd);
	void ExtendSelectionToEndOfCharacterBlock(int nStart, int nEnd);
	void DeleteFromTheBeginningOfWord();
	void DeleteToTheBeginningOfNextWord();

	void UpdateContextMenuItems(CWnd* pWnd);
	UINT FindMenuPos(CMenu* pMenu, UINT myID);
	void AppendKeyboardShortcuts(CMenu* pMenu, UINT id, LPCTSTR shortcut);

	CCommandHistory m_commandHistory;
	bool m_contextMenuShownFirstTime;
	LPTSTR m_pText;
};
