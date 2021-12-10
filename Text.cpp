#include "Text.h"

HRESULT Createfont(SText *text,char *fontName,int size)
{
	// GetDC함수
	// hWnd:DC를 구하고자 하는 윈도우 핸들. NULL일 경우 전체 화면에 대한 DC가 구해진다.
	HDC hDC = GetDC( NULL );

	//GetDeviceCaps함수
	//The GetDeviceCaps function retrieves device-specific information for the specified device.
	
	//전달인자
	//hdc [in]
	//A handle to the DC.

	//nIndex [in]
	//The item to be returned. This parameter can be one of the following values.

	//LOGPIXELSY
	//Number of pixels per logical inch along the screen height. In a system with multiple display monitors, this value is the same for all monitors.

	text->m_nFontSize = size;

	int nLogPixelsY = GetDeviceCaps( hDC, LOGPIXELSY );

	ReleaseDC( NULL, hDC );

	int nHeight = -text->m_nFontSize * nLogPixelsY / 72;


	HRESULT hr = D3DXCreateFont( g_pD3DDevice,            // D3D device
		nHeight,               // Height
		0,                     // Width
		FW_BOLD,               // Weight
		1,                     // MipLevels, 0 = autogen mipmaps
		FALSE,                 // Italic
		DEFAULT_CHARSET,       // CharSet
		OUT_DEFAULT_PRECIS,    // OutputPrecision
		DEFAULT_QUALITY,       // Quality
		DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
		fontName,              // pFaceName
		&text->m_pFont );      // ppFont

	if(	FAILED(hr) )
	{
		return hr;	
	}

	return S_OK;

}


void PutText(SText *text,char *str,float x,float y,D3DXCOLOR color)
{
	// Pass in DT_NOCLIP so we don't have to calc the bottom/right of the rect
	RECT rc;
	SetRect(&rc,x,y,0,0);
	text->m_pFont->DrawText(NULL,str,-1,&rc,DT_NOCLIP,color);


}


void ReleaseFont(SText *text)
{
	if(NULL != text->m_pFont)
	{
		text->m_pFont->Release();
	}
}