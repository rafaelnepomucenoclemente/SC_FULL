#include "stdafx.h"
#include <commctrl.h>
#include "resource.h"
#include "Global.h"
#include "TabControlModule.h"
#include "DialogProc.h"

void WINAPI OnTabbedDialogInit_Data(HWND hwndDlg) 
{ 
	DLGHDR *pHdr = (DLGHDR *) LocalAlloc(LPTR, sizeof(DLGHDR)); 

	DWORD dwDlgBase = GetDialogBaseUnits(); 
	int cxMargin = LOWORD(dwDlgBase) / 4; 
	int cyMargin = HIWORD(dwDlgBase) / 8; 
	TCITEM tie; 
	RECT rcTab; 
	HWND hwndTab; 
	POINT poTab;
//	int i; 

	// Save a pointer to the DLGHDR structure. 
	SetWindowLong(hwndDlg, DWL_USER, (LONG) pHdr); 

	
	pHdr->hwndTab = hwndTab = GetDlgItem(hwndDlg, IDC_TAB_DATA);

	// Add tabs for each day of the week. 
	tie.mask = TCIF_TEXT | TCIF_IMAGE; 
	tie.iImage = -1; 
	tie.pszText = "�ʱ� �ɷ�ġ"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 0, &tie);
	tie.pszText = "�ɷ�ġ ��ȯ ����(����)"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 1, &tie);
	tie.pszText = "�ɷ�ġ ��ȯ ����(����)"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 2, &tie);
	tie.pszText = "���� ���)"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 3, &tie);
	// Add a tab for each of the three child dialog boxes. 
	
	// Lock the resources for the three child dialog boxes. 
	pHdr->apRes[0] = DoLockDlgRes(MAKEINTRESOURCE(IDD_PAGE1)); 
	pHdr->apRes[1] = DoLockDlgRes(MAKEINTRESOURCE(IDD_PAGE2)); 
	pHdr->apRes[2] = DoLockDlgRes(MAKEINTRESOURCE(IDD_PAGE3)); 
	pHdr->apRes[3] = DoLockDlgRes(MAKEINTRESOURCE(IDD_PAGE4)); 

	//	���ν��� �Լ��̸� ����
	pHdr->Proc[0] = (DLGPROC)Page1Proc;
	pHdr->Proc[1] = (DLGPROC)Page2Proc;
	pHdr->Proc[2] = (DLGPROC)Page3Proc;
	pHdr->Proc[3] = (DLGPROC)Page4Proc;

	//	�� ��Ʈ���� ��ȭ���ڸ� ���������� �»�� ��ġ�� ����Ѵ�.
	GetClientRect(pHdr->hwndTab, &rcTab);
	GetWindowRect(pHdr->hwndTab, &rcTab);
	poTab.x = rcTab.right;
	poTab.y = rcTab.bottom;
	ScreenToClient(GetParent(pHdr->hwndTab), &poTab);
	poTab.x = rcTab.left;
	poTab.y = rcTab.top;
	ScreenToClient(GetParent(pHdr->hwndTab), &poTab);

	// Determine the bounding rectangle for all child dialog boxes. 
	//	�� ��Ʈ�ѿ� �Ҽ��� �ڽ� ��ȭ������ ũ�⸦ �����ͼ� �� ��Ʈ���� ũ�⸦ ����Ѵ�.
//	SetRectEmpty(&rcTab); 
//	for (i = 0; i < C_PAGES; i++) { 
//		if (pHdr->apRes[i]->cx > rcTab.right) 
//			rcTab.right = pHdr->apRes[i]->cx; 
//		if (pHdr->apRes[i]->cy > rcTab.bottom) 
//			rcTab.bottom = pHdr->apRes[i]->cy; 
//	} 
//	rcTab.right = rcTab.right * LOWORD(dwDlgBase) / 4; 
//	rcTab.bottom = rcTab.bottom * HIWORD(dwDlgBase) / 8; 
	
	//	�ڽ� ��ȭ���ڰ� ������ ��ġ�� ����Ѵ�.
    // Calculate how large to make the tab control, so 
    // the display area can accommodate all the child dialog boxes. 
    TabCtrl_AdjustRect(pHdr->hwndTab, TRUE, &rcTab); 
    OffsetRect(&rcTab, cxMargin - rcTab.left + poTab.x, 
            cyMargin - rcTab.top + poTab.y); 
 
    // Calculate the display rectangle. 
    CopyRect(&pHdr->rcDisplay, &rcTab); 
    TabCtrl_AdjustRect(pHdr->hwndTab, FALSE, &pHdr->rcDisplay); 

	//	�� ��Ʈ���� ��ġ�� ���� ������ �̵��Ѵ�.
    // Set the size and position of the tab control, buttons, 
    // and dialog box. 
//	SetWindowPos(pHdr->hwndTab, NULL, rcTab.left, rcTab.top, 
//		rcTab.right - rcTab.left, rcTab.bottom - rcTab.top, 
//		SWP_NOZORDER); 

	// Simulate selection of the first item. 
	OnSelChanged(hwndDlg); 

} 

// DoLockDlgRes - loads and locks a dialog box template resource. 
// Returns the address of the locked resource. 
// lpszResName - name of the resource 

DLGTEMPLATE * WINAPI DoLockDlgRes(LPCSTR lpszResName) 
{ 
	HRSRC hrsrc = FindResource(NULL, lpszResName, RT_DIALOG); 
	HGLOBAL hglb = LoadResource(hInstMain, hrsrc); 
	return (DLGTEMPLATE *) LockResource(hglb); 
} 


//The following function processes the TCN_SELCHANGE notification message for the main dialog box. The function destroys the dialog box for the outgoing page, if any. Then it uses the CreateDialogIndirect function to create a modeless dialog box for the incoming page. 

// OnSelChanged - processes the TCN_SELCHANGE notification. 
// hwndDlg - handle to the parent dialog box. 

void WINAPI OnSelChanged(HWND hwndDlg, int iSetPage) 
{ 
	DLGHDR *pHdr = (DLGHDR *) GetWindowLong( 
		hwndDlg, DWL_USER); 
	int iSel = TabCtrl_GetCurSel(pHdr->hwndTab); 
	if(iSetPage != -1) 
	{
		iSel = iSetPage;
		TabCtrl_SetCurSel(pHdr->hwndTab, iSetPage);
	}
	
	// Destroy the current child dialog box, if any. 
	if (pHdr->hwndDisplay != NULL) 
		DestroyWindow(pHdr->hwndDisplay); 
	
	// Create the new child dialog box. 
	pHdr->hwndDisplay = CreateDialogIndirect(hInstMain, pHdr->apRes[iSel], hwndDlg, pHdr->Proc[iSel]); 

	OnChildDialogInit(pHdr->hwndDisplay);
} 

HWND WINAPI GetTabFocus(HWND hwndDlg) 
{ 
	DLGHDR *pHdr = (DLGHDR *) GetWindowLong( 
		hwndDlg, DWL_USER); 

	return pHdr->hwndDisplay;
} 

// OnChildDialogInit - Positions the child dialog box to fall 
// within the display area of the tab control. 

void WINAPI OnChildDialogInit(HWND hwndDlg) 
{ 
	RECT rcRECT;
	HWND hwndParent = GetParent(hwndDlg); 
	DLGHDR *pHdr = (DLGHDR *) GetWindowLong( 
		hwndParent, DWL_USER); 
	GetWindowRect(pHdr->hwndTab, &rcRECT);
	SetWindowPos(hwndDlg, HWND_TOP, 
		pHdr->rcDisplay.left, pHdr->rcDisplay.top, 
		0, 0, SWP_NOSIZE); 
	SetFocus(pHdr->hwndTab);
	ShowWindow(pHdr->hwndDisplay, SW_SHOW);
} 

void WINAPI OnTabbedDialogInit_Report(HWND hwndDlg) 
{ 
	DLGHDR_REPORT *pHdr = (DLGHDR_REPORT *) LocalAlloc(LPTR, sizeof(DLGHDR_REPORT)); 

	DWORD dwDlgBase = GetDialogBaseUnits(); 
	int cxMargin = LOWORD(dwDlgBase) / 4; 
	int cyMargin = HIWORD(dwDlgBase) / 8; 
	TCITEM tie; 
	RECT rcTab; 
	HWND hwndTab; 
	POINT poTab;
//	int i; 

	// Save a pointer to the DLGHDR_REPORT structure. 
	SetWindowLong(hwndDlg, GWL_USERDATA, (LONG) pHdr); 

	
	pHdr->hwndTab = hwndTab = GetDlgItem(hwndDlg, IDC_TAB_REPORT);

	// Add tabs for each day of the week. 
	tie.mask = TCIF_TEXT | TCIF_IMAGE; 
	tie.iImage = -1; 
	tie.pszText = "���� ����"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 0, &tie);
	tie.pszText = "���� ����"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 1, &tie);
	tie.pszText = "������, ��� �ð�"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 2, &tie);
	tie.pszText = "��ü ������"; 
	TabCtrl_InsertItem(pHdr->hwndTab, 3, &tie);
	// Add a tab for each of the three child dialog boxes. 
	
	// Lock the resources for the three child dialog boxes. 
	pHdr->apRes[0] = DoLockDlgRes(MAKEINTRESOURCE(IDD_REPORT_PAGE1)); 
	pHdr->apRes[1] = DoLockDlgRes(MAKEINTRESOURCE(IDD_REPORT_PAGE2)); 
	pHdr->apRes[2] = DoLockDlgRes(MAKEINTRESOURCE(IDD_REPORT_PAGE3)); 
	pHdr->apRes[3] = DoLockDlgRes(MAKEINTRESOURCE(IDD_REPORT_PAGE4)); 

	//	���ν��� �Լ��̸� ����
	pHdr->Proc[0] = (DLGPROC)ReportPage1Proc;
	pHdr->Proc[1] = (DLGPROC)ReportPage2Proc;
	pHdr->Proc[2] = (DLGPROC)ReportPage3Proc;
	pHdr->Proc[3] = (DLGPROC)ReportPage4Proc;

	//	�� ��Ʈ���� ��ȭ���ڸ� ���������� �»�� ��ġ�� ����Ѵ�.
	GetClientRect(pHdr->hwndTab, &rcTab);
	GetWindowRect(pHdr->hwndTab, &rcTab);
	poTab.x = rcTab.right;
	poTab.y = rcTab.bottom;
	ScreenToClient(GetParent(pHdr->hwndTab), &poTab);
	poTab.x = rcTab.left;
	poTab.y = rcTab.top;
	ScreenToClient(GetParent(pHdr->hwndTab), &poTab);

    TabCtrl_AdjustRect(pHdr->hwndTab, TRUE, &rcTab); 
    OffsetRect(&rcTab, cxMargin - rcTab.left + poTab.x, 
            cyMargin - rcTab.top + poTab.y); 
 
    // Calculate the display rectangle. 
    CopyRect(&pHdr->rcDisplay, &rcTab); 
    TabCtrl_AdjustRect(pHdr->hwndTab, FALSE, &pHdr->rcDisplay); 

	// Simulate selection of the first item. 
	OnSelChanged_Report(hwndDlg); 

} 

void WINAPI OnSelChanged_Report(HWND hwndDlg, int iSetPage) 
{ 
	DLGHDR_REPORT *pHdr = (DLGHDR_REPORT *) GetWindowLong( 
		hwndDlg, GWL_USERDATA); 
	int iSel = TabCtrl_GetCurSel(pHdr->hwndTab); 
	if(iSetPage != -1) 
	{
		iSel = iSetPage;
		TabCtrl_SetCurSel(pHdr->hwndTab, iSetPage);
	}
	
	// Destroy the current child dialog box, if any. 
	if (pHdr->hwndDisplay != NULL) 
		DestroyWindow(pHdr->hwndDisplay); 
	
	// Create the new child dialog box. 
	pHdr->hwndDisplay = CreateDialogIndirect(hInstMain, pHdr->apRes[iSel], hwndDlg, pHdr->Proc[iSel]); 

	OnChildDialogInit_Report(pHdr->hwndDisplay);
} 

HWND WINAPI GetTabFocus_Report(HWND hwndDlg) 
{ 
	DLGHDR_REPORT *pHdr = (DLGHDR_REPORT *) GetWindowLong( 
		hwndDlg, GWL_USERDATA); 

	return pHdr->hwndDisplay;
} 

// OnChildDialogInit - Positions the child dialog box to fall 
// within the display area of the tab control. 

void WINAPI OnChildDialogInit_Report(HWND hwndDlg) 
{ 
	RECT rcRECT;
	HWND hwndParent = GetParent(hwndDlg); 
	DLGHDR_REPORT *pHdr = (DLGHDR_REPORT *) GetWindowLong( 
		hwndParent, GWL_USERDATA); 
	GetWindowRect(pHdr->hwndTab, &rcRECT);
	SetWindowPos(hwndDlg, HWND_TOP, 
		pHdr->rcDisplay.left, pHdr->rcDisplay.top, 
		0, 0, SWP_NOSIZE); 
	SetFocus(pHdr->hwndTab);
	ShowWindow(pHdr->hwndDisplay, SW_SHOW);
} 
