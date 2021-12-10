//! 파티클 스크립트 헤더파일 포함
//#include "BadParticleCode/BadParticleCode.h"
#include "D3DApp.h"

extern LPDIRECT3D9			g_pD3D				= NULL;
extern LPDIRECT3DDEVICE9	g_pD3DDevice		= NULL;
D3DDISPLAYMODE				g_d3ddm;

extern RECT g_windowRect;
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Direct3D 초기화.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool InitD3D(HWND hWnd, DWORD dwSetting)
{
	//. 디바이스를 생성할 구조체.
	D3DPRESENT_PARAMETERS d3dpp;

	//. 디바이스를 생성하기 위한 D3D객체 생성.
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	//. Direct3D 파라미터 설정.
	memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	//. Back-Buffer 교체효과 설정.
	d3dpp.hDeviceWindow				= hWnd;
	d3dpp.BackBufferCount			= 1;						
	d3dpp.EnableAutoDepthStencil	= TRUE;						//. Depth-Buffer 사용 유무.
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				//. Depth_Buffer
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	int Width	= 0;
	int Height	= 0;
	//. 설정된 D3D 디바이스 셋팅과 같다면
	if(dwSetting & DS_640x480)
	{
		Width = 640;
		Height = 480;
	}
	else if(dwSetting & DS_800x600)
	{
		Width = 800;
		Height = 600;
	}
	else if(dwSetting & DS_1280x800)
	{
		Width = 1280;
		Height = 800;
	}
	//. 윈도우 모드.
	if(dwSetting & DS_WINDOW)
	{
		d3dpp.Windowed			= TRUE;
		d3dpp.BackBufferFormat	= g_d3ddm.Format;
	}
	//. 풀스크린 모드
	else
	{
		d3dpp.Windowed			= FALSE;
		d3dpp.BackBufferWidth	= Width;
		d3dpp.BackBufferHeight	= Height;

		if(dwSetting & DS_16BIT)
		{
			d3dpp.BackBufferFormat = D3DFMT_A1R5G5B5;		//. 16BIT
		}
		else if(dwSetting & DS_24BIT)
		{
			d3dpp.BackBufferFormat = D3DFMT_R8G8B8;			//. 24BIT
		}

		else
		{
			d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;		//. 32BIT
		}
	}
		/*!
		하드웨어 가속을 이용한 라스터화(D3DDeVTYPE_HAL),
		소프트웨어 정점변환(D3DCREATE_SOFTWARE_VAERTEXPROCESSING)를 사용하고
		파라미터(d3dpp)를 참조하여 Direct3D를 생성한다.
		*/

		HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,	D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice);

		//. 실패시 에러 메시지 박스 출력.
		if(FAILED(hr))
		{
			MessageBox(hWnd, "D3D 장치 생성 실패:", "에러", MB_ICONERROR);
			return false;
		}

		int windowsWidth = abs(g_windowRect.left) + abs(g_windowRect.right) - Width;
		int windowsHeight = abs(g_windowRect.top) + abs(g_windowRect.bottom) - Height;

		//. 뷰포트를 생성한다.
		D3DVIEWPORT9 ViewPort = {0, 0, Width, Height, 0.0f, 1.0f};
		g_pD3DDevice->SetViewport(&ViewPort);

		//.행렬 설정.
		SetupMatrices(Width, Height);

		/*! 2D 그래픽을 나타내므로 다음 설정을 하지 않는다. */
		// 컬링 기능을 사용하지 않는다.
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		//. 라이팅 기능을 사용하지 않는다.
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//. 2D 스프라이트를 출력할 것이므로 Z버퍼는 필요하지 않다.
		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		//. 텍스처 설정.
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		//.알파 블렌딩(실시간 렌더링 실전 테크닉 292P)
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//! 파티클 스크립트 초기화
		//g_pBadParticleCode->SetDevice(g_pD3DDevice);

		return TRUE;
}
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 메모리 해제
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool ReleaseD3D()
{
	if(g_pD3D)
	{
		SAFE_RELEASE(g_pD3D);
	}
	if(g_pD3DDevice)
	{
		SAFE_RELEASE(g_pD3DDevice);
	}

	return TRUE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 행렬 설정.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void SetupMatrices(int Width, int Height)
{
	//.프로텍션 행렬 설정.

	D3DXVECTOR3 vEyePt(0, 0.0f, -1.0f);
	D3DXVECTOR3 vLookatPt(0, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matOrtho;
	//. 정점을 상하로 뒤집은 후에 왼쪽 윗부분을 원점으로 투영한다. ( 모니터 좌상점이 0,0으로 설정)
	D3DXMatrixOrthoOffCenterLH(&matOrtho, 0.0f, (float)(Width), (float)(Height), 0.0f, 0.0f, 1.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);
}