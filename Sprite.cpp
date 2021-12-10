#include "Sprite.h"
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 스프라이트를 생성한다.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool CreateSprite(SSprite *pSprite, STexture *pTexture, int Width, int Height)
{
	//. 버텍스 버퍼에 값이 있으면 실패 리턴
	if(pSprite->m_pVertexBuffer != NULL)
	{
		return FALSE;
	}

	//. 네 꼭지점을 보관할 꼭지점 버퍼를 만든다.
	if(FAILED(g_pD3DDevice->CreateVertexBuffer(sizeof(SpriteVertex)*4,0,
		D3DFVF_SPRITEVERTEX, D3DPOOL_DEFAULT, &pSprite->m_pVertexBuffer, NULL)))
	{
		MessageBox(NULL,"버텍스 버퍼 생성 실패","에러",MB_ICONERROR);
		ReleaseSprite(pSprite);

		return FALSE;
	}

	//. 정점 버퍼에 lock을 걸고 스프라이트 크기와 같은 크기의 사각형을 만든다.
	SpriteVertex *pSpriteVertex;

	if(FAILED(pSprite->m_pVertexBuffer->Lock(0,sizeof(SpriteVertex)*4,(void **)&pSpriteVertex, 0)))
	{
		MessageBox(NULL, "Lock 실패", "에러", MB_ICONERROR);
		ReleaseSprite(pSprite);

		return FALSE;
	}
	/*!
	텍스쳐를 -0.5f 해줘야 픽셀과 텍셀이 정확하게 일치한다.
	D3DXMatrixOrthoOffCenterlH에 맞춰서 셋팅
	D3DXMatrixorthoLH을 쓸경우 상하 좌우를 바꿔주면 된다.
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
		MessageBox(NULL, "Unlock 실패", "에러", MB_ICONERROR);
		ReleaseSprite(pSprite);
		return FALSE;
	}

	pSprite->m_pTexture = pTexture;
	pSprite->m_Width	= Width;
	pSprite->m_Height	= Height;

	return FALSE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 2D 스프라이트를 효과와 함께 출력한다.
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
//. 확대 축소.
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
//. 회전.
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
//. 정점 색을 변화시킨다.
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
//. 정점 색을 원래대로 되돌린다.
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
//. 이펙트가 쓰여지면 거기에 맞는 함수를 불러온다.
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
//. 기본적인 알파블렌딩 상태로 렌더 상태를 변경한다
//.-------------------------------------------------------------------------------------------------------------------------------------------

void SetDefaultAlphaState()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 파티클에 사용되는 블렌딩 상태로 렌더 상태를 변경한다.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void SetParticleAlphaState()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 정점 데이터를 삭제
//.-------------------------------------------------------------------------------------------------------------------------------------------

void ReleaseSprite(SSprite *pSprite)
{
	ReleaseTexture(pSprite->m_pTexture);
	pSprite->m_pTexture = NULL;
	SAFE_RELEASE(pSprite->m_pVertexBuffer);
}