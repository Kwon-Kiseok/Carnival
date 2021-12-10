#include "Gamemain.h"
#include "Win.h"
#include "Timer.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Entry Point.
//.-------------------------------------------------------------------------------------------------------------------------------------------
/*!
		Windows program의 시작점은 main이 아닌 winmain이다.
		따라서, 모든 Windows program은 Winmain에서부터 시작한다.

		hInstance		: 프로그램의 인스턴스 핸들.

		hPrevInstance	: 바로 앞에 실행된 현제 프로그램의 인스턴스 핸들.
						  없을 경우는 NULL이며 Win32에서는 항상 NULL이다.

		lpCmdLine		: 명령행으로 입력된 프로그램 인수이다.

		nShowCmd		: 프로그램이 실행될 형태이며, 최소화, 보통 보양 등이 전달된다.
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdlin, int nShowCmd)
{
#if _DEBUG
	//메모리 릭 잡기 위한 코드.

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 92;
	//디버그용 콘솔
	#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

	Intialize();	//. 윈도우 및 Direct3D 초기화 한다.

	LoadData();		//. 데이터를 로드한다.

	SetFPS(pFPS, 64);	//FPS 고정.

	MsgLoop();		//. 메세지를 반복한다.

	ReleaseData();	//. 데이터를 해제 한다.

	return true;
}