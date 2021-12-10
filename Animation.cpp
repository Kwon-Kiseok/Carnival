#include "Animation.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 에니메이션 정보가 있는 텍스트 파일을 읽어온다.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void ReleaseFrame(SAnimation* pAni);

bool LoadAnimation(SAnimation *pAni, LPSTR szFileName)
{
	//프레임을 초기화 시킨다
	pAni->m_NowFrame = 0;

	//pframe이 있는지 없는지 판단
	if( NULL != pAni->m_pFrame)
	{
		ReleaseFrame(pAni);
	}

	FILE *fp;
	fp = fopen(szFileName,"r");
	int NumFrame;
	//. 프레임 수를 읽어온다.
	fscanf(fp, "%d", &NumFrame);
	pAni->m_NumFrame = NumFrame;
	BOOL Loop;

	//. 반복되는 애니인지 아닌지를읽어 온다. 1이면 반복 0이면 한번만 애니메이션
	fscanf(fp,"%d",&Loop);
	pAni->m_Loop = Loop;

	
	//.애니메이션 수만큼 할당.

	pAni->m_pFrame = new SFrame[pAni->m_NumFrame];
	char szBmp[256];
	memset(szBmp, NULL, sizeof(szBmp));
	DWORD	r,g,b;
	DWORD	Delay;
	int		Width;
	int		Height;
	for(int i=0; i<pAni->m_NumFrame; ++i)
	{
		//. bmp 컬러키 (r g b) 텍스쳐 크기(가로, 세로) 딜레이
		fscanf(fp,"%s %d %d %d %d %d %d",szBmp, &r, &g, &b, &Width, &Height, &Delay);
		//. 텍스쳐를 불러온다.
		pAni->m_pFrame[i].m_pTexture	= new STexture;
		//. 메모리를 생성하고 쓰레기 값을 정리해줘야함.
		memset(pAni->m_pFrame[i].m_pTexture, 0, sizeof(STexture));
		TextureLoad(pAni->m_pFrame[i].m_pTexture, szBmp, D3DCOLOR_ARGB(0,r,g,b));
		//. 스프라이트 생성
		pAni->m_pFrame[i].m_pSprite		= new SSprite;
		//.메모리를 생성하고 쓰레기 값을 정리해줘야함.
		memset(pAni->m_pFrame[i].m_pSprite, 0, sizeof(SSprite));
		CreateSprite(pAni->m_pFrame[i].m_pSprite, pAni->m_pFrame[i].m_pTexture, Width, Height);
		//.	딜레이 값을 입력한다.
		pAni->m_pFrame[i].m_Delay = Delay;
	}
	fclose(fp);
	return TRUE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 메모리 해제
//.-------------------------------------------------------------------------------------------------------------------------------------------

void ReleaseAni(SAnimation *pAni)
{
	ReleaseFrame(pAni);
	SAFE_DELETE(pAni);
}

void ReleaseFrame(SAnimation* pAni)
{
	for(int i = 0; i<pAni->m_NumFrame; ++i)
	{
		if(pAni->m_pFrame[i].m_pTexture)
		{
			ReleaseTexture(pAni->m_pFrame[i].m_pTexture);
		}
		if(pAni->m_pFrame[i].m_pSprite)
		{
			ReleaseSprite(pAni->m_pFrame[i].m_pSprite);
		}
	}
	SAFE_DELETE_ARRAY(pAni->m_pFrame);
}
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 효과 없이 애니메이션 출력
//.-------------------------------------------------------------------------------------------------------------------------------------------

void Put(SAnimation *pAni, int x, int y)
{

	Put(pAni->m_pFrame[pAni->m_NowFrame].m_pSprite,x,y);
	AniProc(pAni);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 효과 있는 애니메이션 출력
//.-------------------------------------------------------------------------------------------------------------------------------------------

void Put(SAnimation *pAni, int x, int y, float fScaling, float fRotate, DWORD dwColor, DWORD dwEffect)
{
	Put(pAni->m_pFrame[pAni->m_NowFrame].m_pSprite, x, y, fScaling, fRotate, dwColor, dwEffect);
	AniProc(pAni);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 애니메이션 프레임을 다음으로 넘어가게 한다.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void AniProc(SAnimation *pAni)
{
	//. 현제 시간값 읽어옴
	float currentTime = (float)GetTickCount();

	//. 현제시간 - 아까시간 >= 현제 프레임의 딜레이보다 크면
	if((currentTime - pAni->m_LastTime) >= pAni->m_pFrame[pAni->m_NowFrame].m_Delay)
	{
		pAni->m_NowFrame++;
		pAni->m_LastTime = currentTime; //. 현제시간을 마지막시간으로 대입

		//. 현제 프레임이 총프레임보다 크면
		if(pAni->m_NowFrame >= pAni->m_NumFrame)
		{
			//. Loop가 1이면 반복하기 위해 0으로 초기화 하고
			//. 아닐경우는 마지막 프레임으로 한다(마지막 동작에서 멈추게 한다)
			if(pAni->m_Loop)
			{
				pAni->m_NowFrame = 0;
			}
			else
			{
				pAni->m_NowFrame = pAni->m_NowFrame - 1;
			}
		}
	}
}