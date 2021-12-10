#include "GameMain.h"
#include "Win.h"
#include "Input.h"
#include "Timer.h"
#include "Text.h"
#include "SceneManage.h"
#include "TutorialScene.h"
#include "MenuScene.h"
#include "Chapter1.h"


CDSHOW		background;
CDSHOW		Ping;


static POINT pPlayer;
//POINT	M_CursorPos;
extern STIME		*pFPS;

extern		POINT	CursorPos;
int Chapter = 0;

typedef struct Node
{
	struct Node *next;
	struct Node *prev;
	int code;
	int pos_x;
	int pos_y;
};
Node *head;
Node *tail;

struct Node *CreateNode(int code,int x,int y)
{
	struct Node *HeadNode;
	HeadNode = head;

	while(HeadNode->next)
	{
		HeadNode=HeadNode->next;
	}
	struct Node*NewNode = (struct Node*)malloc(sizeof(struct Node));
	NewNode->code = code;
	NewNode->prev = NULL;
	NewNode->next = NULL;
	NewNode->pos_x = x;
	NewNode->pos_y = y;
	HeadNode->next = NewNode;

	return NewNode;
}
void DeleteNode(Node*node)
{
	struct Node *Current, *temp_Node, *before_Node;

	Current=head->next;
	before_Node=head;

	while(Current != 0)
	{
		temp_Node=Current;
		before_Node->next = Current->next;
		Current = before_Node;
		free(temp_Node);
		
		before_Node=Current;
		Current=Current->next;
	}

}
void RemoveNode(Node*node)
{
	Node *cycle=NULL;
	Node *temp=NULL;

	cycle = node;

	while(cycle != 0)
	{
		temp = cycle;
		cycle = cycle->next;

		free(temp);
	}
	node = NULL;
}

bool Intialize()
{
	//. ������ ��� �� ����.
	InitWindow(g_hInstance, "Creator Library", NULL, NULL, NULL);

	//. Direct3D ����.
	InitD3D(g_hWnd);

	return TRUE;
}
bool ReleaseData()
{
	//. �޸� ����.

	ReleaseD3D();

	ReleaseScene(Chapter);

	background.CloseFile();
	Ping.CloseFile();

	SAFE_DELETE(pFPS);

	return TRUE;
}
bool LoadData()
{
	LoadScene(Chapter);
	background.OpenFile("BackGround.mp3");
	return TRUE;
}

bool Update(float dt)
{

	background.Play(true);
	if (background.EndCheck())
	{
		background.Loop();
	}
	ScanfVKey();			
	if(VKRelease(VK_O))
	{
		Ping.Pause();
	}
	if(VKRelease(VK_I))
	{
		Ping.Continue();
	}
	//�������� ���̸�;


	//GetMousePos(g_hWnd, &M_CursorPos);		//update �ѹ� ���������� �� ���콺�� Ŀ���� ����.

	UpdateScene(Chapter);
	return TRUE;
}
//UpdateScene(sf)
//
//	switch(sf)
//	case menu:
//		UpdateMenuScene;
//		case 
bool Render()
{
	//. �ĸ� ���� �ʱ�ȭ.
	g_pD3DDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(66, 131, 181), 1.0f, 0);

	//. ������ ����.
	if(SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		RenderScene(Chapter);
		//. ������ ����.
		g_pD3DDevice->EndScene();
	}

	//. �ĸ� ���۸� ���̴� ȭ������ !
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);


	return TRUE;
}
