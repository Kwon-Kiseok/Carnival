//.-----------------------------------------------------------------------------------------------------------------------
//.
//.	Joker Direct3D in 2D Library
//.
//.  FrameSkip Header File
//.
//.  Data 04/06/10/�� �̸� 2�� 23�� ~
//.
//.  Make by Joker (���ڳ� �ڷ� ����)
//.
//.-----------------------------------------------------------------------------------------------------------------------
#ifndef _JOKER_TIME_HEADER_
#define _JOKER_TIME_HEADER_

#include "GameMain.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

struct STIME
{
	DWORD			m_Count;
	LARGE_INTEGER	m_Start;
	LARGE_INTEGER	m_End;
	LARGE_INTEGER	m_Delay;
	LARGE_INTEGER	m_TicksPerSec;

	int				m_FPS;
	float			m_Timer;
	float			m_SecPerFrame;

	STIME() { m_Timer = 0; m_Count = 0; m_FPS = 0; QueryPerformanceFrequency(&m_TicksPerSec); }
};

float	GetAppTimeDelay();				//.	�ý��� �ð��� ���´�

void	TimeReset(STIME *pTime);
void	TimeClear(STIME *pTime);
bool	TimeCheck(STIME *pTime);
void	SetFPS(STIME *pTime, float Fps);
bool	TimeUpdate(STIME *pTime, float dt);
bool	IsFrameSkip(STIME *pTime);
	
extern STIME		*pFPS;
extern float		dt;

#endif