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

	HRESULT		CreateShow();				//. ��� �ʿ� ����
	HRESULT		ReleaseShow();				//. ��� �ʿ� ����
	HRESULT		OpenFile(LPSTR szfile);		//. ���. ���� ����
	HRESULT		CloseFile();				//. ���. ���� ����

	HRESULT		Play(bool len);				//. ���. ���� ���
	HRESULT		Stop();						//. ���. ���� ����
	HRESULT		Continue();					//. ���. ���� �ٽ� ���.
	HRESULT		Pause();					//. ���. ���� �Ͻ� ����.
	HRESULT		Loop();						//. �÷��� ���̳� �Ŀ� �� �Լ��� �����ϸ� ������ ������ �� �ٽ� ��� ���.
	bool		EndCheck();
};
#endif