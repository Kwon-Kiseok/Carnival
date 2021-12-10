//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : Define.h
//.
//. Windows Application for the 2006 Creator Library.
//.
//. �ۼ��� : 2006. 05. 28.
//.
//. �ۼ��� : 04�й� �� �� ö
//.-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#include <windows.h>		//. header file for windows.
							//. �⺻���� ������ Ÿ��, �Լ�����, ��ũ�� ��� ���� �����ϸ�,
							//. �� �� �������� ���α׷��ֿ� �ʿ��� �⺻���� ��� ������ ����.

#pragma comment(lib, "winmm.lib")		//. Multimedia API's Library

#ifdef _DEBUG
//�޸� �� Ȯ�ο�.. 
#include <crtdbg.h>

#include <stdio.h>
#endif


enum WIN_SIZE
{
	WIN_SIZE_640x480 = 0x01,
	WIN_SIZE_800x600 = 0x02,
	WIN_SIZE_1280x800 = 0x04,
	WIN_SIZE_DEFAULT = WIN_SIZE_1280x800
};

extern HWND			g_hWnd;			//. ������ �ڵ�.
extern HINSTANCE	g_hInstance;	//. ������ �ν��Ͻ�
extern bool			g_bLoop;		//. �޼��� ���� �ϱ� ���� ����

//. ������ ��� �� ����.
bool InitWindow(HINSTANCE hInstance,
				LPSTR szAppName,
				WORD wMenu,
				WORD wIcon,
				WORD wCursor,
				DWORD dwSize = WIN_SIZE_DEFAULT,
				DWORD	dwStyle = WS_OVERLAPPEDWINDOW);

//. �޼��� ����.
bool MsgLoop();

//. �޼��� ó�� �Լ�(������ ���ν���).
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

extern RECT g_windowRect;

#endif