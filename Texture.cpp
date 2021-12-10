#include "Texture.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. DirectX �Լ��� �̿��ؼ� �׸������� �ҷ��´�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool TextureLoad(STexture *pTexture, LPSTR szFileName, DWORD dwColorkey, D3DFORMAT format)
{
	//. �޸𸮸� �����ϰ�, �ʱ�ȭ�� ���� �Ѵ�.
	ReleaseTexture(pTexture);

	//. ����̽��� �����̸��� ������ ����.
	if(g_pD3DDevice == NULL || szFileName == NULL)
	{
		return FALSE;
	}

	//. ������ �⺻���� �Ͽ� �ؽ��ĸ� �����Ѵ�.
	if(FAILED(D3DXCreateTextureFromFileEx(g_pD3DDevice, szFileName, D3DX_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, format, D3DPOOL_MANAGED, D3DX_FILTER_POINT, D3DX_FILTER_POINT, dwColorkey, NULL, NULL, &pTexture->m_pTexture)))
	{
		MessageBox(NULL, "Texture���� ����", "����", MB_ICONERROR);
		return FALSE;
	}

	//. �ؽ��� ������ ������Ʈ �Ѵ�.
	UpDateInfo(pTexture);
	return TRUE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. �ؽ��� ������ ������Ʈ �Ѵ�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool UpDateInfo(STexture *pTexture)
{
	//. ǥ���� ����ϴ� ����ü.
	D3DSURFACE_DESC d3dsd;

	if(pTexture->m_pTexture ==NULL)
	{
		return FALSE;
	}

	//. ������ ť�� �ؽ��� ������ 1�� ���� ����� ��� �´�.
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
//. �ؽ��� �޸𸮸� �����ϰ� ��� ���� �ʱ�ȭ�� �Ѵ�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool ReleaseTexture(STexture *pTexture)
{
	SAFE_RELEASE(pTexture->m_pTexture);

	pTexture->m_Width	= NULL;
	pTexture->m_Height	= NULL;
	pTexture->m_format	= D3DFMT_UNKNOWN;

	return TRUE;
}