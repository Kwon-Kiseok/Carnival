//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : Animation.h
//.
//. Sprite Header File for the 2006 Creator Library.
//.
//. 작성일 : 2004. 06. 07.
//. 
//. 작성자 : 03학번 김 권 교
//.
//. 작성일 : 2006. 05. 28.
//.
//. 작성자 : 04학번 김 형 철
//.
//. 수정일 : 2008. 06. 01.
//.
//. 수정자 : 07학번 정 재 학
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
	WORD		m_NumFrame;		//. 총 프레임.
	WORD		m_NowFrame;		//. 현재 프레임.
	BOOL		m_Loop;			//. 계속 애니메이션 시킬것인가 비교
	float		m_LastTime;		//. 마지막 시간 값 저장
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
//. 함수 오버로딩(C++용법, 함수의 인자가 틀리면 다른 함수로 인식해 컴파일러가 알아서 호출)
void Put(SAnimation *pAni, int x, int y);
void Put(SAnimation *pAni, int x, int y, float fScaling, float fRotate, DWORD dwColor = 0xffffffff, DWORD dwEffect = EFFECT_DEFAULT);
void AniProc(SAnimation *pAni);
void ReleaseAni(SAnimation *pAni);

#endif