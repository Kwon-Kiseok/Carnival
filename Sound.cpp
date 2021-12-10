#include "Sound.h"
#include "Define.h"


CDSHOW::CDSHOW()
{
	m_pGB = NULL;
}

CDSHOW::~CDSHOW()
{
}

HRESULT CDSHOW::CreateShow()
{
	HRESULT hr = S_OK;

	
	//COM 초기화
	if(FAILED (hr = CoInitialize(NULL)) ) return hr;

	//DirectShow Graph 초기화
	if(FAILED (hr = CoCreateInstance(CLSID_FilterGraph, NULL,
                                     CLSCTX_INPROC, IID_IGraphBuilder,
                                     reinterpret_cast<void **>(&m_pGB)))) return hr;
	return hr;
}

HRESULT CDSHOW::ReleaseShow()
{
	HRESULT hr = S_OK;
	if(m_pGB)
	{
		SAFE_RELEASE(m_pGB);
		// Finished with COM
		CoUninitialize();
	}
	return hr;
}

HRESULT CDSHOW::OpenFile(LPSTR szFile)
{
	if(m_pGB) ReleaseShow();

	CreateShow();

	WCHAR wFileName[MAX_PATH];
	MultiByteToWideChar(CP_ACP, 0, szFile, -1, wFileName, MAX_PATH);

	HRESULT hr=S_OK;
	if(m_pGB)
	{
		hr = m_pGB->RenderFile(wFileName , NULL);
	}
	return hr;
}

HRESULT CDSHOW::CloseFile()
{
	if(m_pGB) 
	{
		Stop();
		ReleaseShow();
	}
	return S_OK;
}

HRESULT CDSHOW::Play(bool len)
{
	HRESULT hr = S_OK;
	IMediaControl *pMC = NULL; //지역변수로 사용해도 상관없음 
	if(m_pGB)
	{
		if(len==FALSE)
			Stop();
		hr = m_pGB->QueryInterface(IID_IMediaControl , (void**)&pMC);
		pMC->Run();
	}
	SAFE_RELEASE(pMC);
	return hr;
}

HRESULT CDSHOW::Stop()
{
	HRESULT hr = S_OK;
	IMediaControl *pMC = NULL; //지역변수로 사용해도 상관없음 
	IMediaSeeking *pMS = NULL; //이것역시..

	if(m_pGB)
	{
		hr = m_pGB->QueryInterface(IID_IMediaControl , (void**)&pMC); if(FAILED(hr)) return hr;
		hr = m_pGB->QueryInterface(IID_IMediaSeeking,  (void**)&pMS); if(FAILED(hr)) return hr;
		
		pMC->Pause(); 
		LONGLONG SeekPos=0;
		pMS->SetPositions(&SeekPos , AM_SEEKING_AbsolutePositioning , NULL , AM_SEEKING_NoPositioning);
	}
	
	SAFE_RELEASE(pMC);
	SAFE_RELEASE(pMS);

	return hr;
}

HRESULT CDSHOW::Continue()
{
	HRESULT hr = S_OK;
	IMediaControl *pMC = NULL; //지역변수로 사용해도 상관없음 
	if(m_pGB)
	{
		hr = m_pGB->QueryInterface(IID_IMediaControl , (void**)&pMC);
		pMC->Run();
	}
	SAFE_RELEASE(pMC);
	return hr;
}

HRESULT CDSHOW::Pause()
{
	HRESULT hr = S_OK;
	IMediaControl *pMC = NULL; //지역변수로 사용해도 상관없음 
	if(m_pGB)
	{
		hr = m_pGB->QueryInterface(IID_IMediaControl , (void**)&pMC);
		if(FAILED(hr)) return hr;
		pMC->Pause();
	}
	SAFE_RELEASE(pMC);
	return hr;
}

HRESULT CDSHOW::Loop()
{
	HRESULT hr=S_OK;
    LONG evCode, evParam1, evParam2;
	IMediaEventEx *pME = NULL;
	if(m_pGB)
	{
		m_pGB->QueryInterface(IID_IMediaEventEx, (void**)(&pME));
		while(SUCCEEDED(pME->GetEvent(&evCode, &evParam1, &evParam2, 0)))
		{
			if(EC_COMPLETE == evCode)
			{
				Stop();
				Play(TRUE);
			}
		}
		hr = pME->FreeEventParams(evCode , evParam1 , evParam2);
	}
	SAFE_RELEASE(pME);
	return hr;
}

bool CDSHOW::EndCheck()
{
	LONG evCode, evParam1, evParam2;
	IMediaEventEx *pME = NULL;
	if(m_pGB)
	{
		m_pGB->QueryInterface(IID_IMediaEventEx, (void**)(&pME));
		while(SUCCEEDED(pME->GetEvent(&evCode, &evParam1, &evParam2, 0)))
		{
			if(EC_COMPLETE == evCode)
			{
				Stop();
				return true;
			}
		}
	}

	return false;
}