//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : Animation.h
//.
//. Sprite Header File for the 2006 Creator Library.
//.
//. �ۼ��� : 2004. 06. 07.
//. 
//. �ۼ��� : 03�й� �� �� ��
//.
//. �ۼ��� : 2006. 05. 28.
//.
//. �ۼ��� : 04�й� �� �� ö
//.
//. ������ : 2008. 06. 01.
//.
//. ������ : 07�й� �� �� ��
//.-------------------------------------------------------------------------------------------------------------------------------------------

#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <stdio.h>
#include "Sprite.h"

struct SFrame
{
	DWORD		m_Delay;
	SSprite		*m_pSprite;
	STexture	*m_pTexture;
	SFrame()	{ m_Delay = 0; m_pSprite = NULL; m_pTexture = NULL;}
};

struct SAnimation
{
	SFrame		*m_pFrame;
	WORD		m_NumFrame;		//. �� ������.
	WORD		m_NowFrame;		//. ���� ������.
	BOOL		m_Loop;			//. ��� �ִϸ��̼� ��ų���ΰ� ��
	float		m_LastTime;		//. ������ �ð� �� ����
	SAnimation()
	{
		m_pFrame = NULL;
	}
};

struct Player
{
	int x;
	int y;
	int left;
	int right;
	int up;
	int down;
};


bool LoadAnimation(SAnimation *pAni, LPSTR szFileName);
//. �Լ� �����ε�(C++���, �Լ��� ���ڰ� Ʋ���� �ٸ� �Լ��� �ν��� �����Ϸ��� �˾Ƽ� ȣ��)
void Put(SAnimation *pAni, int x, int y);
void Put(SAnimation *pAni, int x, int y, float fScaling, float fRotate, DWORD dwColor = 0xffffffff, DWORD dwEffect = EFFECT_DEFAULT);
void AniProc(SAnimation *pAni);
void ReleaseAni(SAnimation *pAni);

#endif