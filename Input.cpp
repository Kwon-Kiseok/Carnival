#include "Input.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Input 구조체.
//.-------------------------------------------------------------------------------------------------------------------------------------------

struct SVKEY
{
	BYTE	bKeyStates[256];
	DWORD	dwKeyPressTimes[256];
	BYTE	bRecent;
}gVKey;

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Keyboard의 상태를 얻는다. (CDX참고함)
//.-------------------------------------------------------------------------------------------------------------------------------------------
void ScanfVKey()
{
	BYTE bKeyStates[256];			//. 키 상태 배열
	GetKeyboardState(bKeyStates);	//. Api함수로 키드 상태를 얻어와 키 상태 배열에 저장

	BYTE	*pbKeyStates		= gVKey.bKeyStates;
	DWORD	*pdwKeyPressTimes	= gVKey.dwKeyPressTimes;
	BYTE	*bRecent			= &gVKey.bRecent;

	for(int key=0; key<256; key++)
	{
		if(bKeyStates[key] & 0x80)
		{
			if(pbKeyStates[key] == VK_NONE || pbKeyStates[key] == VK_RELEASE)
			{
				//. press event (Key was up before but down now)
				pbKeyStates[key] = VK_PRESS;
				pdwKeyPressTimes[key] = timeGetTime();
				*bRecent = key;
			}
			else if(pbKeyStates[key] == VK_PRESS)
			{
				//. drag event (key is still down)
				pbKeyStates[key] = VK_REPEAT;
			}
		}
		else //. Key is not currently pressed
		{
			if(pbKeyStates[key] == VK_REPEAT || pbKeyStates[key] == VK_PRESS)
			{
				//. release event (Key was down before but up now)
				pbKeyStates[key] = VK_RELEASE;
			}
			else if(pbKeyStates[key] == VK_RELEASE)
			{
				pbKeyStates[key] = VK_NONE;
			}
		}
	}
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Virtual Key의 상태를 얻어온다.
//.-------------------------------------------------------------------------------------------------------------------------------------------
int GetVKeyState(int VirtKey)
{
	return gVKey.bKeyStates[VirtKey];
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Mouse의 위치를 얻어준다.
//.-------------------------------------------------------------------------------------------------------------------------------------------
void GetMousePos(HWND hwnd, LPPOINT lpPoint)
{
	GetCursorPos(lpPoint);
	ScreenToClient(hwnd, lpPoint);
}