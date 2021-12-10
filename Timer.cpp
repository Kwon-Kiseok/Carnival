#include "Timer.h"

//. STIME			*pFPS			= NULL;

//.--------------------------------------------------
//. 시스템 시간을 얻어 온다(경과시간).
//.--------------------------------------------------
float GetAppTimeDelay()
{
	static BOOL			m_bTimerInitialized		= FALSE;	//.	고해상도 타이머 사용 유무
	static BOOL			m_bUsingQPF			= FALSE;
	static LONGLONG	m_llQPFTicksPerSec		= 0;

	//.	타이머 초기화
	if(!m_bTimerInitialized)
	{
		m_bTimerInitialized = TRUE;

		LARGE_INTEGER qwTicksPerSec;
		m_bUsingQPF = (QueryPerformanceFrequency(&qwTicksPerSec) == 0) ? FALSE : TRUE;

		if(m_bUsingQPF)
			m_llQPFTicksPerSec = qwTicksPerSec.QuadPart;
	}

	double fTime;
	double fElapsedTime;
	//.	고해상도 타이머가 적용 될때
    if(m_bUsingQPF)
    {
		static LONGLONG	m_llLastElapsedTime = 0;
        LARGE_INTEGER	qwTime;
		QueryPerformanceCounter(&qwTime);

		fElapsedTime = (double) (qwTime.QuadPart - m_llLastElapsedTime) / (double)m_llQPFTicksPerSec;
		m_llLastElapsedTime = qwTime.QuadPart;
    }
	//.	저해상도 타이머가 적용 될때
    else
    {
		static double m_fLastElapsedTime  = 0.0;
		fTime = timeGetTime() * 0.001;
    
        fElapsedTime = (double) (fTime - m_fLastElapsedTime);
        m_fLastElapsedTime = fTime;
    }

	return (float)fElapsedTime;
}

void TimeReset(STIME *pTime)
{
	QueryPerformanceCounter(&pTime->m_Start);
}

void TimeClear(STIME *pTime)
{
	SetFPS(pTime, 60.0f);
	TimeReset(pTime);

	pTime->m_Timer = 0;
}

//.-------------------------------------------------------------------------------
//. 루프의 끝난 시간과 시작시간을 이용해 딜레이 시간보다 클경우를 찾아낸다.
//.-------------------------------------------------------------------------------
bool TimeCheck(STIME *pTime)
{
	QueryPerformanceCounter(&pTime->m_End);

	if(pTime->m_End.QuadPart - pTime->m_Start.QuadPart >= pTime->m_Delay.QuadPart)
	{
	    QueryPerformanceCounter(&pTime->m_Start);
		return TRUE;
	}

	return FALSE;
}

//.-------------------------------------------------------------------------------
//. 프레임을 설정한다. (UpDate 함수에서만 적용).
//.-------------------------------------------------------------------------------
void SetFPS(STIME *pTime, float Fps)
{
	pTime->m_SecPerFrame = 1.0f / Fps;
	pTime->m_Delay.QuadPart = pTime->m_TicksPerSec.QuadPart;
}

//.-------------------------------------------------------------------------------
//. 원하는 프레임보다 너무 빠르면 FALSE를 반환.
//.-------------------------------------------------------------------------------
bool TimeUpdate(STIME *pTime, float dt)
{
	pTime->m_Timer += dt;		
	if(pTime->m_Timer < 0) return FALSE;

	// 한프레임에 해당하는 시간을 뺀다.
	pTime->m_Timer -= pTime->m_SecPerFrame;
	return TRUE;
}

//.------------------------------------------------------------------------------
//. Update후에 frame skip를 수행 할지 결정.
//.------------------------------------------------------------------------------
bool IsFrameSkip(STIME *pTime)
{
	return pTime->m_Timer >= 0;
}