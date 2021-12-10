#include "Animation.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ���ϸ��̼� ������ �ִ� �ؽ�Ʈ ������ �о�´�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void ReleaseFrame(SAnimation* pAni);

bool LoadAnimation(SAnimation *pAni, LPSTR szFileName)
{
	//�������� �ʱ�ȭ ��Ų��
	pAni->m_NowFrame = 0;

	//pframe�� �ִ��� ������ �Ǵ�
	if( NULL != pAni->m_pFrame)
	{
		ReleaseFrame(pAni);
	}

	FILE *fp;
	fp = fopen(szFileName,"r");
	int NumFrame;
	//. ������ ���� �о�´�.
	fscanf(fp, "%d", &NumFrame);
	pAni->m_NumFrame = NumFrame;
	BOOL Loop;

	//. �ݺ��Ǵ� �ִ����� �ƴ������о� �´�. 1�̸� �ݺ� 0�̸� �ѹ��� �ִϸ��̼�
	fscanf(fp,"%d",&Loop);
	pAni->m_Loop = Loop;

	
	//.�ִϸ��̼� ����ŭ �Ҵ�.

	pAni->m_pFrame = new SFrame[pAni->m_NumFrame];
	char szBmp[256];
	memset(szBmp, NULL, sizeof(szBmp));
	DWORD	r,g,b;
	DWORD	Delay;
	int		Width;
	int		Height;
	for(int i=0; i<pAni->m_NumFrame; ++i)
	{
		//. bmp �÷�Ű (r g b) �ؽ��� ũ��(����, ����) ������
		fscanf(fp,"%s %d %d %d %d %d %d",szBmp, &r, &g, &b, &Width, &Height, &Delay);
		//. �ؽ��ĸ� �ҷ��´�.
		pAni->m_pFrame[i].m_pTexture	= new STexture;
		//. �޸𸮸� �����ϰ� ������ ���� �����������.
		memset(pAni->m_pFrame[i].m_pTexture, 0, sizeof(STexture));
		TextureLoad(pAni->m_pFrame[i].m_pTexture, szBmp, D3DCOLOR_ARGB(0,r,g,b));
		//. ��������Ʈ ����
		pAni->m_pFrame[i].m_pSprite		= new SSprite;
		//.�޸𸮸� �����ϰ� ������ ���� �����������.
		memset(pAni->m_pFrame[i].m_pSprite, 0, sizeof(SSprite));
		CreateSprite(pAni->m_pFrame[i].m_pSprite, pAni->m_pFrame[i].m_pTexture, Width, Height);
		//.	������ ���� �Է��Ѵ�.
		pAni->m_pFrame[i].m_Delay = Delay;
	}
	fclose(fp);
	return TRUE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. �޸� ����
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
//. ȿ�� ���� �ִϸ��̼� ���
//.-------------------------------------------------------------------------------------------------------------------------------------------

void Put(SAnimation *pAni, int x, int y)
{

	Put(pAni->m_pFrame[pAni->m_NowFrame].m_pSprite,x,y);
	AniProc(pAni);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. ȿ�� �ִ� �ִϸ��̼� ���
//.-------------------------------------------------------------------------------------------------------------------------------------------

void Put(SAnimation *pAni, int x, int y, float fScaling, float fRotate, DWORD dwColor, DWORD dwEffect)
{
	Put(pAni->m_pFrame[pAni->m_NowFrame].m_pSprite, x, y, fScaling, fRotate, dwColor, dwEffect);
	AniProc(pAni);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. �ִϸ��̼� �������� �������� �Ѿ�� �Ѵ�.
//.-------------------------------------------------------------------------------------------------------------------------------------------

void AniProc(SAnimation *pAni)
{
	//. ���� �ð��� �о��
	float currentTime = (float)GetTickCount();

	//. �����ð� - �Ʊ�ð� >= ���� �������� �����̺��� ũ��
	if((currentTime - pAni->m_LastTime) >= pAni->m_pFrame[pAni->m_NowFrame].m_Delay)
	{
		pAni->m_NowFrame++;
		pAni->m_LastTime = currentTime; //. �����ð��� �������ð����� ����

		//. ���� �������� �������Ӻ��� ũ��
		if(pAni->m_NowFrame >= pAni->m_NumFrame)
		{
			//. Loop�� 1�̸� �ݺ��ϱ� ���� 0���� �ʱ�ȭ �ϰ�
			//. �ƴҰ��� ������ ���������� �Ѵ�(������ ���ۿ��� ���߰� �Ѵ�)
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