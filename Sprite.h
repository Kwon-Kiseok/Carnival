//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : Sprit.h
//.
//. Sprite Header File for the 2006 Creator Library
//.
//. 작성일 : 2004. 04. 08.
//.
//. 작성자 : 03학번 김 권 교
//.
//. 수정일 : 2006. 5. 28.
//.
//. 작성자 : 04학번 김 형 철
//.-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Texture.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 스프라이트 정점 구조체
//.-------------------------------------------------------------------------------------------------------------------------------------------
struct SpriteVertex
{
	float x,y,z;
	DWORD color;
	float tu, tv;
};

#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//. 스프라이트 이펙트 효과를 주기 위한 열거형.
enum SpriteEffectFlag
{
	EFFECT_NONE			= 0x00,
	EFFECT_FLIP_HORZ	= 0x01,				//. 좌우반전
	EFFECT_FLIP_VERT	= 0x02,				//. 상하반전
	EFFECT_OVERLAY		= 0x04,				//. 오버레이
	EFFECT_DEFAULT		= EFFECT_NONE		//. 오버레이
};

//. 스프라이트 구조체.
struct SSprite
{
	SSprite() {		m_pTexture = NULL ; m_pVertexBuffer = NULL; m_Width = m_Height = 0;}
	STexture*					m_pTexture;
	LPDIRECT3DVERTEXBUFFER9		m_pVertexBuffer;
	D3DXMATRIX					m_matWorld;
	int							m_Width;
	int							m_Height;
};

bool CreateSprite(SSprite *pSprite, STexture * pTexture, int Width, int height);
void ReleaseSprite(SSprite *pSprite);

void Scaling(SSprite *pSprite, float fScaling,bool  vertical = false);
void Rotate(SSprite *pSprite, float fRotate);
void ChangeDiffuse(SSprite *pSprite, DWORD dwColor);
void RestorDiffuse(SSprite *pSprite, DWORD dwColor);
void SpriteEffect(SSprite *pSprite, DWORD dwEffect);

//void Put(SSprite *pSprite, int dx, int dy);
void Put(SSprite *pSprite, int dx, int dy, bool  vertical = false,float fScaling=1, float fRotate=0, DWORD dwColor = 0xffffffff, DWORD dwEffect = EFFECT_DEFAULT);

inline void SetDefaultAlphaState();
inline void SetParticleAlphaState();

#endif