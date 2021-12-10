#include "Win.h"
#include "Input.h"
#include "Text.h"
#include "SceneManage.h"
#include "Chapter1.h"
#include "GameMain.h"

STexture	*pT_Chapter_1_BackGround = NULL;
STexture	*pT_Inventory_1 = NULL;

STexture	*pT_SeongHoon_1 = NULL;
STexture	*pT_Minwoo_1 = NULL;
STexture	*pT_Soyeong_1 = NULL;
STexture	*pT_DaeHo_1 = NULL;

SSprite		*pS_Chapter_1_BackGround = NULL;
SSprite		*pS_Inventory_1 = NULL;

SSprite	*pS_SeongHoon_1 = NULL;
SSprite	*pS_Minwoo_1 = NULL;
SSprite	*pS_Soyeong_1 = NULL;
SSprite	*pS_DaeHo_1 = NULL;

SAnimation  *pA_ScriptBox_1 = NULL;
SAnimation	*pA_SteamAni = NULL;
SAnimation  *pA_SteamCloseUp = NULL;
SAnimation	*pA_Stage2_Ani = NULL;
extern POINT CursorPos;

extern char character;
extern char tempText1[100];
extern char tempText2[100];
extern char NameText[100];
extern bool Click;
extern int ClickCount;
SText		CharacterName_1;
SText		KeyWord_1;
SText		ChatText_1;

FILE *TestFile_1 = fopen("Stage2.txt", "rt");

bool LoadChapter1Data()
{
	//.2챕터 배경.아무 이벤트도 실행하지 않은 상태
	pT_Chapter_1_BackGround = new STexture;
	memset(pT_Chapter_1_BackGround, 0, sizeof(STexture));
	TextureLoad(pT_Chapter_1_BackGround,"Stage2_BackGround_1.png", D3DCOLOR_ARGB(255,0,255,0));

	pS_Chapter_1_BackGround = new SSprite;
	memset(pS_Chapter_1_BackGround, 0, sizeof(SSprite));
	CreateSprite(pS_Chapter_1_BackGround, pT_Chapter_1_BackGround, 1080, 600);

	//.인벤토리.
	pT_Inventory_1 = new STexture;
	memset(pT_Inventory_1, 0, sizeof(STexture));
	TextureLoad(pT_Inventory_1, "Inventory.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Inventory_1 = new SSprite;
	memset(pS_Inventory_1, 0, sizeof(SSprite));
	CreateSprite(pS_Inventory_1, pT_Inventory_1, 300,800);

	//승훈
	pT_SeongHoon_1 = new STexture;
	memset(pT_SeongHoon_1, 0, sizeof(STexture));
	TextureLoad(pT_SeongHoon_1, "Kangseonghoon.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_SeongHoon_1 = new SSprite;
	memset(pS_SeongHoon_1, 0, sizeof(SSprite));
	CreateSprite(pS_SeongHoon_1, pT_SeongHoon_1, 270, 387);
	//민우
	pT_Minwoo_1 = new STexture;
	memset(pT_Minwoo_1, 0, sizeof(STexture));
	TextureLoad(pT_Minwoo_1, "Jangminwoo.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Minwoo_1 = new SSprite;
	memset(pS_Minwoo_1, 0, sizeof(SSprite));
	CreateSprite(pS_Minwoo_1, pT_Minwoo_1, 250, 382);
	//소영
	pT_Soyeong_1 = new STexture;
	memset(pT_Soyeong_1, 0, sizeof(STexture));
	TextureLoad(pT_Soyeong_1, "Jeonsoyeong.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Soyeong_1 = new SSprite;
	memset(pS_Soyeong_1, 0, sizeof(SSprite));
	CreateSprite(pS_Soyeong_1, pT_Soyeong_1, 270, 364);
	//대호
	pT_DaeHo_1 = new STexture;
	memset(pT_DaeHo_1, 0, sizeof(STexture));
	TextureLoad(pT_DaeHo_1, "Choidaeho.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_DaeHo_1 = new SSprite;
	memset(pS_DaeHo_1, 0, sizeof(SSprite));
	CreateSprite(pS_DaeHo_1, pT_DaeHo_1, 351, 400);


	
	//.대화상자.
	pA_ScriptBox_1 = new SAnimation;
	memset(pA_ScriptBox_1, 0, sizeof(SAnimation));
	LoadAnimation(pA_ScriptBox_1, "ScriptBoxAni.txt");

	//.연기 .
	pA_SteamAni = new SAnimation;
	memset(pA_SteamAni, 0, sizeof(SAnimation));
	LoadAnimation(pA_SteamAni, "SteamAni.txt");

	pA_SteamCloseUp = new SAnimation;
	memset(pA_SteamCloseUp, 0, sizeof(SAnimation));
	LoadAnimation(pA_SteamCloseUp, "Steam_CloseUp.txt");

	//.2스테이지 시작 애니메이션.
	pA_Stage2_Ani = new SAnimation;
	memset(pA_Stage2_Ani, 0, sizeof(SAnimation));
	LoadAnimation(pA_Stage2_Ani, "Stage2_Ani.txt");


	Createfont(&KeyWord_1, "MD아트체", 23);
	Createfont(&CharacterName_1, "한컴 쿨재즈 B", 32);
	Createfont(&ChatText_1, "윤고딕340", 15);
	return TRUE;
}


bool UpdateChapter1Data()
{
	GetMousePos(g_hWnd, &CursorPos);

	if(Click==TRUE)
	{
		++ClickCount;
	character = fgetc(TestFile_1);
	fgets(NameText,sizeof(NameText),TestFile_1);
	printf("%s",NameText);
	fgets(tempText1,sizeof(tempText1),TestFile_1);
	printf("%s",tempText1);
	fgets(tempText2,sizeof(tempText2),TestFile_1);
	printf("%s",tempText2);
	}
	if(feof(TestFile_1) != 0)
		fclose(TestFile_1);

	Click=FALSE;
	//CreateNode(아이템코드,x,y);
	return TRUE;
}
bool RenderChapter1Scene()
{
	Put(pS_Chapter_1_BackGround,0,0);
	Put(pS_Inventory_1, 980,0);
	Put(pA_ScriptBox_1, 0,500);
	Put(pA_SteamAni,0,0);


	if(ClickCount >= 4 && ClickCount <= 5)
		Put(pA_SteamCloseUp,0,0);
	if(ClickCount == 8)
		Put(pA_Stage2_Ani,0,0);
	switch(character) //강승훈 왼쪽 k 오른쪽 l , 장민우 왼쪽 n 오른쪽 m, 전소영 왼쪽 s 오른쪽 d , 대호 왼쪽 c 오른쪽 v
	{
		case 'a': //???
			break;
		case 'b': //상황설명문
			break;
		case 'k': //강승훈
			Put(pS_SeongHoon_1,0,213);
			break;
		case 'n':
			Put(pS_Minwoo_1,0,218);
			break;
		case 's':
			Put(pS_Soyeong_1,0,236);
			break;
		case 'c':
			Put(pS_DaeHo_1,0,200);
			break;
			//오른쪽
		case 'l':
			Put(pS_SeongHoon_1,785,213,true);
			break;
		case 'm':
			Put(pS_Minwoo_1,785,218,true);
			break;
		case 'd':
			Put(pS_Soyeong_1,785,236,true);
			break;
		case 'v':
			Put(pS_DaeHo_1,755,200,true);
			break;
	}
	PutText(&CharacterName_1,NameText,60,600, D3DCOLOR_ARGB(255,255,255,110));
	PutText(&ChatText_1, tempText1, 210, 645, D3DCOLOR_ARGB(255,255,255,255));
	PutText(&ChatText_1, tempText2, 210, 680, D3DCOLOR_ARGB(255,255,255,255));

	return TRUE;
}

bool ReleaseChapter1Data()
{
	ReleaseSprite(pS_Chapter_1_BackGround);
	ReleaseTexture(pT_Chapter_1_BackGround);
	ReleaseSprite(pS_Inventory_1);
	ReleaseTexture(pT_Inventory_1);
	ReleaseAni(pA_ScriptBox_1);
	ReleaseAni(pA_SteamAni);
	ReleaseAni(pA_SteamCloseUp);
	ReleaseAni(pA_Stage2_Ani);
	ReleaseTexture(pT_SeongHoon_1);
	ReleaseSprite(pS_SeongHoon_1);
	ReleaseTexture(pT_Minwoo_1);
	ReleaseSprite(pS_Minwoo_1);
	ReleaseTexture(pT_Soyeong_1);
	ReleaseSprite(pS_Soyeong_1);
	ReleaseTexture(pT_DaeHo_1);
	ReleaseSprite(pS_DaeHo_1);
	
	return TRUE;
}