#include "TutorialScene.h"
#include "MenuScene.h"
#include "SceneManage.h"
#include "Chapter1.h"

bool UpdateScene(int SceneName)
{
	switch(SceneName)
	{
		case 0:
			UpdateMenuScene();
			break;
		case 1:
			UpdateTutorialScene();
			break;
		case 2:
			UpdateChapter1Data();
			break;

		/*case Tutorial:
			UpdateTutorialScene;*/
	}
			return TRUE;
}

bool LoadScene(int SceneName)
{
	switch(SceneName)
	{
		case 0:
			LoadMenuSceneData();
			break;
		case 1:
			LoadTutorialSceneData();
			break;
		case 2:
			LoadChapter1Data();
			break;
	}
			return TRUE;
}
bool RenderScene(int SceneName)
{
	switch(SceneName)
	{
		case 0:
			RenderMenuScene();
			break;
		case 1:
			RenderTutorialScene();
			break;
		case 2:
			RenderChapter1Scene();
			break;

	}
			return TRUE;
}


bool ReleaseScene(int SceneName)
{
	switch(SceneName)
	{
		case 0:
			ReleaseMenuSceneData();
			break;
		case 1:
			ReleaseTutorialScene();
			break;
		case 2:
			ReleaseChapter1Data();
			break;
	}
			return TRUE;
}