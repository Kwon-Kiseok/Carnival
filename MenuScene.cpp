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
//.�ؽ�Ʈ���� ��ºκ�, ũ��� ��Ʈ�� �޶����°� �ƴϸ� �� �������� �������� ����.
SText		text;
SText		Titletext;
extern	bool Click;
extern	int Chapter;
RECT GameStart;

int StartMenu_X = 520;
int StartMenu_Y = 480;

bool LoadMenuSceneData()
{
	//. ���ι��
	pT_mainBackground = new STexture;
	memset(pT_mainBackground, 0 , sizeof(STexture));
	TextureLoad(pT_mainBackground, "MainBackGround.png", D3DCOLOR_ARGB(255, 255, 255, 0));

	pS_mainBackground = new SSprite;
	memset(pS_mainBackground, 0, sizeof(SSprite));
	CreateSprite(pS_mainBackground, pT_mainBackground, 1280, 800);

	Createfont(&text,"���� ������ M",60);
	Createfont(&Titletext, "Chiller", 200); 

	return TRUE;
}

bool UpdateMenuScene()
{

	//update �ѹ� ���������� �� ���콺�� Ŀ���� ����.
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

	//���θ޴� ����
	Put(pS_mainBackground, 0,0);
	PutText(&Titletext, "TOLT", 390, 100, D3DCOLOR_ARGB(255, 255, 0 , 0));
	PutText(&text,"���ӽ���",StartMenu_X,StartMenu_Y,D3DCOLOR_ARGB(195,255,255,255));

	//���콺 Ŀ���� �ø� ��� �� ����
	if((CursorPos.x >=GameStart.left && CursorPos.x <=GameStart.right) && (CursorPos.y >= GameStart.top && CursorPos.y <= GameStart.bottom))
	{
		PutText(&text,"���ӽ���",StartMenu_X,StartMenu_Y,D3DCOLOR_ARGB(150,255,185,0));
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