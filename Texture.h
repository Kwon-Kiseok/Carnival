#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "D3DApp.h"

//�ؽ��� ����ü.
struct STexture
{
	LPDIRECT3DTEXTURE9	m_pTexture;
	int					m_Width;
	int					m_Height;
	D3DFORMAT			m_format;
};

bool TextureLoad(STexture *pTextur, LPSTR szFileName, DWORD dwColorkey, D3DFORMAT format = D3DFMT_A8R8G8B8);
// DirectX �Լ��� �̿��� �ε�
bool UpDateInfo(STexture *pTexture);
bool ReleaseTexture(STexture *pTexture);

#endif