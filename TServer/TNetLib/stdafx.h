// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#ifndef _WIN32_WINNT		// Windows NT 4 �̻󿡼��� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINNT 0x0500	// �� ���� Windows 2000 �̻��� ������� �ϴ� �� ������ ������ �����Ͻʽÿ�.
#endif						

#define WIN32_LEAN_AND_MEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// �Ϻ� CString �����ڴ� ��������� ����˴ϴ�.

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
#endif

#include <TNetLib.h>
