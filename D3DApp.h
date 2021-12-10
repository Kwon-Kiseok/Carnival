//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : D3DApp.h
//.
//. Windows Application for the 2006 Creator Library.
//.
//. �ۼ��� : 2006. 05. 28.
//.
//. �ۼ��� : 04�й� �� �� ö
//.-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _D3DAPP_H_
#define _D3DAPP_H_

#include "Define.h"

#include <d3d9.h>					//. Header File For Direct3D.
#include <d3dx9.h>					//. Header File for Direct3DX.

#pragma comment(lib, "d3d9.lib")	//. Direct3D9 �����Լ� Library.
#pragma comment(lib, "d3dx9.lib")	//. D3DX�� �����ϴ� �Լ� Library.

enum D3DDeviceSetting
{
	DS_WINDOW			=0x001,
	DS_16BIT			=0x004,
	DS_24BIT			=0x008,
	DS_32BIT			=0x010,

	DS_640x480			=0x080,
	DS_800x600			=0x100,
	DS_1280x800 		=0x200,
	DS_DEFAULT			=DS_16BIT | DS_WINDOW | DS_1280x800 //. �⺻����.
};

//. Direct3D �ʱ�ȭ �Լ�.
bool InitD3D(HWND hWnd, DWORD dwSetting = DS_DEFAULT);
//. �޸� ���� �Լ�.
bool ReleaseD3D();
//. ��� ���� �Լ�
void SetupMatrices(int Width, int Height);

extern LPDIRECT3D9			g_pD3D;			//. D3D ����̽��� ������ D3D��ü ����.
extern LPDIRECT3DDEVICE9	g_pD3DDevice;	//. �������� ���� D3D ����̽�.

#endif