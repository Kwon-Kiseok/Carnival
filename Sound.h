#ifndef _DIRECT_SOUND_SHOW_HEADER_
#define _DIRECT_SOUND_SHOW_HEADER_

#include <tchar.h>
#include <dshow.h>

#pragma comment(lib , "strmiids.lib")

class CDSHOW
{
private :
	IGraphBuilder *m_pGB;

public :
	CDSHOW();
	~CDSHOW();

	HRESULT		CreateShow();				//. 사용 필요 없음
	HRESULT		ReleaseShow();				//. 사용 필요 없음
	HRESULT		OpenFile(LPSTR szfile);		//. 사용. 파일 오픈
	HRESULT		CloseFile();				//. 사용. 파일 종료

	HRESULT		Play(bool len);				//. 사용. 음악 재생
	HRESULT		Stop();						//. 사용. 음악 정지
	HRESULT		Continue();					//. 사용. 음악 다시 재생.
	HRESULT		Pause();					//. 사용. 음악 일시 정지.
	HRESULT		Loop();						//. 플레이 전이나 후에 이 함수를 실행하면 음악이 끝났을 시 다시 계속 재생.
	bool		EndCheck();
};
#endif