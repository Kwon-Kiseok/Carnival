//! ��ƼŬ ��ũ��Ʈ ������� ����
//#include "BadParticleCode/BadParticleCode.h"
#include "D3DApp.h"

extern LPDIRECT3D9			g_pD3D				= NULL;
extern LPDIRECT3DDEVICE9	g_pD3DDevice		= NULL;
D3DDISPLAYMODE				g_d3ddm;

extern RECT g_windowRect;
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Direct3D �ʱ�ȭ.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool InitD3D(HWND hWnd, DWORD dwSetting)
{
	//. ����̽��� ������ ����ü.
	D3DPRESENT_PARAMETERS d3dpp;

	//. ����̽��� �����ϱ� ���� D3D��ü ����.
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	//. Direct3D �Ķ���� ����.
	memset(&d3dpp, 0, sizeof(D3DPRESENT_PARAMETERS));

	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;	//. Back-Buffer ��üȿ�� ����.
	d3dpp.hDeviceWindow				= hWnd;
	d3dpp.BackBufferCount			= 1;						
	d3dpp.EnableAutoDepthStencil	= TRUE;						//. Depth-Buffer ��� ����.
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;				//. Depth_Buffer
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	int Width	= 0;
	int Height	= 0;
	//. ������ D3D ����̽� ���ð� ���ٸ�
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
	//. ������ ���.
	if(dwSetting & DS_WINDOW)
	{
		d3dpp.Windowed			= TRUE;
		d3dpp.BackBufferFormat	= g_d3ddm.Format;
	}
	//. Ǯ��ũ�� ���
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
		�ϵ���� ������ �̿��� ����ȭ(D3DDeVTYPE_HAL),
		����Ʈ���� ������ȯ(D3DCREATE_SOFTWARE_VAERTEXPROCESSING)�� ����ϰ�
		�Ķ����(d3dpp)�� �����Ͽ� Direct3D�� �����Ѵ�.
		*/

		HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,	D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice);

		//. ���н� ���� �޽��� �ڽ� ���.
		if(FAILED(hr))
		{
			MessageBox(hWnd, "D3D ��ġ ���� ����:", "����", MB_ICONERROR);
			return false;
		}

		int windowsWidth = abs(g_windowRect.left) + abs(g_windowRect.right) - Width;
		int windowsHeight = abs(g_windowRect.top) + abs(g_windowRect.bottom) - Height;

		//. ����Ʈ�� �����Ѵ�.
		D3DVIEWPORT9 ViewPort = {0, 0, Width, Height, 0.0f, 1.0f};
		g_pD3DDevice->SetViewport(&ViewPort);

		//.��� ����.
		SetupMatrices(Width, Height);

		/*! 2D �׷����� ��Ÿ���Ƿ� ���� ������ ���� �ʴ´�. */
		// �ø� ����� ������� �ʴ´�.
		g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		//. ������ ����� ������� �ʴ´�.
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//. 2D ��������Ʈ�� ����� ���̹Ƿ� Z���۴� �ʿ����� �ʴ�.
		g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		//. �ؽ�ó ����.
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

		//.���� ����(�ǽð� ������ ���� ��ũ�� 292P)
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0);

		//! ��ƼŬ ��ũ��Ʈ �ʱ�ȭ
		//g_pBadParticleCode->SetDevice(g_pD3DDevice);

		return TRUE;
}
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. �޸� ����
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
//. ��� ����.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void SetupMatrices(int Width, int Height)
{
	//.�����ؼ� ��� ����.

	D3DXVECTOR3 vEyePt(0, 0.0f, -1.0f);
	D3DXVECTOR3 vLookatPt(0, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIX matOrtho;
	//. ������ ���Ϸ� ������ �Ŀ� ���� ���κ��� �������� �����Ѵ�. ( ����� �»����� 0,0���� ����)
	D3DXMatrixOrthoOffCenterLH(&matOrtho, 0.0f, (float)(Width), (float)(Height), 0.0f, 0.0f, 1.0f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matOrtho);
}