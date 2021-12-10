//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : GameMain.h
//.
//. Windows Alpplication for the 2006 Creator Library.
//.
//. 작성일 : 2006. 05. 28.
//.
//. 작성자 : 04학번 김 형 철
//.-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "Sprite.h"
#include "Sound.h"
#include "Animation.h"

bool Intialize();
bool ReleaseData();
bool LoadData();
bool Update(float dt);
bool Render();
struct Node *CreateNode(int code,int x,int y);
void DeleteNode(Node*node);
void RemoveNode(Node*node);

extern STexture *pT_Plater;
extern SSprite	*pS_mainBackground;

#endif