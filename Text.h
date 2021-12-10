#ifndef _TEXT_H_
#define _TEXT_H_

#include "D3DApp.h"

struct SText
{
	ID3DXFont*	m_pFont;
	int			m_nFontSize;
};

HRESULT Createfont(SText *text,char *fontName,int size);
void	PutText(SText *text,char *str,float x,float y,D3DXCOLOR color);
void	ReleaseFont(SText *text);

#endif // !_TEXT.H_
