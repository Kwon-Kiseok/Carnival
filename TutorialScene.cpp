#include "TutorialScene.h"
#include "SceneManage.h"
#include "Win.h"
#include "Input.h"
#include "Text.h"
#include "Animation.h"
#include "GameMain.h"

STexture	*pT_TutorialBackGround = NULL;
STexture	*pT_NoChairBackGround = NULL;
STexture	*pT_NoChairNoCoin = NULL;
STexture	*pT_NoCanNoChairNoCoin = NULL;
STexture	*pT_Inventory = NULL;
SAnimation	*pA_ScriptBox = NULL;
SAnimation  *pA_Stage1_Ani = NULL;
SAnimation	*pA_CellPhone_CloseUp = NULL;
SAnimation	*pA_Shake_Screen = NULL;
SAnimation	*pA_Door_CloseUp = NULL;
SAnimation	*pA_Light_CloseUp = NULL;
SAnimation	*pA_Punch_CloseUp = NULL;
STexture	*pT_Item_Coin = NULL;
STexture	*pT_Item_Chair = NULL;
STexture	*pT_Item_Can = NULL;
STexture	*pT_Item_Lotto = NULL;
STexture	*pT_Item_CanLid = NULL;
STexture	*pT_Item_ScratchedLotto = NULL;
STexture	*pT_Tutorial_1 = NULL;
STexture	*pT_Tutorial_2 = NULL;
STexture	*pT_Tutorial_3 = NULL;
STexture	*pT_Tutorial_4 = NULL;
STexture	*pT_Tutorial_5 = NULL;
STexture	*pT_Gain_Chair = NULL;
STexture	*pT_Gain_Coin = NULL;
STexture	*pT_Gain_Lotto = NULL;
STexture	*pT_Gain_Can = NULL;
STexture	*pT_Gain_CanLid = NULL;
STexture	*pT_Gain_ScratchedLotto = NULL;
STexture	*pT_DoorLock = NULL;
STexture	*pT_DoorLock_1 = NULL;
STexture	*pT_DoorLock_2 = NULL;
STexture	*pT_DoorLock_3 = NULL;
STexture	*pT_DoorLock_4 = NULL;
STexture	*pT_Clear_Stage_1 = NULL;
STexture	*pT_SeongHoon = NULL;
STexture	*pT_Minwoo = NULL;
STexture	*pT_Soyeong = NULL;
STexture	*pT_DaeHo = NULL;

SSprite		*pS_TutorialBackGround = NULL;
SSprite		*pS_NoChairBackGround = NULL;
SSprite		*pS_NoChairNoCoin = NULL;
SSprite		*pS_NoCanNoChairNoCoin = NULL;
SSprite		*pS_Inventory = NULL;
SSprite		*pS_Item_Coin = NULL;
SSprite		*pS_Item_Chair = NULL;
SSprite		*pS_Item_Can = NULL;
SSprite		*pS_Item_Lotto = NULL;
SSprite		*pS_Item_CanLid = NULL;
SSprite		*pS_Item_ScratchedLotto = NULL;
SSprite	*pS_Tutorial_1 = NULL;
SSprite	*pS_Tutorial_2 = NULL;
SSprite	*pS_Tutorial_3 = NULL;
SSprite	*pS_Tutorial_4 = NULL;
SSprite	*pS_Tutorial_5 = NULL;
SSprite *pS_Gain_Chair = NULL;
SSprite *pS_Gain_Coin = NULL;
SSprite	*pS_Gain_Lotto = NULL;
SSprite *pS_Gain_Can = NULL;
SSprite *pS_Gain_CanLid = NULL;
SSprite	*pS_Gain_ScratchedLotto = NULL;
SSprite	*pS_DoorLock = NULL;
SSprite	*pS_DoorLock_1 = NULL;
SSprite	*pS_DoorLock_2 = NULL;
SSprite	*pS_DoorLock_3 = NULL;
SSprite	*pS_DoorLock_4 = NULL;
SSprite *pS_Clear_Stage_1 = NULL;
SSprite	*pS_SeongHoon = NULL;
SSprite	*pS_Minwoo = NULL;
SSprite	*pS_Soyeong = NULL;
SSprite	*pS_DaeHo = NULL;

//SAnimation  *pA_EventAnimation = NULL;

extern POINT		CursorPos;
extern bool Click;
SText		CharacterName;
SText		KeyWord;
SText		ChatText;

FILE *TestFile = fopen("Stage1_1.txt", "rt");
FILE *TestFile2 = fopen("Stage1_2.txt", "rt");
FILE *TestFile3 = fopen("Stage1_3.txt", "rt");
FILE *TestFile4 = fopen("Stage1_4.txt", "rt");
FILE *TestFile5 = fopen("Stage1_5.txt", "rt");
FILE *TestFile6 = fopen("Stage1_6.txt", "rt");
CDSHOW		Sound1; //문두들기는 소리
CDSHOW		Sound2; //????????????
CDSHOW		Sound3; //아이템획득소리
CDSHOW		Sound4; //도어락입력소리
CDSHOW		Sound5; //문열리는 소리

CODE_POS Chair_Pos;
CODE_POS Coin_Pos;
CODE_POS Lotto_Pos;
CODE_POS Can_Pos;
CODE_POS CanLid_Pos;
CODE_POS ScratchedLotto_Pos;

int BackGroundTurn =0;
int ClickCount = 0;
int StageTurn = 0;
char tempText1[100];
char tempText2[100];
char NameText[100];
char EffectText[100];
char character;
int Eventnum = 0;
int DoorLockPass = 0;
extern int Chapter;

bool LoadTutorialSceneData()
{
	Chair_Pos.Item_Code = 0;
	//.튜토리얼 배경.
	pT_TutorialBackGround = new STexture;
	memset(pT_TutorialBackGround,0,sizeof(STexture));
	TextureLoad(pT_TutorialBackGround,"TutorialStageBackGround.png",D3DCOLOR_ARGB(255,100,100,243));

	pS_TutorialBackGround = new SSprite;
	memset(pS_TutorialBackGround, 0, sizeof(SSprite));
	CreateSprite(pS_TutorialBackGround, pT_TutorialBackGround, 1080,600);

	//.인벤토리.
	pT_Inventory = new STexture;
	memset(pT_Inventory, 0, sizeof(STexture));
	TextureLoad(pT_Inventory, "Inventory.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Inventory = new SSprite;
	memset(pS_Inventory, 0, sizeof(SSprite));
	CreateSprite(pS_Inventory, pT_Inventory, 300,800);
	
	//승훈
	pT_SeongHoon = new STexture;
	memset(pT_SeongHoon, 0, sizeof(STexture));
	TextureLoad(pT_SeongHoon, "Kangseonghoon.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_SeongHoon = new SSprite;
	memset(pS_SeongHoon, 0, sizeof(SSprite));
	CreateSprite(pS_SeongHoon, pT_SeongHoon, 270, 387);
	
	//.대화상자.
	pA_ScriptBox = new SAnimation;
	memset(pA_ScriptBox, 0, sizeof(SAnimation));
	LoadAnimation(pA_ScriptBox, "ScriptBoxAni.txt");

	//.1막시작 애니메이션.
	pA_Stage1_Ani = new SAnimation;
	memset(pA_Stage1_Ani, 0, sizeof(SAnimation));
	LoadAnimation(pA_Stage1_Ani, "Stage1_Ani.txt");

	//.의자 없는 배경.
	pT_NoChairBackGround = new STexture;
	memset(pT_NoChairBackGround,0,sizeof(STexture));
	TextureLoad(pT_NoChairBackGround, "NoChairBackGround.png", D3DCOLOR_ARGB(255,100,100,243));

	pS_NoChairBackGround = new SSprite;
	memset(pS_NoChairBackGround, 0, sizeof(SSprite));
	CreateSprite(pS_NoChairBackGround, pT_NoChairBackGround, 1080,600);

	

	//.아이템의자.
	pT_Item_Chair = new STexture;
	memset(pT_Item_Chair, 0, sizeof(STexture));
	TextureLoad(pT_Item_Chair, "Chair.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Item_Chair = new SSprite;
	memset(pS_Item_Chair, 0, sizeof(STexture));
	CreateSprite(pS_Item_Chair, pT_Item_Chair, 100, 100);

	//.의자,동전 없는 배경.
	pT_NoChairNoCoin = new STexture;
	memset(pT_NoChairNoCoin, 0, sizeof(STexture));
	TextureLoad(pT_NoChairNoCoin, "NoChairNoCoin.png", D3DCOLOR_ARGB(255,100,100,243));

	pS_NoChairNoCoin = new SSprite;
	memset(pS_NoChairNoCoin, 0, sizeof(SSprite));
	CreateSprite(pS_NoChairNoCoin, pT_NoChairNoCoin, 1080, 600);

	//.의자,동전,캔 없는 배경.
	pT_NoCanNoChairNoCoin = new STexture;
	memset(pT_NoCanNoChairNoCoin, 0, sizeof(STexture));
	TextureLoad(pT_NoCanNoChairNoCoin, "NoCanNoChairNoCoin.png", D3DCOLOR_ARGB(255,100,100,243));

	pS_NoCanNoChairNoCoin = new SSprite;
	memset(pS_NoCanNoChairNoCoin, 0, sizeof(SSprite));
	CreateSprite(pS_NoCanNoChairNoCoin, pT_NoCanNoChairNoCoin, 1080, 600);

	//.아이템코인.
	pT_Item_Coin = new STexture;
	memset(pT_Item_Coin, 0, sizeof(STexture));
	TextureLoad(pT_Item_Coin, "Coin_Tutorial.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Item_Coin = new SSprite;
	memset(pS_Item_Coin, 0, sizeof(SSprite));
	CreateSprite(pS_Item_Coin, pT_Item_Coin, 100,100);

	//.튜토리얼.
	pT_Tutorial_1 = new STexture;
	memset(pT_Tutorial_1, 0, sizeof(STexture));
	TextureLoad(pT_Tutorial_1, "Tutorial_1.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Tutorial_1 = new SSprite;
	memset(pS_Tutorial_1, 0, sizeof(SSprite));
	CreateSprite(pS_Tutorial_1, pT_Tutorial_1, 500, 500);

	pT_Tutorial_2 = new STexture;
	memset(pT_Tutorial_2, 0, sizeof(STexture));
	TextureLoad(pT_Tutorial_2, "Tutorial_2.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Tutorial_2 = new SSprite;
	memset(pS_Tutorial_2, 0, sizeof(SSprite));
	CreateSprite(pS_Tutorial_2, pT_Tutorial_2, 500, 500);

	pT_Tutorial_3 = new STexture;
	memset(pT_Tutorial_3, 0, sizeof(STexture));
	TextureLoad(pT_Tutorial_3, "Tutorial_3.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Tutorial_3 = new SSprite;
	memset(pS_Tutorial_3, 0, sizeof(SSprite));
	CreateSprite(pS_Tutorial_3, pT_Tutorial_3, 500, 500);

	pT_Tutorial_4 = new STexture;
	memset(pT_Tutorial_4, 0, sizeof(STexture));
	TextureLoad(pT_Tutorial_4, "Tutorial_4.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Tutorial_4 = new SSprite;
	memset(pS_Tutorial_4, 0, sizeof(SSprite));
	CreateSprite(pS_Tutorial_4, pT_Tutorial_4, 500, 500);

	pT_Tutorial_5 = new STexture;
	memset(pT_Tutorial_5, 0, sizeof(STexture));
	TextureLoad(pT_Tutorial_5, "Tutorial_5.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Tutorial_5 = new SSprite;
	memset(pS_Tutorial_5, 0, sizeof(SSprite));
	CreateSprite(pS_Tutorial_5, pT_Tutorial_5, 500, 500);

	pT_Gain_Chair = new STexture;
	memset(pT_Gain_Chair, 0, sizeof(STexture));
	TextureLoad(pT_Gain_Chair, "Gain_Chair.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Gain_Chair = new SSprite;
	memset(pS_Gain_Chair, 0, sizeof(SSprite));
	CreateSprite(pS_Gain_Chair, pT_Gain_Chair, 1080, 600);

	pT_Gain_Coin = new STexture;
	memset(pT_Gain_Coin, 0, sizeof(STexture));
	TextureLoad(pT_Gain_Coin, "Gain_Coin.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Gain_Coin = new SSprite;
	memset(pS_Gain_Coin, 0, sizeof(SSprite));
	CreateSprite(pS_Gain_Coin, pT_Gain_Coin, 1080, 600);

	pT_Gain_Lotto = new STexture;
	memset(pT_Gain_Lotto, 0, sizeof(STexture));
	TextureLoad(pT_Gain_Lotto, "Gain_Lotto1.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Gain_Lotto = new SSprite;
	memset(pS_Gain_Lotto, 0, sizeof(SSprite));
	CreateSprite(pS_Gain_Lotto, pT_Gain_Lotto, 1080, 600);

	pT_Gain_Can = new STexture;
	memset(pT_Gain_Can, 0, sizeof(STexture));
	TextureLoad(pT_Gain_Can, "Gain_Can.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Gain_Can = new SSprite;
	memset(pS_Gain_Can, 0, sizeof(SSprite));
	CreateSprite(pS_Gain_Can, pT_Gain_Can, 1080, 600);

	pT_Gain_CanLid = new STexture;
	memset(pT_Gain_CanLid, 0, sizeof(STexture));
	TextureLoad(pT_Gain_CanLid, "Gain_CanLid.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Gain_CanLid = new SSprite;
	memset(pS_Gain_CanLid, 0, sizeof(SSprite));
	CreateSprite(pS_Gain_CanLid, pT_Gain_CanLid, 1080, 600);

	pT_Gain_ScratchedLotto = new STexture;
	memset(pT_Gain_ScratchedLotto, 0, sizeof(STexture));
	TextureLoad(pT_Gain_ScratchedLotto, "Gain_Lotto2.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Gain_ScratchedLotto = new SSprite;
	memset(pS_Gain_ScratchedLotto, 0, sizeof(SSprite));
	CreateSprite(pS_Gain_ScratchedLotto, pT_Gain_ScratchedLotto, 1080, 600);

	pT_DoorLock = new STexture;
	memset(pT_DoorLock, 0, sizeof(STexture));
	TextureLoad(pT_DoorLock, "DoorLock.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_DoorLock = new SSprite;
	memset(pS_DoorLock, 0, sizeof(SSprite));
	CreateSprite(pS_DoorLock, pT_DoorLock, 500, 500);

	pT_DoorLock_1 = new STexture;
	memset(pT_DoorLock_1, 0, sizeof(STexture));
	TextureLoad(pT_DoorLock_1, "DoorLock_1.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_DoorLock_1 = new SSprite;
	memset(pS_DoorLock_1, 0, sizeof(SSprite));
	CreateSprite(pS_DoorLock_1, pT_DoorLock_1, 500, 500);

	pT_DoorLock_2 = new STexture;
	memset(pT_DoorLock_2, 0, sizeof(STexture));
	TextureLoad(pT_DoorLock_2, "DoorLock_2.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_DoorLock_2 = new SSprite;
	memset(pS_DoorLock_2, 0, sizeof(SSprite));
	CreateSprite(pS_DoorLock_2, pT_DoorLock_2, 500, 500);

	pT_DoorLock_3 = new STexture;
	memset(pT_DoorLock_3, 0, sizeof(STexture));
	TextureLoad(pT_DoorLock_3, "DoorLock_3.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_DoorLock_3 = new SSprite;
	memset(pS_DoorLock_3, 0, sizeof(SSprite));
	CreateSprite(pS_DoorLock_3, pT_DoorLock_3, 500, 500);

	pT_DoorLock_4 = new STexture;
	memset(pT_DoorLock_4, 0, sizeof(STexture));
	TextureLoad(pT_DoorLock_4, "DoorLock_4.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_DoorLock_4 = new SSprite;
	memset(pS_DoorLock_4, 0, sizeof(SSprite));
	CreateSprite(pS_DoorLock_4, pT_DoorLock_4, 500, 500);

	pT_Clear_Stage_1 = new STexture;
	memset(pT_Clear_Stage_1, 0, sizeof(STexture));
	TextureLoad(pT_Clear_Stage_1, "ClearStage_1.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Clear_Stage_1 = new SSprite;
	memset(pS_Clear_Stage_1, 0, sizeof(SSprite));
	CreateSprite(pS_Clear_Stage_1, pT_Clear_Stage_1, 1080, 600);
	
	//.아이템 캔.
	pT_Item_Can = new STexture;
	memset(pT_Item_Can, 0, sizeof(STexture));
	TextureLoad(pT_Item_Can, "Can.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Item_Can = new SSprite;
	memset(pS_Item_Can, 0, sizeof(SSprite));
	CreateSprite(pS_Item_Can, pT_Item_Can, 100,100);

	//.아이템 복권.
	pT_Item_Lotto = new STexture;
	memset(pT_Item_Lotto, 0, sizeof(STexture));
	TextureLoad(pT_Item_Lotto, "Lotto.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Item_Lotto = new SSprite;
	memset(pS_Item_Lotto, 0, sizeof(SSprite));
	CreateSprite(pS_Item_Lotto, pT_Item_Lotto, 100, 100);

	//.아이템 복권2.
	pT_Item_ScratchedLotto = new STexture;
	memset(pT_Item_ScratchedLotto, 0, sizeof(STexture));
	TextureLoad(pT_Item_ScratchedLotto, "Lotto2.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Item_ScratchedLotto = new SSprite;
	memset(pS_Item_ScratchedLotto, 0, sizeof(SSprite));
	CreateSprite(pS_Item_ScratchedLotto, pT_Item_ScratchedLotto, 100, 100);

	//.아이템 캔뚜껑.
	pT_Item_CanLid = new STexture;
	memset(pT_Item_CanLid, 0, sizeof(STexture));
	TextureLoad(pT_Item_CanLid, "CanLid.png", D3DCOLOR_ARGB(255,255,0,255));

	pS_Item_CanLid = new SSprite;
	memset(pS_Item_CanLid, 0, sizeof(SSprite));
	CreateSprite(pS_Item_CanLid, pT_Item_CanLid, 100, 100);

	
	//민우
	pT_Minwoo = new STexture;
	memset(pT_Minwoo, 0, sizeof(STexture));
	TextureLoad(pT_Minwoo, "Jangminwoo.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Minwoo = new SSprite;
	memset(pS_Minwoo, 0, sizeof(SSprite));
	CreateSprite(pS_Minwoo, pT_Minwoo, 250, 382);
	//소영
	pT_Soyeong = new STexture;
	memset(pT_Soyeong, 0, sizeof(STexture));
	TextureLoad(pT_Soyeong, "Jeonsoyeong.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_Soyeong = new SSprite;
	memset(pS_Soyeong, 0, sizeof(SSprite));
	CreateSprite(pS_Soyeong, pT_Soyeong, 270, 364);
	//대호
	pT_DaeHo = new STexture;
	memset(pT_DaeHo, 0, sizeof(STexture));
	TextureLoad(pT_DaeHo, "Choidaeho.png", D3DCOLOR_ARGB(100,255,0,255));

	pS_DaeHo = new SSprite;
	memset(pS_DaeHo, 0, sizeof(SSprite));
	CreateSprite(pS_DaeHo, pT_DaeHo, 351, 400);
	
	//.화면 흔들림.
	pA_Shake_Screen = new SAnimation;
	memset(pA_Shake_Screen, 0, sizeof(SAnimation));
	LoadAnimation(pA_Shake_Screen, "Shake_Screen.txt");

	//.핸드폰 클로즈업.
	pA_CellPhone_CloseUp = new SAnimation;
	memset(pA_CellPhone_CloseUp, 0, sizeof(SAnimation));
	LoadAnimation(pA_CellPhone_CloseUp, "CellPhone_CloseUp.txt");

	//.문 클로즈업.
	pA_Door_CloseUp = new SAnimation;
	memset(pA_Door_CloseUp, 0, sizeof(SAnimation));
	LoadAnimation(pA_Door_CloseUp, "Door_CloseUp.txt");

	//.펀치머신 클로즈업.
	pA_Punch_CloseUp = new SAnimation;
	memset(pA_Punch_CloseUp, 0, sizeof(SAnimation));
	LoadAnimation(pA_Punch_CloseUp, "Punch_CloseUp.txt");

	//.전등 클로즈업.
	pA_Light_CloseUp = new SAnimation;
	memset(pA_Light_CloseUp, 0, sizeof(SAnimation));
	LoadAnimation(pA_Light_CloseUp, "Light_CloseUp.txt");

	Createfont(&KeyWord, "MD아트체", 23);
	Createfont(&CharacterName, "한컴 쿨재즈 B", 32);
	Createfont(&ChatText, "윤고딕340", 15);

	//.효과음.
	Sound1.OpenFile("K001-1_door.wav");
	Sound2.OpenFile("K001-2.wav");
	Sound3.OpenFile("GainItem.wav");
	Sound4.OpenFile("K001-3.wav");
	Sound5.OpenFile("K001-4.wav");
	return TRUE;

}


bool UpdateTutorialScene()
{
	GetMousePos(g_hWnd, &CursorPos);
	ITEM_INFO Door; ITEM_INFO Light;ITEM_INFO Chair;ITEM_INFO Punch;ITEM_INFO Can;

	Door.top = 250;Door.bottom = 345;Door.left = 315;Door.right = 380;
	Light.top = 175;Light.bottom = 209;Light.left = 250; Light.right = 318;
	Chair.top = 280;Chair.bottom = 380;Chair.left = 190; Chair.right = 250;
	Punch.top = 368;Punch.bottom = 575;Punch.left = 698; Punch.right = 860;
	Can.top = 460; Can.bottom = 506; Can.left = 177; Can.right = 255;

	Chair_Pos.x = 1160; Chair_Pos.y = 50;
	Coin_Pos.x = 1160; Coin_Pos.y = 50;
	Lotto_Pos.x = 1160; Lotto_Pos.y = 50;
	Can_Pos.x = 1160; Can_Pos.y = 200;
	CanLid_Pos.x = 1160; CanLid_Pos.y = 200;
	ScratchedLotto_Pos.x = 1160; ScratchedLotto_Pos.y = 50;

	if(TestFile==NULL)
		printf("파일오픈실패");

	if(Click==TRUE && (BackGroundTurn == 0 || BackGroundTurn == 4))
	{
		ClickCount++;
		character = fgetc(TestFile);
		fgets(NameText,sizeof(NameText),TestFile);
		printf("%s",NameText);
		fgets(tempText1,sizeof(tempText1),TestFile);
		printf("%s",tempText1);
		fgets(tempText2,sizeof(tempText2),TestFile);
		printf("%s",tempText2);
		if(ClickCount == 10) //.효과음.
		{
			BackGroundTurn = 4;
			Sound1.Play(true);
		}
		Click = FALSE;
	}
	if(feof(TestFile) != 0)
	{	
		ClickCount = 0;
		BackGroundTurn = 1;
		fclose(TestFile);
	}
	if(Click==TRUE && BackGroundTurn != 0 && StageTurn == 0) 
	{
		ClickCount++;
		BackGroundTurn = 2;
		character = fgetc(TestFile2);
		fgets(NameText,sizeof(NameText),TestFile2);
		printf("%s",NameText);
		fgets(tempText1,sizeof(tempText1),TestFile2);
		printf("%s",tempText1);
		fgets(tempText2,sizeof(tempText2),TestFile2);
		printf("%s",tempText2);
		if(ClickCount == 5) //.핸드폰 클로즈업.
			BackGroundTurn = 3;
		else if(ClickCount == 13)
			Sound2.Play(true);
		else if(ClickCount >= 19)
		{
			StageTurn = 1;
			ClickCount = 0;
		}
		Click = FALSE;
	}
	if(Click==TRUE && StageTurn == 1)
	{
		ClickCount++;
		Click=FALSE;
	}
	if(feof(TestFile2) != 0)
	{	
		fclose(TestFile2);
	}

	switch(StageTurn)
	{
	case 2:
		if(Click==TRUE)
		{
			if(ClickCount==0)
			{
				BackGroundTurn = 2;
				character = fgetc(TestFile3);
				fgets(NameText,sizeof(NameText),TestFile3);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile3);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile3);
				printf("%s",tempText2);
			}

			if(ClickCount==1)
			{
				if((CursorPos.x >= Door.left && CursorPos.x <= Door.right) && (CursorPos.y>=Door.top && CursorPos.y<=Door.bottom))
				{
					BackGroundTurn=5;
					character = fgetc(TestFile3);
					fgets(NameText,sizeof(NameText),TestFile3);
					printf("%s",NameText);
					fgets(tempText1,sizeof(tempText1),TestFile3);
					printf("%s",tempText1);
					fgets(tempText2,sizeof(tempText2),TestFile3);
					printf("%s",tempText2);
				}
				else 
					ClickCount--;
			}
			if(ClickCount==2)
			{
				character = fgetc(TestFile3);
				fgets(NameText,sizeof(NameText),TestFile3);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile3);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile3);
				printf("%s",tempText2);
			}
			if(ClickCount==3)
			{
				if((CursorPos.x >= Light.left && CursorPos.x <= Light.right) && (CursorPos.y>=Light.top && CursorPos.y<=Light.bottom))
				{
					BackGroundTurn=6;
					character = fgetc(TestFile3);
					fgets(NameText,sizeof(NameText),TestFile3);
					printf("%s",NameText);
					fgets(tempText1,sizeof(tempText1),TestFile3);
					printf("%s",tempText1);
					fgets(tempText2,sizeof(tempText2),TestFile3);
					printf("%s",tempText2);
				}
				else 
					ClickCount--;
			}
			if(ClickCount>=4 && ClickCount<=9)
			{
				BackGroundTurn=2;
				character = fgetc(TestFile3);
				fgets(NameText,sizeof(NameText),TestFile3);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile3);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile3);
				printf("%s",tempText2);
			}
			if(ClickCount==10)
			{
				if((CursorPos.x >= Chair.left && CursorPos.x <= Chair.right) && (CursorPos.y>=Chair.top && CursorPos.y<=Chair.bottom))
				{
					BackGroundTurn=7;
					character = fgetc(TestFile3);
					fgets(NameText,sizeof(NameText),TestFile3);
					printf("%s",NameText);
					fgets(tempText1,sizeof(tempText1),TestFile3);
					printf("%s",tempText1);
					fgets(tempText2,sizeof(tempText2),TestFile3);
					printf("%s",tempText2);
				}
				else
					ClickCount--;
			}
			if(ClickCount==11)
			{
				Sound3.Play(true);
				character = fgetc(TestFile3);
				fgets(NameText,sizeof(NameText),TestFile3);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile3);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile3);
				printf("%s",tempText2);
				Chair_Pos.Item_Code=1;
			}
			ClickCount++;
			if(ClickCount == 13)
			{
				character = fgetc(TestFile3);
				fgets(NameText,sizeof(NameText),TestFile3);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile3);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile3);
				printf("%s",tempText2);
				ClickCount=4;
				StageTurn=1;
				fclose(TestFile3);
			}

			Click=FALSE;
		}
		break;
	case 3:
		if(Click==TRUE)
		{
			if(Eventnum==0 && Chair_Pos.Item_Code==1 && (CursorPos.x >= Chair_Pos.x && CursorPos.x <= Chair_Pos.x+100) && (CursorPos.y>=Chair_Pos.y && CursorPos.y<=Chair_Pos.y+100))
			{
				character = fgetc(TestFile4);
				fgets(NameText,sizeof(NameText),TestFile4);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile4);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile4);
				printf("%s",tempText2);
				Eventnum = 1;
			}
			if(Eventnum==1 && Chair_Pos.Item_Code==1 && (CursorPos.x >= Light.left && CursorPos.x <= Light.right) && (CursorPos.y>=Light.top && CursorPos.y<=Light.bottom))
			{
				Chair_Pos.Item_Code=0;
				character = fgetc(TestFile4);
				fgets(NameText,sizeof(NameText),TestFile4);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile4);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile4);
				printf("%s",tempText2);
			}
			if(Eventnum==1 && Chair_Pos.Item_Code==0 && StageTurn==3)
			{
				ClickCount++;
				character = fgetc(TestFile4);
				fgets(NameText,sizeof(NameText),TestFile4);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile4);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile4);
				printf("%s",tempText2);
			}
			if(ClickCount==12 && Eventnum==1)
			{
				Sound3.Loop();
				BackGroundTurn = 8;
				Coin_Pos.Item_Code=1;
				character = fgetc(TestFile4);
				fgets(NameText,sizeof(NameText),TestFile4);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile4);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile4);
				printf("%s",tempText2);
				fclose(TestFile4);
				Eventnum = 0;
			}
			else if(ClickCount == 12 && Eventnum == 0)
			{
				ClickCount=13;
			}
			if(ClickCount==13 && Eventnum==0)
			{
				StageTurn=4;
				ClickCount=0;
			}
			Click=FALSE;
		}
		break;
	case 4:
		if(Click == TRUE)
		{
			if(Eventnum==0 && ClickCount==0 && (CursorPos.x>= Punch.left && CursorPos.x <= Punch.right) && (CursorPos.y >= Punch.top && CursorPos.y <= Punch.bottom))
			{
				ClickCount=1;
				BackGroundTurn=9;
				character = fgetc(TestFile5);
				fgets(NameText,sizeof(NameText),TestFile5);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile5);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile5);
				printf("%s",tempText2);
			}
			if(Eventnum==0 && ClickCount >= 1 && ClickCount <= 7 && StageTurn==4)
			{
				BackGroundTurn=8;
				ClickCount++;
				character = fgetc(TestFile5);
				fgets(NameText,sizeof(NameText),TestFile5);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile5);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile5);
				printf("%s",tempText2);
			}
			if(ClickCount==8 && Eventnum==0 && Coin_Pos.Item_Code==1 && (CursorPos.x >= Coin_Pos.x && CursorPos.x <= Coin_Pos.x+100) && (CursorPos.y>=Coin_Pos.y && CursorPos.y<=Coin_Pos.y+100))
			{
				ClickCount=0;
				Eventnum = 1;
			}
			if(ClickCount == 0 && Eventnum==1 && Coin_Pos.Item_Code==1 &&  (CursorPos.x>= Punch.left && CursorPos.x <= Punch.right) && (CursorPos.y >= Punch.top && CursorPos.y <= Punch.bottom))
			{
				ClickCount=1;
				character = fgetc(TestFile5);
				fgets(NameText,sizeof(NameText),TestFile5);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile5);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile5);
				printf("%s",tempText2);
			}
			if(Eventnum==1 && Coin_Pos.Item_Code==1 && ClickCount>=1 && ClickCount <= 9)
			{
				ClickCount++;
				character = fgetc(TestFile5);
				fgets(NameText,sizeof(NameText),TestFile5);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile5);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile5);
				printf("%s",tempText2);
			}
			if(ClickCount >= 15 && ClickCount <= 21 && Coin_Pos.Item_Code==0)
			{
				ClickCount++;
				Eventnum=1;
				Lotto_Pos.Item_Code=1;
				character = fgetc(TestFile5);
				fgets(NameText,sizeof(NameText),TestFile5);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile5);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile5);
				printf("%s",tempText2);
				if(ClickCount==21)
					Sound3.Loop();
			}
			if(ClickCount >= 11 && ClickCount <= 14 && (Eventnum==0 && Coin_Pos.Item_Code==0))
			{
				ClickCount++;
				character = fgetc(TestFile5);
				fgets(NameText,sizeof(NameText),TestFile5);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile5);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile5);
				printf("%s",tempText2);
			}
			if(ClickCount == 10 && Eventnum==1 && Coin_Pos.Item_Code==1)
			{
				Eventnum=0;
				ClickCount++;
				Coin_Pos.Item_Code=0;
			}



			if(ClickCount==22 && (CursorPos.x >= Lotto_Pos.x && CursorPos.x <= Lotto_Pos.x+100 && CursorPos.y >= Lotto_Pos.y && CursorPos.y <= Lotto_Pos.y+100))
			{
				ClickCount++;
			}
			if(Eventnum==1 && Lotto_Pos.Item_Code==1 && ClickCount >= 23)
			{
				character = fgetc(TestFile5);
				fgets(NameText,sizeof(NameText),TestFile5);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile5);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile5);
				printf("%s",tempText2);
			}
			if(feof(TestFile5) != 0)
			{
				Eventnum = 0;
				ClickCount = 0;
				fclose(TestFile5);
				StageTurn=5;
			}
		}Click=FALSE;
		break;
	case 5:
		if(Click==TRUE)
		{
			//캔 분해
			if(CanLid_Pos.Item_Code == 0 && ClickCount==3 && Can_Pos.Item_Code==1 && (CursorPos.x >= 1115 && CursorPos.x <= 1145) && (CursorPos.y >= 235 && CursorPos.y <= 265))
			{
				Sound3.Loop();
				Can_Pos.Item_Code=0;
				CanLid_Pos.Item_Code=1;
				BackGroundTurn = 10;
			}
			else if(CanLid_Pos.Item_Code==1 && ClickCount==3)
				ClickCount=4;
			if(ClickCount==4 && CanLid_Pos.Item_Code==1 && Eventnum==0)
			{
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
				StageTurn=1;
				ClickCount=8;
				Eventnum=1;
			}
			//조합 문제는 1번 버튼을 누르고 다른 곳을 누른 후에 2번 버튼을 눌러도 조합이 됨 ㅁㄴㅇㄹ
			if(Eventnum!=4 &&ClickCount==4 && CanLid_Pos.Item_Code==1 && Eventnum==1 && ((CursorPos.x >= 1115 && CursorPos.x <= 1145) && (CursorPos.y >= 50 && CursorPos.y <= 80)))
			{
				Eventnum=2;
			}
			else if(Eventnum!=4 &&ClickCount==4 && CanLid_Pos.Item_Code==1 && Eventnum==1 && ((CursorPos.x >= 1115 && CursorPos.x <= 1145) && (CursorPos.y >= 200 && CursorPos.y <= 230)))
			{
				Eventnum=3;
			}
			if(Eventnum!=4 && ClickCount==4 && CanLid_Pos.Item_Code==1 && Eventnum==2 && ((CursorPos.x >= 1115 && CursorPos.x <= 1145) && (CursorPos.y >= 200 && CursorPos.y <= 230)))
			{
				Eventnum=4;
			}
			else if(Eventnum!=4 &&ClickCount==4 && CanLid_Pos.Item_Code==1 && Eventnum==3 && ((CursorPos.x >= 1115 && CursorPos.x <= 1145) && (CursorPos.y >= 50 && CursorPos.y <= 80)))
			{
				Eventnum=4;
			}
			if(Eventnum == 6)
			{
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
			}
			if(feof(TestFile6) != 0)
			{
				Eventnum = 7;
				fclose(TestFile6);
			}
			if(Eventnum==7 && (CursorPos.x >= Door.left && CursorPos.x <= Door.right) && (CursorPos.y >= Door.top && CursorPos.y <= Door.bottom))
			{
				ReleaseScene(Chapter);
				Chapter = 2;
				LoadScene(Chapter);
			}
			//.도어락.
			if(DoorLockPass == 0 && Eventnum == 5 && ScratchedLotto_Pos.Item_Code == 1 && (CursorPos.x >= Door.left && CursorPos.x <= Door.right) && (CursorPos.y >= Door.top && CursorPos.y <= Door.bottom))
			{
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
				BackGroundTurn=11;
			}
			switch(DoorLockPass)
			{
			case 0:
				if((CursorPos.x >= 521 && CursorPos.x <= 564) && (CursorPos.y >= 290 && CursorPos.y <= 332))
				{	
					Sound4.Play(true);
					DoorLockPass = 1;
					BackGroundTurn=12;
				}
				else 
					DoorLockPass==0;
				break;
			case 1:
				if((CursorPos.x >= 603 && CursorPos.x <= 645) && (CursorPos.y >= 289 && CursorPos.y <= 332))
				{
					Sound4.Loop();
					DoorLockPass = 2;
					BackGroundTurn=13;
				}
				else 
				{
					DoorLockPass--;
					BackGroundTurn--;
				}
				break;
			case 2:
				if((CursorPos.x >= 603 && CursorPos.x <= 645) && (CursorPos.y >= 289 && CursorPos.y <= 332))
				{
					Sound4.Loop();
					DoorLockPass = 3;
					BackGroundTurn=14;
				}
				else 
				{
					DoorLockPass--;
					BackGroundTurn--;
				}
				break;
			case 3:
				if((CursorPos.x >= 521 && CursorPos.x <= 564) && (CursorPos.y >= 351 && CursorPos.y <= 392))
				{
					Sound4.Loop();
					DoorLockPass = 4;
					BackGroundTurn=15;
				}
				else 
				{
					DoorLockPass--;
					BackGroundTurn--;
				}
				break;
			case 4:
				BackGroundTurn=16;
				Sound5.Play(true);
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
				Eventnum = 6;
				DoorLockPass=5;
				break;
			}
			if(Eventnum == 4 && ScratchedLotto_Pos.Item_Code==0)
			{
				Sound3.Loop();
				CanLid_Pos.Item_Code=0;
				Lotto_Pos.Item_Code=0;
				ScratchedLotto_Pos.Item_Code=1;
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
			}
			else if(Eventnum == 4 && ScratchedLotto_Pos.Item_Code==1)
			{	
				ClickCount = 0;
				Eventnum = 5;
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
			}
			if(ClickCount==2 && Can_Pos.Item_Code==1)
			{
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
				StageTurn=1;
				ClickCount=6;
			}
			if(ClickCount==1 && Eventnum==0 && Can_Pos.Item_Code==0)
			{
				ClickCount++;
				Can_Pos.Item_Code=1;
				Sound3.Loop();
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
			}
			if(Eventnum != 5 && ClickCount==0 && (CursorPos.x >= Can.left && CursorPos.x <= Can.right) && (CursorPos.y >= Can.top && CursorPos.y <= Can.bottom))
			{
				character = fgetc(TestFile6);
				fgets(NameText,sizeof(NameText),TestFile6);
				printf("%s",NameText);
				fgets(tempText1,sizeof(tempText1),TestFile6);
				printf("%s",tempText1);
				fgets(tempText2,sizeof(tempText2),TestFile6);
				printf("%s",tempText2);
				ClickCount=1;
			}

		}Click=FALSE;
		break;
		Click=FALSE;
	}

	return TRUE;
}

bool RenderTutorialScene()
{
		Put(pS_Inventory, 980,0);
	if(Chair_Pos.Item_Code == 1)
		Put(pS_Item_Chair, Chair_Pos.x,Chair_Pos.y);
	if(Coin_Pos.Item_Code == 1)
		Put(pS_Item_Coin, Coin_Pos.x, Coin_Pos.y);
	if(Lotto_Pos.Item_Code == 1)
		Put(pS_Item_Lotto, Lotto_Pos.x, Lotto_Pos.y);
	if(Can_Pos.Item_Code == 1)
		Put(pS_Item_Can, Can_Pos.x, Can_Pos.y);
	if(CanLid_Pos.Item_Code == 1)
		Put(pS_Item_CanLid, CanLid_Pos.x, CanLid_Pos.y);
	if(ScratchedLotto_Pos.Item_Code == 1)
		Put(pS_Item_ScratchedLotto, ScratchedLotto_Pos.x, ScratchedLotto_Pos.y);
	switch(BackGroundTurn)
	{
	case 0:
		Put(pS_TutorialBackGround,0,0);
		break;
	case 1:
		Put(pA_Stage1_Ani,0,0);
		break;	
	case 2:
		Put(pS_TutorialBackGround,0,0);
		break;
	case 3:
		Put(pS_TutorialBackGround,0,0);
		Put(pA_CellPhone_CloseUp,0,0);
		break;
	case 4:
		Put(pA_Shake_Screen,0,0);
		break;
	case 5:
		Put(pS_TutorialBackGround,0,0);
		Put(pA_Door_CloseUp,0,0);
		break;
	case 6:
		Put(pS_TutorialBackGround,0,0);
		Put(pA_Light_CloseUp,0,0);
		break;
	case 7:
		Put(pS_NoChairBackGround,0,0);
		break;
	case 8:
		Put(pS_NoChairNoCoin, 0, 0);
		break;
	case 9:
		Put(pS_NoChairNoCoin, 0, 0);
		Put(pA_Punch_CloseUp,0,0);
		break;
	case 10:
		Put(pS_NoCanNoChairNoCoin,0,0);
		break;
	case 11:
		Put(pS_NoCanNoChairNoCoin,0,0);
		Put(pS_DoorLock,290,50);
		break;
	case 12:
		Put(pS_NoCanNoChairNoCoin,0,0);
		Put(pS_DoorLock_1,290,50);
		break;
	case 13:
		Put(pS_NoCanNoChairNoCoin,0,0);
		Put(pS_DoorLock_2,290,50);
		break;
	case 14:
		Put(pS_NoCanNoChairNoCoin,0,0);
		Put(pS_DoorLock_3,290,50);
		break;
	case 15:
		Put(pS_NoCanNoChairNoCoin,0,0);
		Put(pS_DoorLock_4,290,50);
		break;
	case 16:
		Put(pS_Clear_Stage_1,0,0);
		break;
	}
	switch(character)
	{
		case 'a': //???
			break;
		case 'b': //상황설명문
			break;
		case 'k': //강승훈
			Put(pS_SeongHoon,0,213);
			break;
		case 'm':
			Put(pS_Minwoo,0,218);
			break;
		case 's':
			Put(pS_Soyeong,0,236);
			break;
		case 'c':
			Put(pS_DaeHo,0,200);
			break;
	}
	
	if(StageTurn == 1) //.튜토리얼.
	{
		switch(ClickCount)
		{
		case 1:
			Put(pS_Tutorial_1, 290, 50);
			break;
		case 2:
			Put(pS_Tutorial_2, 290, 50);
			break;
		case 3:
			ClickCount = 0; StageTurn = 2;
			break;
		case 4:
			Put(pS_Tutorial_4,290,50);
			break;
		case 5:
			StageTurn=3;
			ClickCount=0;
			break;
		case 6:
			Put(pS_Tutorial_3,290,50);
			break;
		case 7:
			StageTurn=5;
			ClickCount=3;
			break;
		case 8:
			Put(pS_Tutorial_5,290,50);
			break;
		case 9:
			StageTurn=5;
			ClickCount=4;
			break;
		}
	}
	if(StageTurn == 2)
	{
		switch(ClickCount)
		{
		case 12:
			Put(pS_Gain_Chair, 0, 0);
			break;
		}
	}
	if(StageTurn == 3)
	{
		switch(ClickCount)
		{
		case 12:
			Put(pS_Gain_Coin, 0,0);
			break;
		}
	}
	if(StageTurn == 4)
	{
		switch(ClickCount)
		{
		case 21:
			Put(pS_Gain_Lotto, 0, 0);
			break;
		}
	}
	if(StageTurn == 5)
	{
		switch(ClickCount)
		{
		case 2:
			Put(pS_Gain_Can, 0, 0);
			break;
		case 3:
			if(CanLid_Pos.Item_Code==1)
			{
				Put(pS_Gain_CanLid, 0, 0);		
			}
			break;
		case 4:
			if(Eventnum==4)
			{
				Put(pS_Gain_ScratchedLotto,0,0);
			}
			break;
		}
	}
	Put(pA_ScriptBox, 0,500);
	PutText(&CharacterName,NameText,60,600, D3DCOLOR_ARGB(255,255,255,110));
	PutText(&ChatText, tempText1, 210, 645, D3DCOLOR_ARGB(255,255,255,255));
	PutText(&ChatText, tempText2, 210, 680, D3DCOLOR_ARGB(255,255,255,255));

	
	return TRUE;
}

bool ReleaseTutorialScene()
{
	ReleaseTexture(pT_SeongHoon);
	ReleaseSprite(pS_SeongHoon);
	ReleaseTexture(pT_Minwoo);
	ReleaseSprite(pS_Minwoo);
	ReleaseTexture(pT_Soyeong);
	ReleaseSprite(pS_Soyeong);
	ReleaseTexture(pT_DaeHo);
	ReleaseSprite(pS_DaeHo);
	ReleaseSprite(pS_TutorialBackGround);
	ReleaseTexture(pT_TutorialBackGround);
	ReleaseSprite(pS_NoChairBackGround);
	ReleaseTexture(pT_NoChairBackGround);
	ReleaseTexture(pT_NoCanNoChairNoCoin);
	ReleaseSprite(pS_NoCanNoChairNoCoin);
	ReleaseTexture(pT_NoChairNoCoin);
	ReleaseSprite(pS_NoChairNoCoin);
	ReleaseAni(pA_ScriptBox);
	ReleaseAni(pA_Stage1_Ani);
	ReleaseAni(pA_CellPhone_CloseUp);
	ReleaseAni(pA_Shake_Screen);
	ReleaseAni(pA_Door_CloseUp);
	ReleaseAni(pA_Light_CloseUp);
	ReleaseAni(pA_Punch_CloseUp);
	ReleaseSprite(pS_Inventory);
	ReleaseTexture(pT_Inventory);
	ReleaseSprite(pS_Item_Coin);
	ReleaseTexture(pT_Item_Coin);
	ReleaseSprite(pS_Item_Chair);
	ReleaseTexture(pT_Item_Chair);
	ReleaseTexture(pT_Item_Can);
	ReleaseSprite(pS_Item_Can);
	ReleaseTexture(pT_Item_CanLid);
	ReleaseSprite(pS_Item_CanLid);
	ReleaseTexture(pT_Item_Lotto);
	ReleaseSprite(pS_Item_Lotto);
	ReleaseTexture(pT_Tutorial_1);
	ReleaseTexture(pT_Tutorial_2);
	ReleaseTexture(pT_Tutorial_3);
	ReleaseTexture(pT_Tutorial_4);
	ReleaseTexture(pT_Tutorial_5);
	ReleaseSprite(pS_Tutorial_1);
	ReleaseSprite(pS_Tutorial_2);
	ReleaseSprite(pS_Tutorial_3);
	ReleaseSprite(pS_Tutorial_4);
	ReleaseSprite(pS_Tutorial_5);
	ReleaseTexture(pT_Gain_Chair);
	ReleaseSprite(pS_Gain_Chair);
	ReleaseTexture(pT_Gain_Coin);
	ReleaseSprite(pS_Gain_Coin);
	ReleaseTexture(pT_Gain_Lotto);
	ReleaseSprite(pS_Gain_Lotto);
	ReleaseTexture(pT_Gain_Can);
	ReleaseSprite(pS_Gain_Can);
	ReleaseTexture(pT_Gain_CanLid);
	ReleaseSprite(pS_Gain_CanLid);
	ReleaseTexture(pT_Item_ScratchedLotto);
	ReleaseSprite(pS_Item_ScratchedLotto);
	ReleaseTexture(pT_Gain_ScratchedLotto);
	ReleaseSprite(pS_Gain_ScratchedLotto);
	ReleaseTexture(pT_DoorLock);
	ReleaseSprite(pS_DoorLock);
	ReleaseTexture(pT_DoorLock_1);
	ReleaseSprite(pS_DoorLock_1);
	ReleaseTexture(pT_DoorLock_2);
	ReleaseSprite(pS_DoorLock_2);
	ReleaseTexture(pT_DoorLock_3);
	ReleaseSprite(pS_DoorLock_3);
	ReleaseTexture(pT_DoorLock_4);
	ReleaseSprite(pS_DoorLock_4);
	ReleaseSprite(pS_Clear_Stage_1);
	ReleaseTexture(pT_Clear_Stage_1);
	Sound1.CloseFile();
	Sound2.CloseFile();
	Sound3.CloseFile();
	Sound4.CloseFile();
	Sound5.CloseFile();
	//ReleaseAni(pA_EventAnimation);
	return TRUE;
}
