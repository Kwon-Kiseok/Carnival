#include "MenuScene.h"
#include "Win.h"
#include "Input.h"
#include "Text.h"
#include "GameMain.h"
#include "SceneManage.h"
#include "TutorialScene.h"

STexture	*pT_mainBackground = NULL;
SSprite		*pS_mainBackground = NULL;

extern POINT	CursorPos;
//.텍스트파일 출력부분, 크기와 폰트가 달라지는거 아니면 한 변수에서 돌려쓰기 가능.
SText		text;
SText		Titletext;
extern	bool Click;
extern	int Chapter;
RECT GameStart;

int StartMenu_X = 520;
int StartMenu_Y = 480;

bool LoadMenuSceneData()
{
	//. 메인배경
	pT_mainBackground = new STexture;
	memset(pT_mainBackground, 0 , sizeof(STexture));
	TextureLoad(pT_mainBackground, "MainBackGround.png", D3DCOLOR_ARGB(255, 255, 255, 0));

	pS_mainBackground = new SSprite;
	memset(pS_mainBackground, 0, sizeof(SSprite));
	CreateSprite(pS_mainBackground, pT_mainBackground, 1280, 800);

	Createfont(&text,"한컴 쿨재즈 M",60);
	Createfont(&Titletext, "Chiller", 200); 

	return TRUE;
}

bool UpdateMenuScene()
{

	//update 한번 루프때마다 매 마우스의 커서를 추적.
	GetMousePos(g_hWnd, &CursorPos);
	GameStart.top = StartMenu_Y;
	GameStart.bottom = StartMenu_Y+50;
	GameStart.left = StartMenu_X;
	GameStart.right = StartMenu_X+170;

	if((CursorPos.x >= GameStart.left && CursorPos.x <= GameStart.right) && (CursorPos.y >= GameStart.top && CursorPos.y <= GameStart.bottom))
	{
		if(Click == TRUE)
		{
		Click = FALSE;
		ReleaseScene(Chapter);
		Chapter = 1;
		LoadScene(Chapter);
		}
	}
	else
		Click = FALSE;
	return TRUE;
}

bool RenderMenuScene()
{

	//메인메뉴 구성
	Put(pS_mainBackground, 0,0);
	PutText(&Titletext, "TOLT", 390, 100, D3DCOLOR_ARGB(255, 255, 0 , 0));
	PutText(&text,"게임시작",StartMenu_X,StartMenu_Y,D3DCOLOR_ARGB(195,255,255,255));

	//마우스 커서를 올릴 경우 색 변경
	if((CursorPos.x >=GameStart.left && CursorPos.x <=GameStart.right) && (CursorPos.y >= GameStart.top && CursorPos.y <= GameStart.bottom))
	{
		PutText(&text,"게임시작",StartMenu_X,StartMenu_Y,D3DCOLOR_ARGB(150,255,185,0));
	}

	return TRUE;
}

bool ReleaseMenuSceneData()
{
	ReleaseSprite(pS_mainBackground);
	ReleaseTexture(pT_mainBackground);

	ReleaseFont(&text);
	ReleaseFont(&Titletext);

	return TRUE;
}