#include "Gamemain.h"
#include "Win.h"
#include "Timer.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Entry Point.
//.-------------------------------------------------------------------------------------------------------------------------------------------
/*!
		Windows program�� �������� main�� �ƴ� winmain�̴�.
		����, ��� Windows program�� Winmain�������� �����Ѵ�.

		hInstance		: ���α׷��� �ν��Ͻ� �ڵ�.

		hPrevInstance	: �ٷ� �տ� ����� ���� ���α׷��� �ν��Ͻ� �ڵ�.
						  ���� ���� NULL�̸� Win32������ �׻� NULL�̴�.

		lpCmdLine		: ��������� �Էµ� ���α׷� �μ��̴�.

		nShowCmd		: ���α׷��� ����� �����̸�, �ּ�ȭ, ���� ���� ���� ���޵ȴ�.
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdlin, int nShowCmd)
{
#if _DEBUG
	//�޸� �� ��� ���� �ڵ�.

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_crtBreakAlloc = 92;
	//����׿� �ܼ�
	#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

	Intialize();	//. ������ �� Direct3D �ʱ�ȭ �Ѵ�.

	LoadData();		//. �����͸� �ε��Ѵ�.

	SetFPS(pFPS, 64);	//FPS ����.

	MsgLoop();		//. �޼����� �ݺ��Ѵ�.

	ReleaseData();	//. �����͸� ���� �Ѵ�.

	return true;
}