//.-------------------------------------------------------------------------------------------------------------------------------------------
//. File : Define.h
//.
//. Windows Application for the 2006 Creator Library.
//.
//. 작성일 : 2006. 05. 28.
//.
//. 작성자 : 04학번 김 형 철
//.-------------------------------------------------------------------------------------------------------------------------------------------
#ifndef _DEFINE_H_
#define _DEFINE_H_

#include  <windows.h>


#define PI			(float)3.141592653589794348462643383279502		//. degree(180)
#define DEGREE		(float)0.017453292519943295769234907684886		//. degree(1)

//>>>>>>>>>>>>>>>>>>
//WINUSERAPI
//int
//WINAPI
//DrawTextA(
//    __in HDC hdc,
//    __inout_ecount_opt(cchText) LPCSTR lpchText,
//    __in int cchText,
//    __inout LPRECT lprc,
//    __in UINT format);
//WINUSERAPI
//int
//WINAPI
//DrawTextW(
//    __in HDC hdc,
//    __inout_ecount_opt(cchText) LPCWSTR lpchText,
//    __in int cchText,
//    __inout LPRECT lprc,
//    __in UINT format);
//#ifdef UNICODE
//#define DrawText  DrawTextW
//#else
//#define DrawText  DrawTextA
//#endif // !UNICODE
//
//#if defined(_M_CEE)
//#undef DrawText
//__inline
//int
//DrawText(
//    HDC hdc,
//    LPCTSTR lpchText,
//    int cchText,
//    LPRECT lprc,
//    UINT format
//    )
//{
//#ifdef UNICODE
//    return DrawTextW(
//#else
//    return DrawTextA(
//#endif
//        hdc,
//    lpchText,
//    cchText,
//    lprc,
//    format
//        );
//}
//#endif  /* _M_CEE */
//
//
//#if(WINVER >= 0x0400)
//WINUSERAPI
//int
//WINAPI
//DrawTextExA(
//    __in HDC hdc,
//    __inout_ecount_opt(cchText) LPSTR lpchText,
//    __in int cchText,
//    __inout LPRECT lprc,
//    __in UINT format,
//    __in_opt LPDRAWTEXTPARAMS lpdtp);
//WINUSERAPI
//int
//WINAPI
//DrawTextExW(
//    __in HDC hdc,
//    __inout_ecount_opt(cchText) LPWSTR lpchText,
//    __in int cchText,
//    __inout LPRECT lprc,
//    __in UINT format,
//    __in_opt LPDRAWTEXTPARAMS lpdtp);
//#ifdef UNICODE
//#define DrawTextEx  DrawTextExW
//#else
//#define DrawTextEx  DrawTextExA
//#endif // !UNICODE
//#endif /* WINVER >= 0x0400 */
//
//#endif /* !NODRAWTEXT */
//
//WINUSERAPI
//BOOL
//WINAPI
//GrayStringA(
//    __in HDC hDC,
//    __in_opt HBRUSH hBrush,
//    __in_opt GRAYSTRINGPROC lpOutputFunc,
//    __in LPARAM lpData,
//    __in int nCount,
//    __in int X,
//    __in int Y,
//    __in int nWidth,
//    __in int nHeight);
//WINUSERAPI
//BOOL
//WINAPI
//GrayStringW(
//    __in HDC hDC,
//    __in_opt HBRUSH hBrush,
//    __in_opt GRAYSTRINGPROC lpOutputFunc,
//    __in LPARAM lpData,
//    __in int nCount,
//    __in int X,
//    __in int Y,
//    __in int nWidth,
//    __in int nHeight);
//#ifdef UNICODE
//#define GrayString  GrayStringW
//#else
//#define GrayString  GrayStringA
//#endif // !UNICODE
////<<<<<<<<<<<<<<<<



//.-------------------------------------------------------------------------------------------------------------------------------------------
//. 템플릿 클래스
//.-------------------------------------------------------------------------------------------------------------------------------------------

template <class DATA>
inline void SAFE_RELEASE(DATA &Data)
{
	if(Data != NULL)
	{
		Data->Release(); 
		Data = NULL;
	}
}

template <class DATA>
inline void SAFE_DELETE(DATA &Data)
{
	if(Data != NULL)
	{
		delete Data;
		Data=NULL;
	}
}

template <class DATA>
inline void SAFE_DELETE_ARRAY(DATA & Data)
{
	if(Data != NULL)
	{
		delete []Data;
		Data = NULL;
	}
}

#endif