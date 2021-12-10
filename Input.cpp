#include "Input.h"

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Input ����ü.
//.-------------------------------------------------------------------------------------------------------------------------------------------

struct SVKEY
{
	BYTE	bKeyStates[256];
	DWORD	dwKeyPressTimes[256];
	BYTE	bRecent;
}gVKey;

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Keyboard�� ���¸� ��´�. (CDX������)
//.-------------------------------------------------------------------------------------------------------------------------------------------
void ScanfVKey()
{
	BYTE bKeyStates[256];			//. Ű ���� �迭
	GetKeyboardState(bKeyStates);	//. Api�Լ��� Ű�� ���¸� ���� Ű ���� �迭�� ����

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
//. Virtual Key�� ���¸� ���´�.
//.-------------------------------------------------------------------------------------------------------------------------------------------
int GetVKeyState(int VirtKey)
{
	return gVKey.bKeyStates[VirtKey];
}

//.-------------------------------------------------------------------------------------------------------------------------------------------
//. Mouse�� ��ġ�� ����ش�.
//.-------------------------------------------------------------------------------------------------------------------------------------------
void GetMousePos(HWND hwnd, LPPOINT lpPoint)
{
	GetCursorPos(lpPoint);
	ScreenToClient(hwnd, lpPoint);
}