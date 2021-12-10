#include "Sprite.h"
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ��������Ʈ�� �����Ѵ�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool CreateSprite(SSprite *pSprite, STexture *pTexture, int Width, int Height)
{
	//. ���ؽ� ���ۿ� ���� ������ ���� ����
	if(pSprite->m_pVertexBuffer != NULL)
	{
		return FALSE;
	}

	//. �� �������� ������ ������ ���۸� �����.
	if(FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(SpriteVertex)*4,0,
		D3DFVF_SPRITEVERTEX, D3DPOOL_DEFAULT, &pSprite->m_pVertexBuffer, NULL)))
	{
		MessageBox(NULL,"���ؽ� ���� ���� ����","����",MB_ICONERROR);
		ReleaseSprite(pSprite);

		return FALSE;
	}

	//. ���� ���ۿ� lock�� �ɰ� ��������Ʈ ũ��� ���� ũ���� �簢���� �����.
	SpriteVertex *pSpriteVertex;

	if(FAILED(pSprite->m_pVertexBuffer->Lock(0,sizeof(SpriteVertex)*4,(void **)&pSpriteVertex, 0)))
	{
		MessageBox(NULL, "Lock ����", "����", MB_ICONERROR);
		ReleaseSprite(pSprite);

		return FALSE;
	}
	/*!
	�ؽ��ĸ� -0.5f ����� �ȼ��� �ؼ��� ��Ȯ�ϰ� ��ġ�Ѵ�.
	D3DXMatrixOrthoOffCenterlH�� ���缭 ����
	D3DXMatrixorthoLH�� ����� ���� �¿츦 �ٲ��ָ� �ȴ�.
	*/
	pSpriteVertex[0].x				=-0.5f - (float)(Width/2);
	pSpriteVertex[0].y				=-0.5f - (float)(Height/2);
	pSpriteVertex[0].z				=0.0f;
	pSpriteVertex[0].color			=0xffffffff;
	pSpriteVertex[0].tu				=0.0f;
	pSpriteVertex[0].tv				=0.0f;

	pSpriteVertex[1].x				=(float)(Width/2)-0.5f;
	pSpriteVertex[1].y				=-0.5f - (float)(Height/2);
	pSpriteVertex[1].z				=0.0f;
	pSpriteVertex[1].color			=0xffffffff;
	pSpriteVertex[1].tu				=1.0f;
	pSpriteVertex[1].tv				=0.0f;

	pSpriteVertex[2].x				=-0.5f - (float)(Width/2);
	pSpriteVertex[2].y				=(float)(Height/2);
	pSpriteVertex[2].z				=0.0f;
	pSpriteVertex[2].color			=0xffffffff;
	pSpriteVertex[2].tu				=0.0f;
	pSpriteVertex[2].tv				=1.0f;

	pSpriteVertex[3].x				=(float)(Width/2)-0.5f;
	pSpriteVertex[3].y				=(float)(Height/2)-0.5f;
	pSpriteVertex[3].z				=0.0f;
	pSpriteVertex[3].color			=0xffffffff;
	pSpriteVertex[3].tu				=1.0f;
	pSpriteVertex[3].tv				=1.0f;

	if(FAILED(pSprite->m_pVertexBuffer->Unlock()))
	{
		MessageBox(NULL, "Unlock ����", "����", MB_ICONERROR);
		ReleaseSprite(pSprite);
		return FALSE;
	}

	pSprite->m_pTexture = pTexture;
	pSprite->m_Width	= Width;
	pSprite->m_Height	= Height;

	return FALSE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 2D ��������Ʈ�� ȿ���� �Բ� ����Ѵ�.
//.-------------------------------------------------------------------------------------------------------------------------------------------
void Put(SSprite *pSprite, int dx, int dy,bool  vertical, float fScaling, float fRotate, DWORD dwColor, DWORD dwEffect)
{
	D3DXMatrixIdentity(&pSprite->m_matWorld);

	Scaling(pSprite, fScaling ,vertical);
	Rotate(pSprite, fRotate);
	ChangeDiffuse(pSprite, dwColor);
	SpriteEffect(pSprite, dwEffect);

	D3DXMATRIX matTrans;
	D3DXMatrixTranslation(&matTrans, (float)(dx + pSprite->m_Width/2), (float)(dy + pSprite->m_Height/2), 0.0f);
	D3DXMatrixMultiply(&pSprite->m_matWorld, &pSprite->m_matWorld, &matTrans);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &pSprite->m_matWorld);
	g_pD3DDevice->SetTexture(0, pSprite->m_pTexture->m_pTexture);
	g_pD3DDevice->SetStreamSource(0, pSprite->m_pVertexBuffer, 0, sizeof(SpriteVertex));
	g_pD3DDevice->SetFVF(D3DFVF_SPRITEVERTEX);
	g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	SetDefaultAlphaState();
	RestorDiffuse(pSprite, dwColor);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Ȯ�� ���.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void Scaling(SSprite *pSprite, float fScaling,bool  vertical)
{
	//if(fScaling == 1.0f)
	//{
	//	return;
	//}
	D3DXMATRIX matScale;
	if( vertical)
	{
		D3DXMatrixScaling(&matScale, -fScaling, 1.0f, 0.0f);
	}
	else
	{
		D3DXMatrixScaling(&matScale, fScaling, fScaling, 0.0f);
	}
	D3DXMatrixMultiply(&pSprite->m_matWorld, &pSprite->m_matWorld, &matScale);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ȸ��.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void Rotate(SSprite *pSprite, float fRotate)
{
	if(fRotate == 0.0f)
	{
		return;
	}

	D3DXMATRIX matRotate;
	D3DXMatrixRotationZ(&matRotate, fRotate);
	D3DXMatrixMultiply(&pSprite->m_matWorld, &pSprite->m_matWorld, &matRotate);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ���� ���� ��ȭ��Ų��.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void ChangeDiffuse(SSprite *pSprite, DWORD dwColor)
{
	if(dwColor == 0xffffffff)
	{
		return;
	}

	SpriteVertex *pSpriteVertex;

	pSprite->m_pVertexBuffer->Lock(0,sizeof(SpriteVertex)*4, (void**)&pSpriteVertex,0);

	for(int i=0; i<4; i++)
	{
		pSpriteVertex[i].color = dwColor;
	}

	pSprite->m_pVertexBuffer->Unlock();
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ���� ���� ������� �ǵ�����.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void RestorDiffuse(SSprite *pSprite, DWORD dwColor)
{
	if(dwColor == 0xffffffff)
	{
		return;
	}
	SpriteVertex *pSpriteVertex;

	pSprite->m_pVertexBuffer->Lock(0, sizeof(SpriteVertex)*4, (void**)&pSpriteVertex,0);

	for(int i=0; i<4; i++)
	{
		pSpriteVertex[i].color = 0xffffffff;
	}
	pSprite->m_pVertexBuffer->Unlock();
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ����Ʈ�� �������� �ű⿡ �´� �Լ��� �ҷ��´�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void SpriteEffect(SSprite *pSprite, DWORD dwEffect)
{
	if(dwEffect & EFFECT_NONE)
	{
		return;
	}

	if(dwEffect & EFFECT_FLIP_HORZ)
	{
		D3DXMATRIX matFlipHorz;
		D3DXMatrixIdentity(&matFlipHorz);
		matFlipHorz._11 = -1.0f;

		D3DXMatrixMultiply(&pSprite->m_matWorld, &pSprite->m_matWorld, &matFlipHorz);
	}

	if(dwEffect & EFFECT_FLIP_VERT)
	{
		D3DXMATRIX matFlipVert;
		D3DXMatrixIdentity(&matFlipVert);
		matFlipVert._22 = -1.0f;

		D3DXMatrixMultiply(&pSprite->m_matWorld, &pSprite->m_matWorld, &matFlipVert);
	}

	if(dwEffect & EFFECT_OVERLAY)
	{
		SetParticleAlphaState();
	}
}
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. �⺻���� ���ĺ��� ���·� ���� ���¸� �����Ѵ�
//.-------------------------------------------------------------------------------------------------------------------------------------------

void SetDefaultAlphaState()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ��ƼŬ�� ���Ǵ� ���� ���·� ���� ���¸� �����Ѵ�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void SetParticleAlphaState()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ���� �����͸� ����
//.-------------------------------------------------------------------------------------------------------------------------------------------

void ReleaseSprite(SSprite *pSprite)
{
	ReleaseTexture(pSprite->m_pTexture);
	pSprite->m_pTexture = NULL;
	SAFE_RELEASE(pSprite->m_pVertexBuffer);
}