
#pragma once

#include "ParseHelper.h"


#include <wtypes.h>
#include <tchar.h>

#pragma warning(disable:4786)
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// CParseIni

#define INI_STATUS_START			0
#define INI_STATUS_SECTION			1
#define INI_STATUS_PREKEY			2
#define INI_STATUS_KEY				3
#define INI_STATUS_PREVALUE		4
#define INI_STATUS_VALUE			5
#define INI_STATUS_COMMENT			6
#define INI_STATUS_DBCS_FIRSTPART	10

#define INI_ROOTSECTION_NAME		_T("_ROOT_")

class CParseIni
{
public:
	CParseIni();
	virtual ~CParseIni();

	friend class CIniPart;

#ifdef UNICODE
	struct _CNoCaseLess
	{
		bool operator()(const wstring& str1, const wstring& str2) const
		{	return _tcsicmp(str1.c_str(), str2.c_str()) < 0;	}
	};
	typedef map <wstring, CIniPart*, _CNoCaseLess> INIPARTMAP;
	typedef map <wstring, CIniPart*, _CNoCaseLess>::iterator POSITION;
	INIPARTMAP m_mapIniParts;
#else
	struct _CNoCaseLess
	{
		bool operator()(const string& str1, const string& str2) const
		{	return _tcsicmp(str1.c_str(), str2.c_str()) < 0;	}
	};
	typedef map <string, CIniPart*, _CNoCaseLess> INIPARTMAP;
	typedef map <string, CIniPart*, _CNoCaseLess>::iterator POSITION;
	INIPARTMAP m_mapIniParts;
#endif

public:
#ifdef UNICODE
	typedef vector <wstring> STRINGVECTOR;
#else
	typedef vector <string> STRINGVECTOR;
#endif

	
public:
	void Clear();
	BOOL LoadFromFile(LPCTSTR lpszFilePathName);
	BOOL WriteToFile(LPCTSTR lpszFilePathName);

	BOOL LoadFromStringW(LPCWSTR lpszString);
	BOOL LoadFromStringA(LPCSTR lpszString);
	LONG LoadFromString(LPCTSTR lpszString, UINT cchKeyBufferLen = 512, UINT cchValueBufferLen = 2048);

	CIniPart& operator[](LPCTSTR lpszPartName);

	//Navigate
	POSITION GetFirstPartPos();
	CIniPart* GetNextPart(POSITION &pos);

	LONG GetPartCount();
	CIniPart* FindPart(LPCTSTR lpszPartName);
	CIniPart* CreatePart(LPCTSTR lpszPartName);

	LONG GetPartNamesLeadWith(LPCTSTR lpszLead, STRINGVECTOR *pStringVector, BOOL bClear = TRUE);
	BOOL IsPartExists(LPCTSTR lpszPartName);

};

//////////////////////////////////////////////////////////////////////////
// CIniPartValue

class CIniPartValue
{
public:
	CIniPartValue();
	CIniPartValue(LPCTSTR lpszValue);
	CIniPartValue(const CIniPartValue& val);
	virtual ~CIniPartValue();

	friend class CIniPart;

protected:
	CIniPart *m_pPart;
#ifdef UNICODE
	wstring m_strValue;
	wstring m_strResFileNameTemp;
#else
	string m_strValue;
	string m_strResFileNameTemp;
#endif
	RECT m_rcRectTemp;
	RECT m_rcMarginsTemp;
	LOGFONT m_LogFontTemp;
	
public:
	CIniPartValue& operator =(const CIniPartValue& val);
	operator LPCTSTR();
	void SetValue(LPCTSTR lpszValue);
	LPCTSTR GetValueRef();

public:
	int ToInt();
	int ToInt(int iDefault);
	INT32 ToInt32();
	INT32 ToInt32(INT32 iDefault);
	double ToDouble();
	double ToDouble(double fDefault);
	SIZE ToSize();
	POINT ToPoint();
	LPCTSTR ToString();
	COLORREF ToColor(COLORREF clrDefault);
	COLORREF ToColor();
	BOOL ToBool();
	BOOL ToBool(BOOL bBoolDefault);
	LPCTSTR ToResFileNameRef();
	LPLOGFONT ToFontRef();
	LPCRECT ToRectRef();
	LPCRECT ToMarginsRef();

	BOOL ToRect(LPRECT lprcRect);
	BOOL ToMargins(LPRECT lprcRect);
	BOOL ToFont(LPLOGFONT lpLogFont);
	BOOL ToFont(LPTSTR lpszFaceNameBuf, DWORD cchBufLen, LPINT lpSize, LPBOOL lpBold, LPBOOL lpItalic);
	BOOL ToResFileName(LPTSTR lpszBuf, LONG cchBufLen);

};


//////////////////////////////////////////////////////////////////////////
// CIniPart

class CIniPart
{
public:
	CIniPart(LPCTSTR lpszPartName, CParseIni *pProfile, LONG iPartIndex);
	virtual ~CIniPart();

	friend class CParseIni;

#ifdef UNICODE
	typedef map <wstring, CIniPartValue*, CParseIni::_CNoCaseLess> PARTVALUEMAP;
	typedef map <wstring, CIniPartValue*, CParseIni::_CNoCaseLess>::iterator POSITION;
#else
	typedef map <string, CIniPartValue*, CParseIni::_CNoCaseLess> PARTVALUEMAP;
	typedef map <string, CIniPartValue*, CParseIni::_CNoCaseLess>::iterator POSITION;
#endif

protected:

	CParseIni *m_pProfile;
	LONG m_iPartIndex;

#ifdef UNICODE
	PARTVALUEMAP m_mapPartValues;
	wstring m_strPartName;
#else
	PARTVALUEMAP m_mapPartValues;
	string m_strPartName;
#endif
	CIniPartValue m_valEmpty;

private:
	BOOL WriteFile(HANDLE hFile);

public:
	void Clear();

	LONG GetPartIndex();
	LPCTSTR GetPartName();
	void SetValue(LPCTSTR lpszKey, LPCTSTR lpszValue);
	LONG GetKeyCount();
	BOOL DeleteKey(LPCTSTR lpszKeyName);
	CIniPartValue& operator[](LPCTSTR lpszKey);
	BOOL IsValueExists(LPCTSTR lpszKey);

	//Navigate
	POSITION GetFirstKeyValuePos();
	BOOL GetNextKeyValue(POSITION &pos, LPCTSTR &lpszrKey, LPCTSTR &lpszrValue);

	LONG GetValueString(LPCTSTR lpszKeyName, LPTSTR lpszBuf, LONG cchBufLen, LPCTSTR lpszDefault = _T(""));
	LPCTSTR GetValueString(LPCTSTR lpszKeyName);
	LONG GetValueInt(LPCTSTR lpszKeyName);
	SIZE GetValueSize(LPCTSTR lpszKeyName);
	POINT GetValuePoint(LPCTSTR lpszKeyName);
	BOOL GetValueRect(LPCTSTR lpszKeyName, LPRECT lprcRect);
	BOOL GetValueMargins(LPCTSTR lpszKeyName, LPRECT lprcRect);
	BOOL GetValueFont(LPCTSTR lpszKeyName, LPLOGFONT lpLogFont);
	BOOL GetValueFont(LPCTSTR lpszKeyName, LPTSTR lpszFaceNameBuf, DWORD cchBufLen, LPINT lpSize, LPBOOL lpBold, LPBOOL lpItalic);
	COLORREF GetValueColor(LPCTSTR lpszKeyName);
	LONG GetValueResFileName(LPCTSTR lpszKeyName, LPTSTR lpszBuf, LONG cchBufLen);
	BOOL GetValueBool(LPCTSTR lpszKeyName);
};
