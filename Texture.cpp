#include "Texture.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. DirectX 함수를 이용해서 그림파일을 불러온다.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool TextureLoad(STexture *pTexture, LPSTR szFileName, DWORD dwColorkey, D3DFORMAT format)
{
	//. 메모리를 해제하고, 초기화를 먼저 한다.
	ReleaseTexture(pTexture);

	//. 디바이스나 파일이름이 없으면 실패.
	if(g_pD3DDevice == NULL || szFileName == NULL)
	{
		return FALSE;
	}

	//. 파일을 기본으로 하여 텍스쳐를 생성한다.
	if(FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, szFileName, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, format, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_FILTER_POINT, dwColorkey, NULL, NULL, &pTexture->m_pTexture)))
	{
		MessageBox(NULL, "Texture생성 실패", "에러", MB_ICONERROR);
		return FALSE;
	}

	//. 텍스쳐 정보를 업데이트 한다.
	UpDateInfo(pTexture);
	return TRUE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 텍스쳐 정보를 업테이트 한다.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool UpDateInfo(STexture *pTexture)
{
	//. 표면을 기술하는 구조체.
	D3DSURFACE_DESC d3dsd;

	if(pTexture->m_pTexture ==NULL)
	{
		return FALSE;
	}

	//. 지정한 큐브 텍스쳐 레벨의 1개 면의 기술을 얻어 온다.
	if(FAILED(pTexture->m_pTexture->GetLevelDesc(0, &d3dsd)))
	{
		return FALSE;
	}

	pTexture->m_Width	= d3dsd.Width;
	pTexture->m_Height	= d3dsd.Height;
	pTexture->m_format	= d3dsd.Format;

	return TRUE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 텍스쳐 메모리를 해제하고 멤버 변수 초기화를 한다.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool ReleaseTexture(STexture *pTexture)
{
	SAFE_RELEASE(pTexture->m_pTexture);

	pTexture->m_Width	= NULL;
	pTexture->m_Height	= NULL;
	pTexture->m_format	= D3DFMT_UNKNOWN;

	return TRUE;
}