/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include "ComboboxRegexHelper.h"

void ComboboxRegexHelper::PopulateRegexFields(CComboBox& comboBox)
{
	comboBox.ResetContent();
	comboBox.AddString(_T("Match any character one time"));
	comboBox.AddString(_T("Match any character zero or more times (wildcard *)"));
	comboBox.AddString(_T("Match any character one or more times (wildcard ?)"));
	comboBox.AddString(_T("Match any single character in the set 'abc'"));
	comboBox.AddString(_T("Match any single character not in the set 'abc'"));
	comboBox.AddString(_T("Match any single character in range a to f"));
	comboBox.AddString(_T("Match any word character"));
	comboBox.AddString(_T("Match any decimal digit"));
	comboBox.AddString(_T("Match any whitespace character"));
	comboBox.AddString(_T("Match any character zero or one time"));
	comboBox.AddString(_T("Match any character zero or more times"));
	comboBox.AddString(_T("Match any character one or more times"));
	comboBox.AddString(_T("Match three consecutive decimal digits"));
	comboBox.AddString(_T("Match at beginning or end of word"));
	comboBox.AddString(_T("Match at beginning of line"));
	comboBox.AddString(_T("Match a line break"));
	comboBox.AddString(_T("Match at end of line"));
	comboBox.AddString(_T("Capture and impicitily number the subexpression 'dog|cat'"));
	comboBox.AddString(_T("Backreference the first captured subexpression"));
	comboBox.AddString(_T("Capture subexpression 'dog|cat' and name it 'pet'"));
	comboBox.AddString(_T("Backreference the captured subexpression named 'pet'"));
	comboBox.AddString(_T("Space or Tab"));
	comboBox.AddString(_T("Match any numeric character"));
	comboBox.AddString(_T("C/C++ identifier"));
	comboBox.AddString(_T("Quoted string"));
	comboBox.AddString(_T("Match a hexadecimal number"));
	comboBox.AddString(_T("Match integer and decimals"));
	comboBox.SetCurSel(0);
}

void ComboboxRegexHelper::SetSearchFields(CComboBox& comboBox, CComboBox& comboBoxRegex)
{
	int iSel = comboBoxRegex.GetCurSel();
	if (iSel == 0)
	{
		comboBox.SetWindowTextW(_T("."));
	}
	else if (iSel == 1)
	{
		comboBox.SetWindowTextW(_T(".*"));
	}
	else if (iSel == 2)
	{
		comboBox.SetWindowTextW(_T(".+"));
	}
	else if (iSel == 3)
	{
		comboBox.SetWindowTextW(_T("[abc]"));
	}
	else if (iSel == 4)
	{
		comboBox.SetWindowTextW(_T("^[abc]"));
	}
	else if (iSel == 5)
	{
		comboBox.SetWindowTextW(_T("[a-f]"));
	}
	else if (iSel == 6)
	{
		comboBox.SetWindowTextW(_T("\\w"));
	}
	else if (iSel == 7)
	{
		comboBox.SetWindowTextW(_T("\\d"));
	}
	else if (iSel == 8)
	{
		comboBox.SetWindowTextW(_T("[^\\S\\r\\n]"));
	}
	else if (iSel == 9)
	{
		comboBox.SetWindowTextW(_T("be?"));
	}
	else if (iSel == 10)
	{
		comboBox.SetWindowTextW(_T("be*"));
	}
	else if (iSel == 11)
	{
		comboBox.SetWindowTextW(_T("be+"));
	}
	else if (iSel == 12)
	{
		comboBox.SetWindowTextW(_T("\\d{3}"));
	}
	else if (iSel == 13)
	{
		comboBox.SetWindowTextW(_T("\\b"));
	}
	else if (iSel == 14)
	{
		comboBox.SetWindowTextW(_T("^"));
	}
	else if (iSel == 15)
	{
		comboBox.SetWindowTextW(_T("\\r?\\n"));
	}
	else if (iSel == 16)
	{
		comboBox.SetWindowTextW(_T("(?=\r?$)"));
	}
	else if (iSel == 17)
	{
		comboBox.SetWindowTextW(_T("(dog|cat)"));
	}
	else if (iSel == 18)
	{
		comboBox.SetWindowTextW(_T("\\1"));
	}
	else if (iSel == 19)
	{
		comboBox.SetWindowTextW(_T("(?<pet>dog|cat)"));
	}
	else if (iSel == 20)
	{
		comboBox.SetWindowTextW(_T("\\k<pet>"));
	}
	else if (iSel == 21)
	{
		comboBox.SetWindowTextW(_T("[\\t]"));
	}
	else if (iSel == 22)
	{
		comboBox.SetWindowTextW(_T("\\d"));
	}
	else if (iSel == 23)
	{
		comboBox.SetWindowTextW(_T("\\b(_\\w+|[\\w-[0-9_]]\\w*)\\b"));
	}
	else if (iSel == 24)
	{
		comboBox.SetWindowTextW(_T("((\\\".+?\\\")|('.+?'))"));
	}
	else if (iSel == 25)
	{
		comboBox.SetWindowTextW(_T("\\b(_\\w+|[\\w-[0-9_]]\\w*)\\b"));
	}
	else if (iSel == 26)
	{
		comboBox.SetWindowTextW(_T("\\b[0-9]*\\.*[0-9]+\\b"));
	}
}
