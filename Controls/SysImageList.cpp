// SysImageList.cpp: implementation of the CWSysImageList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HMODULE CWSysImageList::hShell32 = NULL;
HIMAGELIST CWSysImageList::hLarge = NULL;
HIMAGELIST CWSysImageList::hSmall = NULL;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWSysImageList::CWSysImageList()
{
}

CWSysImageList::~CWSysImageList()
{
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
HIMAGELIST CWSysImageList::Large()
{
	if (CWSysImageList::hLarge == NULL)
	{
		CWSysImageList::GetSystemImageList(&CWSysImageList::hLarge, &CWSysImageList::hSmall);
	}

	return CWSysImageList::hLarge;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
HIMAGELIST CWSysImageList::Small()
{
	if (CWSysImageList::hLarge == NULL)
	{
		CWSysImageList::GetSystemImageList(&CWSysImageList::hLarge, &CWSysImageList::hSmall);
	}

	return CWSysImageList::hSmall;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : Use undocumented SHELL APIs to get system imagelists
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
BOOL CWSysImageList::GetSystemImageList(HIMAGELIST *phLarge, HIMAGELIST *phSmall)
{
	SHGIL_PROC	Shell_GetImageLists;
	FII_PROC	FileIconInit;

	if(phLarge == 0 || phSmall == 0)
		return FALSE;

	// Don't free until we terminate - otherwise, the image-lists will be destroyed
	if(CWSysImageList::hShell32 == 0)
		CWSysImageList::hShell32 = LoadLibrary("shell32.dll");

	if(CWSysImageList::hShell32 == 0)
		return FALSE;

	// Get Undocumented APIs from Shell32.dll: 
	// Shell_GetImageLists and FileIconInit
	//
	Shell_GetImageLists  = (SHGIL_PROC)  GetProcAddress(CWSysImageList::hShell32, (LPCSTR)71);
	FileIconInit		 = (FII_PROC)    GetProcAddress(CWSysImageList::hShell32, (LPCSTR)660);

	// FreeIconList@8 = ord 227

	if(Shell_GetImageLists == 0)
	{
		FreeLibrary(hShell32);
		return FALSE;
	}

	// Initialize imagelist for this process - function not present on win95/98
	if(FileIconInit != 0)
		FileIconInit(TRUE);

	// Get handles to the large+small system image lists!
	Shell_GetImageLists(phLarge, phSmall);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
void CWSysImageList::FreeSystemImageList()
{
	FreeLibrary(hShell32);
	CWSysImageList::hShell32 = 0;
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWSysImageList::GetFolderIconIndex()
{
	return GetIconIndex("c:\\windows");
}

////////////////////////////////////////////////////////////////////////////////
/// Purpose : 
/// Input   : 
/// Output  : 
////////////////////////////////////////////////////////////////////////////////
int CWSysImageList::GetIconIndex(const char* file)
{
	int res = 0;

	SHFILEINFO shfi;
	SHGetFileInfo(file, 0, &shfi, sizeof(SHFILEINFO), SHGFI_SYSICONINDEX | SHGFI_DISPLAYNAME | SHGFI_TYPENAME );

	res = shfi.iIcon;

	return shfi.iIcon;
}
