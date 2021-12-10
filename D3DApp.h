//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : D3DApp.h
//.
//. Windows Application for the 2006 Creator Library.
//.
//. 작성일 : 2006. 05. 28.
//.
//. 작성자 : 04학번 김 형 철
//.-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _D3DAPP_H_
#define _D3DAPP_H_

#include "Define.h"

#include <d3d9.h>					//. Header File For Direct3D.
#include <d3dx9.h>					//. Header File for Direct3DX.

#pragma comment(lib, "d3d9.lib")	//. Direct3D9 관련함수 Library.
#pragma comment(lib, "d3dx9.lib")	//. D3DX로 시작하는 함수 Library.

enum D3DDeviceSetting
{
	DS_WINDOW			=0x001,
	DS_16BIT			=0x004,
	DS_24BIT			=0x008,
	DS_32BIT			=0x010,

	DS_640x480			=0x080,
	DS_800x600			=0x100,
	DS_1280x800 		=0x200,
	DS_DEFAULT			=DS_16BIT | DS_WINDOW | DS_1280x800 //. 기본설정.
};

//. Direct3D 초기화 함수.
bool InitD3D(HWND hWnd, DWORD dwSetting = DS_DEFAULT);
//. 메모리 해제 함수.
bool ReleaseD3D();
//. 행렬 설정 함수
void SetupMatrices(int Width, int Height);

extern LPDIRECT3D9			g_pD3D;			//. D3D 디바이스를 생성할 D3D객체 변수.
extern LPDIRECT3DDEVICE9	g_pD3DDevice;	//. 렌더링에 사용될 D3D 디바이스.

#endif