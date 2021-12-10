//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : Define.h
//.
//. Windows Application for the 2006 Creator Library.
//.
//. 작성일 : 2006. 05. 28.
//.
//. 작성자 : 04학번 김 형 철
//.-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#include <windows.h>		//. header file for windows.
							//. 기본적인 데이터 타입, 함수원형, 매크로 상수 등을 정의하며,
							//. 그 외 윈도우즈 프로그래밍에 필요한 기본적인 헤더 파일을 포함.

#pragma comment(lib, "winmm.lib")		//. Multimedia API's Library

#ifdef _DEBUG
//메모리 릭 확인용.. 
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

extern HWND			g_hWnd;			//. 윈도우 핸들.
extern HINSTANCE	g_hInstance;	//. 윈도우 인스턴스
extern bool			g_bLoop;		//. 메세지 루프 하기 위한 변수

//. 윈도우 등록 및 생성.
bool InitWindow(HINSTANCE hInstance,
				LPSTR szAppName,
				WORD wMenu,
				WORD wIcon,
				WORD wCursor,
				DWORD dwSize = WIN_SIZE_DEFAULT,
				DWORD	dwStyle = WS_OVERLAPPEDWINDOW);

//. 메세지 루프.
bool MsgLoop();

//. 메세지 처리 함수(윈도우 프로시져).
LRESULT CALLBACK WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);

extern RECT g_windowRect;

#endif