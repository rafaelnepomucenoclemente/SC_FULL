#include "stdafx.h"
#include "Global.h"

HWND hWndMain, hWndEdit, hWndPage1, hWndPage2, hWndPage3, hWndPage4=NULL;
HWND hWndReportPage1, hWndReportPage2, hWndReportPage3, hWndReportPage4;
HINSTANCE hInstMain;


//	�޴����� ���Ǵ� �ӽ� ����
EditResultData gsLevelStat
	={1,0,0,0,
	1,0,0,
	1,5,0,
	1,0,2,6,
	1,5,11,6,
	0,2,6,6,
	FALSE};

//	���� ���� ���
char ReportPath[_MAX_FNAME];
