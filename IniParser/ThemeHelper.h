
#pragma once

#include <wtypes.h>
#include <tchar.h>

#pragma warning(disable:4786)
#include <string>
#include <map>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// CThemeHelper

// SizingType
#define INI_TRUESIZE		4
#define INI_STRETCH			5
#define INI_TILE			6
#define INI_TILEHORZ		7
#define INI_TILEVERT		8
#define INI_TILECENTER		9

// ContentAlignment
#define INI_LEFT			10
#define INI_CENTER			11
#define INI_RIGHT			12

// ImageLayout
#define INI_VERTICAL		13
#define INI_HORIZONTAL		14

// BgType
#define INI_IMAGEFILE		15
#define INI_BORDERFILL		16
#define INI_NONE			0

// GlyphType
#define INI_IMAGEGLYPH		17
#define INI_FONTGLYPH		18
//#define NONE				0

// ImageSelectType
//#define NONE				0
#define INI_SIZE			19
#define INI_DPI				20

// OffsetType
#define INI_TOPLEFT				21
#define INI_TOPRIGHT			22
#define INI_TOPMIDDLE			23
#define INI_BOTTOMLEFT			24
#define INI_BOTTOMRIGHT			25
#define INI_BOTTOMMIDDLE		26
#define INI_MIDDLELEFT			27
#define INI_MIDDLERIGHT			28
#define INI_LEFTOFCAPTION		29
#define INI_RIGHTOFCAPTION		30
#define INI_LEFTOFLASTBUTTON	31
#define INI_RIGHTOFLASTBUTTON	32
#define INI_ABOVELASTBUTTON		33
#define INI_BELOWLASTBUTTON		34


class CThemeHelper
{
private:
	CThemeHelper();
public:
	virtual ~CThemeHelper();

public:
	static BOOL IsStringLeadWith(LPCTSTR lpszString, LPCTSTR lpszLead);
	static BOOL IsUnicodeText(LPVOID pText);

	//Parse (T)
	static COLORREF ParseColor(LPCTSTR lpszColor);		//XXX XXX XXX
	static COLORREF ParseColor(LPCTSTR lpszColor, COLORREF clrDefault);		//XXX XXX XXX
	static int ParseInt(LPCTSTR lpszInt);		//XXX
	static int ParseInt(LPCTSTR lpszInt, int iDefault);		//XXX
	static INT32 ParseInt32(LPCTSTR lpszInt32);		//XXX
	static INT32 ParseInt32(LPCTSTR lpszInt32, INT32 iDefault);		//XXX
	static BOOL ParseFont(LPCTSTR lpszFont, LOGFONT* lpLogFont);	//FontFaceName 12 Bold
	static BOOL ParseFont(LPCTSTR lpszFont, LPTSTR lpszFaceNameBuf, DWORD cchBufLen, LPINT lpSize, LPBOOL lpBold, LPBOOL lpItalic);
	static BOOL ParseMargins(LPCTSTR lpszMargins, LPRECT lpMargins);	//X,X,X,X
	static BOOL ParseRect(LPCTSTR lpszMargins, LPRECT lpMargins);	//X,X,X,X
	static SIZE ParseSize(LPCTSTR lpszSize);	//X,X
	static POINT ParsePoint(LPCTSTR lpszPoint);	//X,X
	static BOOL ParseBool(LPCTSTR lpszBool);	//true or false
	static BOOL ParseBool(LPCTSTR lpszBool, BOOL bBoolDefault);	//true or false
	static LONG ParseResFileName(LPCTSTR lpszFileName, LPTSTR lpszBuf, DWORD cchBufSize);	//convert AA\BB.bmp to AA_BB_BMP
	static int ParseTypedInt(LPCTSTR lpszTypedString);

	static LPCTSTR GetNextPart(LPCTSTR lpszString, TCHAR chSeparator);
	static LPCTSTR GetNextPart(LPCTSTR lpszString);	//Separated by [Space] or ,
	static DWORD CopyFirstPart(LPTSTR lpszBuf, LPCTSTR lpszString, DWORD dwMaxLen);		//Copy the first part of the string, terminated by [Space] or ,
	static DWORD CopyFirstPart(LPTSTR lpszBuf, LPCTSTR lpszString, DWORD dwMaxLen, TCHAR chSeparator);		//Copy the first part of the string, terminated by [Space] or ,

public:
	static DWORD GetResBitmapCoreHeader(LPVOID pResData, LPBITMAPINFO lpBMCH);	//return the offset of the bitmap data
	static SIZE GetBitmapSize(HBITMAP hBitmap, int nTotalFrame = 1, int iImageLayout = INI_VERTICAL);
	static void SizeAbs(SIZE *lpSize);	//abs(size.cx), abs(size.cy)
	static void PointAbs(POINT *lpPoint);	//abs(point.x), abs(point.y)
	static POINT CalcPositionFromOffset(SIZE sizeArea, POINT ptOffset, int iOffsetType);
	static BOOL IsEmptyMargins(LPCRECT lprcMargins);
	static int SetDCProperties(HDC hDC, COLORREF clrTextColor, HFONT hFont, int nBkMode = TRANSPARENT, COLORREF clrBkColor = RGB(255, 255, 255));
	static void RestoreDCProperties(HDC hDC, int iSavedDC);

protected:
	static CThemeHelper s_ThemeHelper;
#ifdef UNICODE
	struct _CNoCaseLess
	{
		bool operator()(const wstring& str1, const wstring& str2) const
		{	return _tcsicmp(str1.c_str(), str2.c_str()) < 0;	}
	};
	typedef map<wstring, int, _CNoCaseLess> TYPEDINTMAP;
	TYPEDINTMAP m_mapTypedInt;
#else
	struct _CNoCaseLess
	{
		bool operator()(const string& str1, const string& str2) const
		{	return _tcsicmp(str1.c_str(), str2.c_str()) < 0;	}
	};
	typedef map<string, int, _CNoCaseLess> TYPEDINTMAP;
	TYPEDINTMAP m_mapTypedInt;
#endif

};
