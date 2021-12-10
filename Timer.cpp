#include "Timer.h"

//. STIME			*pFPS			= NULL;

//.--------------------------------------------------
//. �ý��� �ð��� ��� �´�(����ð�).
//.--------------------------------------------------
float GetAppTimeDelay()
{
	static BOOL			m_bTimerInitialized		= FALSE;	//.	���ػ� Ÿ�̸� ��� ����
	static BOOL			m_bUsingQPF			= FALSE;
	static LONGLONG	m_llQPFTicksPerSec		= 0;

	//.	Ÿ�̸� �ʱ�ȭ
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
	//.	���ػ� Ÿ�̸Ӱ� ���� �ɶ�
    if(m_bUsingQPF)
    {
		static LONGLONG	m_llLastElapsedTime = 0;
        LARGE_INTEGER	qwTime;
		QueryPerformanceCounter(&qwTime);

		fElapsedTime = (double) (qwTime.QuadPart - m_llLastElapsedTime) / (double)m_llQPFTicksPerSec;
		m_llLastElapsedTime = qwTime.QuadPart;
    }
	//.	���ػ� Ÿ�̸Ӱ� ���� �ɶ�
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
//. ������ ���� �ð��� ���۽ð��� �̿��� ������ �ð����� Ŭ��츦 ã�Ƴ���.
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
//. �������� �����Ѵ�. (UpDate �Լ������� ����).
//.-------------------------------------------------------------------------------
void SetFPS(STIME *pTime, float Fps)
{
	pTime->m_SecPerFrame = 1.0f / Fps;
	pTime->m_Delay.QuadPart = pTime->m_TicksPerSec.QuadPart;
}

//.-------------------------------------------------------------------------------
//. ���ϴ� �����Ӻ��� �ʹ� ������ FALSE�� ��ȯ.
//.-------------------------------------------------------------------------------
bool TimeUpdate(STIME *pTime, float dt)
{
	pTime->m_Timer += dt;		
	if(pTime->m_Timer < 0) return FALSE;

	// �������ӿ� �ش��ϴ� �ð��� ����.
	pTime->m_Timer -= pTime->m_SecPerFrame;
	return TRUE;
}

//.------------------------------------------------------------------------------
//. Update�Ŀ� frame skip�� ���� ���� ����.
//.------------------------------------------------------------------------------
bool IsFrameSkip(STIME *pTime)
{
	return pTime->m_Timer >= 0;
}