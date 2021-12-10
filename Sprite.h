//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : Sprit.h
//.
//. Sprite Header File for the 2006 Creator Library
//.
//. �ۼ��� : 2004. 04. 08.
//.
//. �ۼ��� : 03�й� �� �� ��
//.
//. ������ : 2006. 5. 28.
//.
//. �ۼ��� : 04�й� �� �� ö
//.-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "Texture.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ��������Ʈ ���� ����ü
//.-------------------------------------------------------------------------------------------------------------------------------------------
struct SpriteVertex
{
	float x,y,z;
	DWORD color;
	float tu, tv;
};

#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//. ��������Ʈ ����Ʈ ȿ���� �ֱ� ���� ������.
enum SpriteEffectFlag
{
	EFFECT_NONE			= 0x00,
	EFFECT_FLIP_HORZ	= 0x01,				//. �¿����
	EFFECT_FLIP_VERT	= 0x02,				//. ���Ϲ���
	EFFECT_OVERLAY		= 0x04,				//. ��������
	EFFECT_DEFAULT		= EFFECT_NONE		//. ��������
};

//. ��������Ʈ ����ü.
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