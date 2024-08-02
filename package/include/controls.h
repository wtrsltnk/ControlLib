#ifndef CONTROLS_H
#define CONTROLS_H

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shlwapi.h>
#include <shlobj.h>
#include <commctrl.h>
#include <commdlg.h>
#include <vector>
#include <gl/gl.h>
#include <gl/glu.h>
using namespace std;


#ifdef CONTROLS_EXPORTS
#define CTRLDLL_API __declspec(dllexport)
#else
#define CTRLDLL_API __declspec(dllimport)
#endif

#pragma warning( disable : 4251 )

class CWMenu;
class CWSystrayIcon;

// Define's
#define IDM_WINDOW_NEXT					23001
#define IDM_WINDOW_PREVIOUS				23002
#define IDM_WINDOW_TILEHORIZONTAAL		23003
#define IDM_WINDOW_TILEVERTICAAL		23004
#define IDM_WINDOW_CASCADE				23005
#define IDM_WINDOW_CLOSE				23006
#define IDM_WINDOW_CLOSEALL				23007
#define IDM_TITLEBUTTON					23008

#define ID_SYSTRAY						4

#define WM_SHELLNOTIFY					WM_USER + 23000
#define WM_SCROLLDLGS					WM_USER + 23001
#define WM_MDICHILDACTIVATE				WM_USER + 23002
#define WM_MDICHILDCLOSE				WM_USER + 23003





//////////////////////////////////////////////////////////////////////////////////////////
// BaseControl class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWBaseApp
{
protected:
	static CWBaseApp* m_pInstance;

	static LRESULT CALLBACK StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	static char* AppPath();
	static char* ExeName();
	static int Args(char* argv[]);
	static void GoFullscreen(int width, int height, int bits);
	static void LeavFullscreen();
	static SIZE* GetScreensize();

protected:
	CWBaseApp* m_pPrevInstance;
	HINSTANCE m_hInstance;
	HWND m_hWnd;

	DWORD m_PosX;
	DWORD m_PosY;
	DWORD m_dwWindowStyle;
	DWORD m_dwExWindowStyle;
	DWORD m_dwCreationHeight;
	DWORD m_dwCreationWidth;
	DWORD m_dwCreationFlags;
	LPCTSTR m_strWindowTitle;
	LPCTSTR m_strWindowClass;
	HBRUSH m_hbrWindowColor;
	HICON  m_hIcon;
	HCURSOR m_hCursor;
	HACCEL m_hAccelTable;

	CWMenu* m_pMenu;
	CWMenu* m_pSysMenu;

	CWSystrayIcon* m_pSystrayIcon;

	char m_strAppPath[MAX_PATH];
	char m_strExeName[128];

	LRESULT InitWindowClass();
	virtual LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
    CWBaseApp(HINSTANCE hInstance);
	~CWBaseApp();

    LRESULT Init();
	LRESULT Run();
};





//////////////////////////////////////////////////////////////////////////////////////////
// MDIChild class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWMDIChild
{
protected:
	friend class CWBaseMDIApp;

	static HWND m_hActiveWnd;
	static LRESULT StaticProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

protected:
	HINSTANCE m_hInstance;
	HWND m_hClient;
	HWND m_hWnd;

	LPCTSTR m_strTitle;
	DWORD m_dwStyle;
	DWORD m_PosX;
	DWORD m_PosY;
	DWORD m_dwCreationHeight;
	DWORD m_dwCreationWidth;
 	DWORD m_dwCreationFlags;

	void SetHandle(HWND hWnd);
	virtual void ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual LRESULT OnClose(WPARAM wParam, LPARAM lParam){ return 0; }
	virtual LRESULT OnActivate(WPARAM wParam, LPARAM lParam){ return 0; }
	virtual LRESULT OnSize(WPARAM wParam, LPARAM lParam){ return 0; }
public:
	CWMDIChild();
	virtual ~CWMDIChild();
	
    LRESULT Create(HWND hClient, LPCTSTR strWindowClass);
	void Activate();

};




//////////////////////////////////////////////////////////////////////////////////////////
// BaseMDIApp class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWBaseMDIApp
{
protected:
	static CWBaseMDIApp* m_pInstance;

	static LRESULT StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	CWBaseMDIApp* m_pPrevInstance;
	HINSTANCE m_hInstance;
	HWND    m_hWnd;
	HWND    m_hClient;
	
	DWORD   m_dwWindowStyle;
	DWORD   m_dwExWindowStyle;
	DWORD   m_PosX;
	DWORD   m_PosY;
	DWORD   m_dwCreationHeight;
	DWORD   m_dwCreationWidth;
	DWORD   m_dwCreationFlags;
	LPCTSTR m_strWindowTitle;
	HACCEL  m_hAccelTable;
	
	DWORD   m_dwClientWindowStyle;
	DWORD   m_dwClientExWindowStyle;
	DWORD   m_ClientPosX;
	DWORD   m_ClientPosY;
	DWORD   m_dwClientCreationHeight;
	DWORD   m_dwClientCreationWidth;

	HICON   m_hIcon;
	HICON   m_hSmallIcon;
	HICON   m_hCursor;
	HBRUSH  m_hbrWindowColor;
	LPCTSTR m_strWindowClass;

	HICON   m_hChildIcon;
	HICON   m_hChildSmallIcon;
	HICON   m_hChildCursor;
	HBRUSH  m_hbrChildWindowColor;
	LPCTSTR m_strChildWindowClass;

	CWMenu* m_pMenu;
	CWMenu* m_pSysMenu;
	CWMenu* m_pWindowMenu;

	CWSystrayIcon* m_pSystrayIcon;

	LRESULT InitWindowClasses();
	LRESULT InitClientArea();
	virtual LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnChildActivate(WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnChildClose(WPARAM wParam, LPARAM lParam);

public:
	CWBaseMDIApp();
	virtual ~CWBaseMDIApp();

	LRESULT Init(HINSTANCE hInstance);
	LRESULT Run();

};





//////////////////////////////////////////////////////////////////////////////////////////
// BaseControl class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWControl
{
protected:
	CWControl();
    virtual ~CWControl();

	HWND		m_hWnd, m_hParent;
	HINSTANCE	m_hInstance;
	int			m_nX, m_nY, m_nWidth, m_nHeight;
	int			m_nID;
	BOOL		m_bVisible;

	DWORD		m_dwStyle, m_dwExStyle;
	LPCTSTR		m_strClassName;
	char		m_strTitle[256];
	HFONT		m_hFont;
	LPVOID		m_lpTag;

	void		SetHWND(HWND hWnd) { m_hWnd = hWnd; }
	void		SetParent(HWND hWnd);
	virtual LRESULT InitWindowClass() { return FALSE; }
public:
	virtual void Create(HWND hWnd);
	virtual void Create(HWND parent, int id);
	virtual void Create(CWControl* parent, int id);
	void ReCreate(HWND newParent);
	virtual void Resize(int x, int y, int width, int height);
	void Refresh();
	void Kill();
	void Focus();

	HWND GetHandle();

	HFONT GetFont();
	void SetFont(HFONT font);

	const char* GetTitle();
	void SetTitle(const char* title);

	DWORD GetStyle();
	void SetStyle(DWORD style);

	DWORD GetExStyle();
	void SetExStyle(DWORD exstyle);

	LPVOID GetTag();
	void SetTag(LPVOID tag);

	bool IsEnabled();
	void SetEnable(bool enabled);

	bool IsVisible();
	void SetVisible(bool visible);

	void SetRect(RECT* rc);
	void GetRect(RECT* rc);

	void SetID(int id);
	int GetID();
};





//////////////////////////////////////////////////////////////////////////////////////////
// BaseDialog class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWDialog
{
protected:
	static LRESULT StaticProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	HWND m_hDlg;
	HWND m_hParent;
	HINSTANCE m_hInstance;
	DWORD m_dwResourceDlg;

	virtual void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void SetHandle(HWND hWnd);
public:
	CWDialog();
	virtual ~CWDialog();

	enum ItemTypes
	{
		ItemTypeEdit = 1,
		ItemTypeStatic,
		ItemTypeButton,
		ItemTypeCombobox,
		ItemTypeList,
		ItemTypeListView,
		ItemTypeTreeView
	};

	int ShowModal(HINSTANCE hInst, HWND hParent);
	int ShowModalless(HINSTANCE hInst, HWND hParent);

	void Resize(int x, int y, int width, int height);

	void SetItemText(int nIDDlgItem, LPTSTR lpString);
	void GetItemText(int nIDDlgItem, LPTSTR lpString, int nMaxCount);

	void SetItemInt(int nIDDlgItem, int nValue);
	int GetItemInt(int nIDDlgItem);

	void SetItemCheck(int nIDDlgItem, bool bChecked);
	bool IsChecked(int nIDDlgItem);

	int GetItemType(int nIDDlgItem);

	HWND GetItem(int nIDDlgItem);
};





//////////////////////////////////////////////////////////////////////////////////////////
// CustomControlWindow class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWCustomControl : public CWControl
{
protected:
	HBRUSH m_hbrBackground;
    HICON m_hIcon;
    HCURSOR m_hCursor;
    HICON m_hIconSm;

protected:
	LRESULT InitWindowClass();

	static LRESULT StaticProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CWCustomControl();
	virtual ~CWCustomControl();

};





//////////////////////////////////////////////////////////////////////////////////////////
// 3DEngine class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CW3DEngine
{
protected:
	HWND m_hWnd;
	HDC m_hDC;
	HGLRC m_hRC;
	UINT m_uFont;

	int m_nWidth;
	int m_nHeight;
	float m_fAspect;

	float m_fFieldOfView;
	float m_fNearClipping;
	float m_fFarClipping;

	LRESULT InitPixelFormat();
	void Goto3D();
	void Leave3D();
public:
	CW3DEngine();
	virtual ~CW3DEngine();

	LRESULT Init(HWND hWnd);
	LRESULT Kill();
	void Resize(int width, int height);
	void Use();

	void PreRender();
	void PostRender();

	void Goto2D();
	void Leave2D();

	void Render2DFilledRect(RECT* rc, float color[4]);
	void Render2DRect(RECT* rc, float color[4]);
	void Render2DText(int x, int y, float color[4], UINT font, const char *format, ...);

	void AddFont(char* face, int height, int width, UINT* fontid);
	void AddFont(HFONT hFont, UINT* fontid);
	void AddTexture(BITMAP bmp, unsigned int* texid);
	void UseTexture(int i);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Button class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWButton : public CWControl
{
public:
	CWButton();
	virtual ~CWButton();

};





//////////////////////////////////////////////////////////////////////////////////////////
// CustomButton class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWCustomButton : public CWCustomControl
{
protected:
	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool m_bPressed;

	COLORREF m_cBGColor;
	COLORREF m_cFGColor;
	COLORREF m_cBorderColor;

public:
	CWCustomButton();
	virtual ~CWCustomButton();

	void SetBGColor(COLORREF rgb);
	void SetFGColor(COLORREF rgb);
	void SetBorderColor(COLORREF rgb);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Checkbox class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWCheck : public CWControl
{
public:
	CWCheck();
	virtual ~CWCheck();
};





//////////////////////////////////////////////////////////////////////////////////////////
// Combobox class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWCombo : public CWControl
{
public:
	CWCombo();
	virtual ~CWCombo();

	int AddItem(char item[], int index, DWORD data);
	bool RemoveItem(int index);

	char* GetText(int index);
	DWORD GetData(int index);
	int GetSelectedIndex();

	void Clear();
	void Select(int index);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Combolist class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWComboList : public CWCombo
{
public:
	CWComboList();
	virtual ~CWComboList();

};





//////////////////////////////////////////////////////////////////////////////////////////
// Editbox class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWEdit : public CWControl
{
public:
	CWEdit();
	virtual ~CWEdit();

	void Append(char* text);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Label class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWLabel : public CWControl
{
public:
	CWLabel();
	virtual ~CWLabel();

};





//////////////////////////////////////////////////////////////////////////////////////////
// Listbox class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWList : public CWControl
{
public:
	CWList();
	virtual ~CWList();

	int AddItem(char item[], int index, DWORD data);
	bool RemoveItem(int index);

	char* GetText(int index);
	DWORD GetData(int index);
	int GetSelectedIndex();

	void Clear();
	void Select(int index);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Listview class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWListView : public CWControl
{
protected:
	HWND		m_hHeader;
	DWORD		m_dwExLvStyle;

	LPLVITEM GetItem(int index);
public:
	CWListView();
	virtual ~CWListView();

	void Create(HWND parent, int id, DWORD exlvstyle);
	void SetExLvStyle(DWORD exlvstyle);

	void AddColumn(char title[], int width, int index);
	void RemoveColumn(int index);
	void ClearColumns();

	void AddItem(char text[], int index, int image = 0, LPARAM data = 0);
	void AddSubitem(char text[], int index, int subindex, LPARAM data = 0);
	void RemoveItem(int index);
	void ClearItems();

	char* GetItemText(int index);
	char* GetSubItemText(int index, int subindex);
	LPARAM GetItemData(int index);
	int GetSelectedItemIndex();

	HIMAGELIST SetNormalImageList(HIMAGELIST himl);
	HIMAGELIST SetSmallImageList(HIMAGELIST himl);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Option class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWOption : public CWControl
{
public:
	CWOption();
	virtual ~CWOption();

	int GetState();
	void SetState(int state);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Optionframe class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWOptionFrame : public CWControl
{
private:
	int m_nNumOptions;

	vector <CWOption*> m_aOptions;
public:
	CWOptionFrame();
	virtual ~CWOptionFrame();

	bool AddOption(CWOption* option, int id);
	int GetSelectedOption();
	void SetSelectedOption(int id);
};





//////////////////////////////////////////////////////////////////////////////////////////
// PropertieDialog class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWPropertieDialog : public CWDialog
{
protected:
	friend class CWBasePropertieChild;
	bool m_bDrag;

	LRESULT Init(DWORD dwResource);
	LRESULT Show(HWND hParent);
	LRESULT Close();

	void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CWPropertieDialog();
	virtual ~CWPropertieDialog();
};





//////////////////////////////////////////////////////////////////////////////////////////
// PropertieDialog class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWBasePropertieChild : public CWCustomControl
{
protected:
	friend class CWPropertieWindow;
	CWBasePropertieChild* m_pNext;
	int m_nX;
	int m_nY;
	int m_nWidth;
	int m_nHeight;
	int m_nOriginalHeight;
	DWORD m_dwResource;

	CWPropertieDialog m_Dialog;
	CWButton m_Button;

	LRESULT Show(HWND hParent);
	LRESULT Close();

	int MoveDialog(int x, int y, int width);
	int GetHeight();
	
	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam) { return FALSE; }
	virtual LRESULT OnItemChanged(WPARAM wParam, LPARAM lParam) { return FALSE; }
public:
	CWBasePropertieChild();
	virtual ~CWBasePropertieChild();

	void Init(int width, int height, DWORD resource, int id);

	HWND GetItem(int id);
	void SetTitle(const char* strTitle);
};





//////////////////////////////////////////////////////////////////////////////////////////
// PropertieWindow class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWPropertieWindow : public CWCustomControl
{
protected:
	CWBasePropertieChild* m_pDlgHead;
	int m_nScrollAmount;
	int m_nTotalHeight;
	RECT m_ClRc;
	bool m_bDrag;
	HCURSOR m_hHand;

	LRESULT ScrollChilds(int scrollamount);
	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CWPropertieWindow();
	virtual ~CWPropertieWindow();

	void Resize(int x, int y, int width, int height);

	LRESULT AddDialog(CWBasePropertieChild* dlg);
	void ClearDialogs();
};





//////////////////////////////////////////////////////////////////////////////////////////
// ToolBoxDlg class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWToolBoxDlg : public CWDialog
{
	friend class CWBasePropertieChild;

	void DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CWToolBoxDlg();
	virtual ~CWToolBoxDlg();

	LRESULT Init(DWORD dwResource);
	LRESULT Show(HWND hParent);
	LRESULT Close();
};





//////////////////////////////////////////////////////////////////////////////////////////
// ToolBox class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWToolBox : protected CWCustomControl
{
protected:
	friend class CWToolBoxContainer;
	CWToolBox* m_pNext;
	DWORD m_dwResource;
	int m_nOriginalHeight;
	
	CWToolBoxDlg m_Dialog;
	CWButton m_Button;

	LRESULT Show(HWND hParent);
	LRESULT Close();
	int Move(int x, int y, int width);
	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	CWToolBox();
	virtual ~CWToolBox();

	void Initialize(int height, int id, DWORD resource = 0);
	
	void SetTitle(const char* title);
	void SetButtonStyle(DWORD style);
	int GetID();

};





//////////////////////////////////////////////////////////////////////////////////////////
// ToolBoxContainer class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWToolBoxContainer : public CWCustomControl
{
private:
	class Layer : public CWCustomControl
	{
	public:
		Layer();
		virtual ~Layer();

		int X();
		int Y();
		int Width();
		int Height();
		void X(int x);
		void Y(int y);
		void Height(int h);
		void Width(int w);
		LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	};

private:
	CWToolBox m_Head;
	Layer m_Layer;
	bool m_bDrag;
	HCURSOR m_hHand;
	int m_nScrollAmount;
	int m_nTotalHeight;
	RECT m_ClRc;

	LRESULT Scroll(int amount);
	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void UpdateBoxes();

public:
	CWToolBoxContainer();
	virtual ~CWToolBoxContainer();

	LRESULT AddToolBox(CWToolBox* toolBox);
	LRESULT RemoveToolBox(int id);
	void ClearToolBoxes();
};





//////////////////////////////////////////////////////////////////////////////////////////
// ToolWindow class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWToolWindow : public CWCustomControl
{
protected:
	virtual LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
	CWToolWindow();
	virtual ~CWToolWindow();
	void Create(HWND parent);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Treeview class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWTreeView : public CWControl
{
public:
	CWTreeView();
	virtual ~CWTreeView();

    HTREEITEM AddItem(char* text, HTREEITEM parent, int image = 0, int selimage = 1, DWORD data = 0);
	void RemoveItem(HTREEITEM item);
	void ClearItems();
	void ClearChilds(HTREEITEM item);
	bool HasChilds(HTREEITEM item);

	const char* GetItemText(HTREEITEM item);
	DWORD GetItemData(HTREEITEM item);
	HTREEITEM GetSelectedItem();
	HTREEITEM GetParentItem(HTREEITEM item);
	HTREEITEM GetChild(HTREEITEM parent, int index);
	HTREEITEM GetFirstChild(HTREEITEM item);
	HTREEITEM GetNextSibling(HTREEITEM item);
	void Expand(HTREEITEM item);
	void Collapse(HTREEITEM item);

	HIMAGELIST SetNormalImageList(HIMAGELIST himl);

	void SetCheckState(HTREEITEM item, bool state);
	bool GetCheckState(HTREEITEM item);

	HTREEITEM HitTestCursor();
};





//////////////////////////////////////////////////////////////////////////////////////////
// Slider class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWSlider : public CWControl
{
public:
	CWSlider();
	virtual ~CWSlider();
	
	void Init(int min, int max);
	void Reset();

	void SetSel(int sel);
	int GetSel();

	bool CompareHandle(HWND hWnd);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Splitter class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWSplitter : public CWCustomControl
{
private:
	CWControl* m_pControlA;
	CWControl* m_pControlB;

	int m_nSplitPosition;
	int m_nMinPosition;
	int m_nMaxPosition;

	bool m_bHorzSplit;

	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	void ResizeControls();
	void DrawHorzXorBar(HDC hdc);
	void DrawVertXorBar(HDC hdc);
public:
	CWSplitter ();
	virtual ~CWSplitter ();

	void Create(HWND parent, int id, bool horz);
	void Resize(int x, int y, int width, int height);
	
	void SetControlA(CWControl* controlA, int minSize);
	void SetControlB(CWControl* controlB, int minSize);
};





//////////////////////////////////////////////////////////////////////////////////////////
// Splitter class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWTrackbar : public CWCustomControl
{
private:
	bool m_bHasFocus;
	bool m_bDrag;

	int m_nStart;
	int m_nEnd;
	int m_nStep;
	int m_nStepCount;

	LRESULT ViewProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void DrawRange(HDC hdc, int steps);
	void DrawStep(HDC hdc, int steps, int step);
	void GetDrawArea(RECT* area);
	void GetStepArea(RECT* area, int steps, int step);
	float GetStepSpace(int steps);

public:
	CWTrackbar();
	virtual ~CWTrackbar();
	
	void SetRange(int start, int end);
	void SetStep(int step);
	int GetStep();
	void Increase();
	void Decrease();
};





//////////////////////////////////////////////////////////////////////////////////////////
// Commondlg class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWCommondlg
{
public:
	CWCommondlg();
	virtual ~CWCommondlg();

	static char* OpenFile(HWND hOwner, char *szFilter, char *szDefExt);
	static char* SaveFile(HWND hOwner, char *szFilter, char *szDefExt);
	static char* Directory(HWND hOwner);
	static bool Color(HWND hOwner, float color[3]);
};





//////////////////////////////////////////////////////////////////////////////////////////
// PopUpMenu class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWMenu
{
public:
	static CWMenu* FromResource(UINT id);
	static CWMenu* FromSystemMenu(HWND hWnd);

protected:
	HMENU m_hMenu;
	char m_strName[64];
public:
	CWMenu();
	CWMenu(const char* name);
	virtual ~CWMenu();

	void AddItem(const char* item, UINT id);
	void AddSubMenu(CWMenu* submenu);
	void AddSeperator();

	void InsertItem(const char* item, UINT id, int pos);
	void InsertSubMenu(CWMenu* submenu, int pos);
	void InsertSeperator(int pos);

	void CheckItem(UINT id, bool check);
	bool IsChecked(UINT id);

	void CheckGroupItem(UINT first, UINT last, UINT id);
	int IsGroupChecked(UINT first, UINT last);

	void EnableItem(UINT id, bool enable);

	HMENU Handle();
};





//////////////////////////////////////////////////////////////////////////////////////////
// PopUpMenu class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
class CTRLDLL_API CWPopUpMenu : public CWMenu
{
public:
	CWPopUpMenu();
	CWPopUpMenu(char* name);
	virtual ~CWPopUpMenu();

	void ShowMenu(HWND hOwner, int x, int y);
};





//////////////////////////////////////////////////////////////////////////////////////////
// SystemImageList class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
typedef BOOL (WINAPI * SHGIL_PROC)	(HIMAGELIST *phLarge, HIMAGELIST *phSmall);
typedef BOOL (WINAPI * FII_PROC)	(BOOL fFullInit);

class CTRLDLL_API CWSysImageList  
{
private:
	static HMODULE		hShell32;
	static HIMAGELIST	hLarge;
	static HIMAGELIST	hSmall;

	static BOOL GetSystemImageList(HIMAGELIST *phLarge, HIMAGELIST *phSmall);
public:
	CWSysImageList();
	virtual ~CWSysImageList();

	static HIMAGELIST Large();
	static HIMAGELIST Small();
	static void FreeSystemImageList();

	static int GetFolderIconIndex();
	static int GetIconIndex(const char* type);
};





//////////////////////////////////////////////////////////////////////////////////////////
// SystemImageList class
// Purpose :	
//				
//				
//				
//////////////////////////////////////////////////////////////////////////////////////////
#include <shellapi.h>

class CTRLDLL_API CWSystrayIcon
{
protected:
	HWND m_hWnd;
	HICON m_hIcon;
	NOTIFYICONDATA m_NotifyData;
	LPCTSTR m_strTitle;
	int m_iID;
public:
	CWSystrayIcon();
	virtual ~CWSystrayIcon();

	LRESULT Init(HWND hWnd, int id);
	LRESULT Kill();

	virtual LRESULT OnClick(WPARAM wParam, LPARAM lParam) { return 0; };
	virtual LRESULT OnDblClick(WPARAM wParam, LPARAM lParam) { return 0; };
	virtual LRESULT OnRClick(WPARAM wParam, LPARAM lParam) { return 0; };
};

#endif
