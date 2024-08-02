// CWDialog.cpp: implementation of the CWDialog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWDialog::CWDialog()
{
	this->m_hInstance			 = NULL;
	this->m_hParent				 = NULL;
	this->m_hDlg				 = NULL;
    this->m_dwResourceDlg		 = 0;
}

CWDialog::~CWDialog() = default;

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
LRESULT CWDialog::StaticProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CWDialog *pDlg = 0;

	// Is it the first message?
	if (uMsg == WM_INITDIALOG)
	{
		// Get the object from the creation param
		pDlg = reinterpret_cast<CWDialog *>(lParam);
		pDlg->SetHandle(hDlg);

		// Set it in the Window param
        ::SetWindowLongPtr(hDlg, GWLP_USERDATA, reinterpret_cast<long long>(pDlg));
	}
	else
	{
		// Get the object from the window param
        pDlg = reinterpret_cast<CWDialog *>(::GetWindowLongPtr(hDlg, GWLP_USERDATA));
	}

	if (pDlg)
		pDlg->DlgProc(uMsg, wParam, lParam);

	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CWDialog::ShowModal(HINSTANCE hInst, HWND hParent)
{
	this->m_hInstance = hInst;
	this->m_hParent = hParent;

	return DialogBoxParam(hInst, MAKEINTRESOURCE(m_dwResourceDlg), hParent, (DLGPROC)CWDialog::StaticProc, (LPARAM)this);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CWDialog::ShowModalless(HINSTANCE hInst, HWND hParent)
{
	this->m_hInstance = hInst;
	this->m_hParent = hParent;

	m_hDlg = CreateDialogParam(hInst, MAKEINTRESOURCE(m_dwResourceDlg), hParent, (DLGPROC)CWDialog::StaticProc, (LPARAM)this);
	ShowWindow(m_hDlg, SW_SHOW);
	
	return 1;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWDialog::Resize(int x, int y, int width, int height)
{
	::MoveWindow(this->m_hDlg, x, y, width, height, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : Set the handle of the created dialogwindow in this 
//           instance. Used in the wndproc of the clientwindowclass
// Input   : Handle of the dialogwindow created by this instance
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWDialog::SetHandle(HWND hWnd)
{
	this->m_hDlg = hWnd;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWDialog::SetItemText(int nIDDlgItem, LPTSTR lpString)
{
	::SetDlgItemText(this->m_hDlg, nIDDlgItem, lpString);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWDialog::GetItemText(int nIDDlgItem, LPTSTR lpString, int nMaxCount)
{
	::GetDlgItemText(this->m_hDlg, nIDDlgItem, lpString, nMaxCount);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWDialog::SetItemInt(int nIDDlgItem, int nValue)
{
	::SetDlgItemInt(this->m_hDlg, nIDDlgItem, nValue, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CWDialog::GetItemInt(int nIDDlgItem)
{
	return ::GetDlgItemInt(this->m_hDlg, nIDDlgItem, NULL, TRUE);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWDialog::SetItemCheck(int nIDDlgItem, bool bChecked)
{
	::SendMessage(GetDlgItem(this->m_hDlg, nIDDlgItem), BM_SETCHECK, bChecked?BST_CHECKED:BST_UNCHECKED, 0);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
bool CWDialog::IsChecked(int nIDDlgItem)
{
	return ::SendMessage(GetDlgItem(this->m_hDlg, nIDDlgItem), BM_GETCHECK, 0, 0) == BST_CHECKED;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
HWND CWDialog::GetItem(int nIDDlgItem)
{
	return ::GetDlgItem(this->m_hDlg, nIDDlgItem);
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
int CWDialog::GetItemType(int nIDDlgItem)
{
	int res = 0;

	char lpClassName[256] = {0};
	::GetClassName(GetItem(nIDDlgItem), lpClassName, 256);

	if (strcmp(lpClassName, "EDIT") == 0)
	{
		return ItemTypeEdit;
	}
	else if (strcmp(lpClassName, "STATIC") == 0)
	{
		return ItemTypeStatic;
	}
	else if (strcmp(lpClassName, "BUTTON") == 0)
	{
		return ItemTypeButton;
	}
	else if (strcmp(lpClassName, "COMBOBOX") == 0)
	{
		return ItemTypeCombobox;
	}
	else if (strcmp(lpClassName, "LISTBOX") == 0)
	{
		return ItemTypeList;
	}
	else if (strcmp(lpClassName, "SysListView32") == 0)
	{
		return ItemTypeListView;
	}
	else if (strcmp(lpClassName, "SysTreeView32") == 0)
	{
		return ItemTypeTreeView;
	}
	return res;
}

//////////////////////////////////////////////////////////////////////
// Purpose : 
// Input   : 
// Output  : 
//////////////////////////////////////////////////////////////////////
void CWDialog::DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		{
			switch (wParam)
			{
			case IDCANCEL:
			case IDOK:
				{
					EndDialog(m_hDlg, IDOK);
					break;
				}
			}
			break;
		}

	case WM_CLOSE:
		{
			EndDialog(m_hDlg, IDOK);
			break;
		}
	}
}
