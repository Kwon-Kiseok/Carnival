#include "Win.h"
#include "GameMain.h"
#include "Timer.h"
#include "TutorialScene.h"CursorPos
#include "MenuScene.h"
#include "Chapter1.h"

HWND		g_hWnd		= NULL;
HINSTANCE	g_hInstance	= NULL;
float		dt = 0;
bool		g_bLoop		= TRUE;
STIME		*pFPS		= new STIME;
POINT		CursorPos;
bool Click = FALSE;

RECT g_windowRect;
/*!
인스턴스(Instance)라는 말은 클래스가 메모리에 실제로 구현된 실체를 위미,
즉, 윈도우용 프로그램은 여러 개의 프로그램이 동시에 실행되는 멀티태스킹
시스템일 뿐만 아니라 하나의 프로그램이 여러번 실행될 수도 있다.
이 때 실행되고 있는 각각의 프로그램을 프로그램 인스턴스라고 하며,
간단히 줄여서 인스턴스라고 한다.
*/
//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 등록 및 생성.
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool InitWindow(HINSTANCE hInstance, LPSTR szAppName, WORD wMenu, WORD wICON, WORD wCursor, DWORD dwSize, DWORD dwStyle)
{
	HWND hWnd = NULL;
	/*!
	윈도우를 만들려면 윈도우 클래스를 먼저 등록한 수 CreateWindow 함수를 호출해야 한다.
	윈도우 클래스는 만들어질 윈도우의 여러가지 특성을 정의하는 구조체이며,
	모든 윈도우는 윈도우 클래스의 정보를 기반으로 하여 만들어진다.
	WNDCLASS 커서를 놓고 "정의로 이동"(F12 또는 오른쪽 버튼 클릭 후 정의로 이동 선택)하면
	10개나 되는 멤버를 볼 수 있다. WNDCLASS 구조체의 각 멤버 의미는 다음과 같다.
	이 내용을 일부러 암기할 필요는 없지만, 대충 어떤 역할을 하는 멤버인지 알아두자.

	cbClsExtra, cbWndExtra : 일종의 예약 영역이다. 윈도우즈가 내부적으로 사용하며,
	아주 특수한 목적에 사용되는 여분의 공간이다.
	예약 영역을 사용하지 않을 경우 NULL로 지정한다.

	hbaBackground : 윈도우 배경 채색할 브러시를 지정.
	GetStockObject 라는 함수를 사용하여 흰색으로 배경을 칠했다.
	WHITE_BRUSH 에 커서를 가져다 놓고 f12를 누르면
	다음과 같이 정의 되어 있는 것을 볼 수 있다.
	#define WHITE_BRUSH			0
	#define LTGRAY_BRUSH		1
	#define GRAY_BRUSH			2
	#define	DKGRAY_BRUSH		3
	#define BLACK_BRUSH			4
	#define NULL_BRUSH			5

	hIcon, hCirsor : 윈도우가 사용할 아이콘과 커서이다. LoadIcon 함수와 LoadCursor 함수를
	사용하여 아이콘, 커서를 읽어와 이 멤버에 대입해 주면 된다.

	lpszMenuName : 프로그램이 사용할 메뉴를 지정한다. 메뉴 프로그램은 리소스 에디터에
	의해 별도로 만들어진 후 링크시에 같이 합쳐진다.
	메뉴를 사용하지 않으므로 NULL 대입해준다.

	hinstance : 윈도우 클래스를 등록하는 프로그램의 번호이며,
	이 값은 Winmain의 인수로 전달된 hInstance 값을 그대로 대입해주면 된다.

	lpfnwndproc : 윈도우의 메세지 처리 함수를 지정, 메세지가 발생할 때마다 이 멤버가
	지정하는 함수가 호출되어 이 함수가 모든 메세지를 처리한다.

	lpszClassName : 윈도우 클래스의 이름을 문자열로 정의한다, 여기서 지정한 이름은
	CreateWindow 함수에 전달되며 CreateWindows 함수는 윈도우 클래스에서
	정의한 특정값을 참조하여 윈도우를 만든다.

	style : 윈도우 스타일 정의. 즉, 윈도우가 어떤 형태를 가질 것인가를 지정하는 멤버.
	가장 많이 사용되는 값이 CS_Hredraw | CS_VREDRAW이다.
	윈도우의 수직 또는 수평 크기가 변할 경우 윈도우를 다시 그린다는 뜻이다.
	*/

	WNDCLASS WndClass;

	WndClass.cbClsExtra		= NULL;
	WndClass.cbWndExtra		= NULL;
	WndClass.hbrBackground	= (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndClass.lpszMenuName	= NULL;
	WndClass.hInstance		= hInstance;
	WndClass.lpfnWndProc	= (WNDPROC)WndProc;
	WndClass.lpszClassName	= szAppName;
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	/*!
	윈도우 클래스 구조체를 정의한 후 RegisterClass 함수를 호출하여 윈도우 클래스를 등록한다.
	RegisterClass 함수의 인자로 WNDCLASS 구조체의 번지를 넘겨주면 된다.
	운영체제는 이 윈도우 클래스의 특성을 잘 기억해 놓는다.
	*/
	RegisterClass(&WndClass);

	//.사이즈를 정해주지 않았으므로 800x600으로 만든다.
	int WinWidth	= 0;
	int WinHeight	= 0;

	if(dwSize & WIN_SIZE_640x480)
	{
		WinWidth	= 640;
		WinHeight	= 480;
	}
	else if(dwSize & WIN_SIZE_800x600)
	{
		WinWidth	= 800;
		WinHeight	= 600;
	}
	else if(dwSize & WIN_SIZE_1280x800)
	{
		WinWidth	=1280;
		WinHeight	=800;
	}
	//. 현재 화면의 크기를 구함.
	int WinX = GetSystemMetrics(SM_CXSCREEN);
	int WinY = GetSystemMetrics(SM_CYSCREEN);

	/*!
	윈도우 클래스를 등록한 후에는 이 윈도우 클래스를 기본으로 실제 윈도우를 생성해야 한다.
	윈도우를 생성할 때는 CreateWindow 함수를 사용한다. 원형은 다음과 같다.

	HWND CreateWindow(lpszClassName, lpszWindowName, dwStyle, x, y, nWidth, nHeight,
	hwndParent, hmenu, hinst, lpvParam)

	lpszClassName : 생성하고자 하는 윈도우의 클래스를 지정하는 문자열이다.
	WNDCLASS 구조체의 lpszClassName 멤버에 대한 값을 여기에 대입한다.

	lpszWindowName : 윈도우 타이틀 바에 나타날 문자열이다.
	함수에서 인자로 받아온 문자열을 출력한다.

	dwStyle : 만들고자 하는 윈도우 형태를 지정하는 인수이다. 크기 조절이 가능하도록 할 것인가,
	타이틀 바를 가질 것인가, 스크롤 바의 유무 등등을 세세하게 지정해 줄 수 있다.
	헤더 파일에 함수 프로토 타입 선언에 기본적으로 WS_OVERLAPPEDWINDOW를 정의 하였기
	때문에 가장 무난한 설정 상태인 시스템 메뉴, 최대 최소 버튼, 타이틀 바,
	경계선을 가진 윈도우가 생성된다.

	x, y : 윈도우 위치를 지정 해준다. 현재 화면 크기를 얻어와 중앙에 위치하도록 설정하였다.

	nWidth, nHeight : 윈도우 크기를 지정한다. 기본적으로 설정한 800 x 600 이 지정된다.

	hwndParent : 부모 윈도우가 있을 경우 부모 윈도우의 핸들을 지정해 준다.
	MDI 프로그램이나 팝업 윈도우는 윈도우끼리 수직적인 상하관계를 가져
	부자(parent-child)관계가 성립되는데 이 관계를 지정해 주는 인수이다.
	부모 윈도우가 없을 경우는 이 값을 NULL로 지정하면 된다.

	hmenu : 윈도우에서 사용할 메뉴의 핸들을 지정한다. 윈도우에서 지정한 메뉴를 그대로
	사용하려면 이 인수를 NULL로 지정하면 된다.
	hinst : 윈도우를 만든 주체, 즉 프로그램의 핸들을 지정한다.
	Winmain의 인수로 전달된 hInstance를 대입해 주면 된다.

	lpParam : CREACursorPosRUCT 라는 구조체의 번지이며 특수한 목적에 사용된다.
	보통은 NULL 값을 사용한다.

	CreateWindow 함수는 윈도우에 관한 모든 정보를 메모리에 만든 후 핸들을 리턴 값으로
	넘겨 준다. 넘겨지는 윈도우 핸들을 hWnd라는 변수에 저장되었다가 윈도우를 참조하는
	모든 함수의 인수로 사용된다.

	ps. 여기서 당장 CreateWindow의 모든 인수에 대해 다 외우려고 할 필요까지는 없다.
	어떤 값이 사용되었는가와 그 의미가 무엇인가만 알아두도록 하자.
	조언을 한가지 하자면 공부를 할 때는 무시할 건 무시하고 지나가는 요령이 때론 필요하다.
	API를 처음 배우는 사람에게는 모든 인수들의 정확한 의미를 꼼꼼이 알려고
	할 필요는 없다. 그렇다고 해서 무시하고 넘어가라는 소리는 아니다.
	완벽하게 이해한다고 해서 나쁠 것은 없지만 처음부터 그렇게 하다가는 제풀에 지쳐
	금세 흥미를 읽고 만다. 중요한 것은 이론적으로 의미가 있는 큰 줄기를 먼저 파악
	하는데 노력하라는 소리이다.
	*/


	hWnd = CreateWindow(szAppName, szAppName, dwStyle, WinX/2 - WinWidth/2, WinY/2 - WinHeight/2, WinWidth, WinHeight, NULL, NULL, hInstance, NULL);

	//. hWnd 에 값이 리턴이 안 될 경우 FALSE를 대입하여 실패하게 된다.
	if(hWnd == NULL)
	{
		return FALSE;
	}

	//창으로 띄울때 뷰공간을 맞춰주기 위함...
	//0RECT rect;


	SetRect(&g_windowRect, 0, 0, WinWidth, WinHeight);				//사각형을 설정	
	AdjustWindowRect(&g_windowRect, WS_OVERLAPPEDWINDOW, false);	//사용자가 원하는 클라이언트 크기를 포함한 전체 윈도우 응용프로그램의 크기를 계산해 주는 함수.
	MoveWindow(hWnd, WinX / 2 - WinWidth / 2, WinY / 2 - WinHeight / 2, g_windowRect.right - g_windowRect.left, g_windowRect.bottom - g_windowRect.top, TRUE);	//생성된 윈도우의 위치와 크기를 변경하는 역할



	/*!
	CreateWindow 함수로 만든 윈도우는 메모리상에만 있을 뿐이며 아직까지 화면에 출력되지는
	않았다. 메모리에 만들어진 윈도우를 화면으로 보이게 하려면 ShowWindow 함수를 사용하면 된다.
	원형은 다음과 같다.

	BOOL ShowWindow(hWnd, nCmdShow)

	hWnd : 화면으로 출력하고자 하는 윈도우 핸들.
	nCmdShow : 윈도우를 화면에 출력하는 방법을 지정.
	F12키를 눌러 다음과 매크로 상수들이 정의 되어 있는 것을 볼 수 있다.
	몇가지만 살펴보자.

	SW_HIDE		: 윈도우를 숨긴다.
	SW_MINIMIZE	: 윈도우를 최소화 시키고 활성화 시키지 않는다.
	SW_RESTORE	: 윈도우를 활성화 시킨다.
	SW_SHOW		: 윈도우를 활성화 시켜 보여준다.
	SW_SHOWNORMAL : 윈도우를 활성화 시켜 보여 준다.
	*/

	ShowWindow(hWnd, SW_SHOW);
	/*!
	WH_PAINT 메세지를 발생시키는 것이며, 이떄 윈도우가 무효화 영역이 있어야 한다.
	즉, 다시 그려져야할 필요가 있는 영역이 있다면 다시 그리도록 만드는 것이다.

	Tip:
	InvalidateRect 함수는 윈도우의 클라이언트 영역 중에서 일부분을 무효화 시키는 것이다.
	즉, 특정 영역을 무조건 다시 그리도록 하는 함수이다.
	*/

	UpdateWindow(hWnd);
	//. 마우스 커서를 표시한다. 표시 하지 않을 경우 FALSE를 대입.
	ShowCursor(TRUE);

	g_hWnd = hWnd;
	return TRUE;
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 윈도우 프로시져(Window Procedure)
//.-------------------------------------------------------------------------------------------------------------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam)
{
	/*!
	WndProc은 WinMain에서 호출하는 것이 아니라 운영체제에 의해 호출된다.
	Winmain 내의 메세지 루프는 메세지를 메세지 처리 함수(WndProc)로 보내주기만 할 뿐이며
	WndProc은 메세지가 입력되면 운영체제에 의해 호출되어 메세지를 처리한다.
	이렇게 운영체제에 의해 호출되는 응용프로그램 내의 함수를 콜백(CallBack)함수라 한다.
	*/
	switch(uiMsg)
	{
	case WM_CHAR :
		{
			switch(wParam)
			{
				//. ESC키 누를 시 종료.
			case VK_ESCAPE:
				g_bLoop = false;
				PostQuitMessage(0);
				break;
			}
			break;
		}
		/*
		사용자가 시스템 메뉴(종료 버튼x)를 클릭하거나 Alt+F4를 눌러 종료를 할려고 할 때
		발생하는 메세지다. WndProc에서 이 메세지가 발생하면 PostQuitMessage 함수를 호출하여
		WM_QUIT 메세지를 보낸다. g_bLoop 변수에 false 값이 대입 되어 메세지 루프 함수의
		while을 빠져 나오게 되며 winmain이 종료된다.
		*/
	case WM_DESTROY :
		g_bLoop = false;
		SAFE_DELETE(pFPS);
		PostQuitMessage(0);
		break;

		//마우스 왼쪽 클릭 메시지를 받았을떄 실행할 구문.
	case WM_LBUTTONDOWN:
		Click = TRUE;
		if(Click == TRUE)
	{	
		printf("Mouse pos_x : %d\n", CursorPos.x);
		printf("Mouse pos_y : %d\n", CursorPos.y);
	}

	}
	/*!
	DefWindowProc 함수는 WndProc에서 처리하지 않는 나머지 메세지에 관한 처리를
	디폴트 처리를 해준다. WndProc은 메세지를처리 했을 경우 반드시 0을 리턴해 주어야
	한다. 또한 DefWindowProc 함수가 메세지를 처리했을 경우 이 함수가 리턴한 값을
	WndProc 함수가 다시 리턴해 주어야 한다.
	*/
	return DefWindowProc(hWnd, uiMsg, wParam, lParam);
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 메세지 루프 (Message Loop)
//.-------------------------------------------------------------------------------------------------------------------------------------------

bool MsgLoop()
{
	/*!
	도스와 가장 뚜렷한 대비를 이루는 특징 중 하나가 메세지 구동 시스템(Message DrivenSystem)
	이다. 도스에서는 프로그래머에 의해 미리 입력된 일련 명령들을 순서대로 실행하는 순차적
	방법을 사용한다. 윈도우즈는 이와 다르게 프로그램의 실행순서가 명확하게 정해져 있지 않으며
	상황에 따라 실행 순서가 달라지는데 여기서 말하는 상황이란 어떤 메세지가 발생하느냐이다.

	(메세지란 사용자나 시스템 내부적인 동작에 의해 발생된 일체의 변화에 대한 정보이다.
	예를 들면 사용자가 마우스 버튼을 누르거나, 키보드를 누르거나, 윈도우를 최소화 하거나,
	하는 등등 변화에 대한 정보들이 메세지다.)

	메세지 루프에서 하는 일은 메세지를 꺼내고, 필요한 경우 수정을 한 후 응용 프로그램으로
	전달하는 것 뿐이다. 이 과정은 WM_QUIT 메세지가 전달될 때까지, 즉 프로그램이 종료될 때까지
	반복된다. 결국 메세지 루프가 하는 일이란 메세지 큐에서 메세지를 꺼내 메세지 처리
	함수(WndProc)로 보내주는 것 뿐이다. 실제 메세지 처리는 별도의 메세지 처리 함수에서
	실행한다.

	(메세지 큐(Message Queue)란 시스템이나 사용자로부터 발생된 메세지가 잠시 대기하는
	일종의 메세지 임시 저장 영역이다.)
	*/

	//. MSG 구조체 변수.
	MSG mMsg;

	while(g_bLoop)
	{
		/*!
		Peekmessage 함수는 메세지가 있는 없든 즉시 리턴하므로 메세지가 없을 때 다른 일을
		할 수 있다. 그래서 게임 프로그램에서는 GetMessage 함수보다 PeekMessage 함수를 사용한다.
		일반적으로 게임에서는 사용자 입력만 기다리고 있지 않기 떄문이다.
		한마디로 이벤트가 없을 땐 일반적인 게임루틴이 일어나기 때문이다.
		리턴 값이 TRUE라면 메세지가 있다는 뜻이고 FALSE이라면 메세지가 없다는 뜻이다.

		PM_REMOVE : GetMessage 함수처럼 메세지를 큐에서 제거해 버린다.
		PM_NOREMOVE : 메세지 큐에 어떤 메세지가 있는지 검사만 하고 리턴한다.

		tip:
		GetMessage 함수.
		메세지 큐에서 대기중인 메세지를 꺼내 첫 번째 인수로 전달된 MSG 구조체에 복사한다.
		그리고 이 메세지를 메세지 큐에서 제거하고 TRUE 하되 만약 큐에서 가져온 메세지가
		WM_QUIT이면 FLASE를 리턴한다.

		- PeekMessage와 GetMessage의 차이점.
		PeekMessage : 큐에 메세지가 없을경우 0을 리턴하게 된다.
		GetMessage : 큐에 메세지가 없을 경우 리턴하지 않고 메세지를 기다리게 된다.
		*/

		if(PeekMessage(&mMsg, g_hWnd, 0, 0, PM_REMOVE))
		{
			/*!
			PeekMessage 함수로 메세지 루프를 작성했을 경우 WM_QUIT 메세지에 대한 예외 처리를
			반드시 해 주어야 한다. GetMEssage 함수는 WM_QUIT 메세지를 받으면 FALSE를 리턴해
			주어 메세지 루프를 종료할 수 있도록 해 주지만 PeekMessage 함수의 리턴값은
			들어오더라도 무한 반복하게 된다. 그래서 Winmain 함수가 종료되지 않으므로
			정상적인 종료할 방법이 없다.
			*/
			if(mMsg.message == WM_QUIT)
			{
				break;
			}
			//. 키보드 입력 메세지를 가공하여 프로그램에서 쉽게 쓸 수 있도록 해준다.
			TranslateMessage(&mMsg);
			//.메세지 큐에서 꺼낸 메세지를 윈도우 처리 함수(WndProc)로 전달 한다.
			DispatchMessage(&mMsg);
		}
		else
		{
			dt = GetAppTimeDelay();
			if(dt > 0 && dt < 1.0f)
			{
				if(TimeUpdate(pFPS, dt))
				{
					pFPS->m_Count++;
					//.여기서 게임 렌더링을 한다.
					Update(dt);
					Render();
				}
				if(TimeCheck(pFPS))
				{
					pFPS->m_FPS = pFPS->m_Count;
					pFPS->m_Count = 0;
				}
			}
		}
	}
	return TRUE;
}