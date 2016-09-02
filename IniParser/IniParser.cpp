// IniParser.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ParseIni.h"

#include <iostream>


int main()
{
	STLSTRING testFile = _T("../Test/test1.ini");
	CParseIni parser;
	wcout << "Now parsing " << testFile << endl;
	//LoadFromFile first load the whole file into memory, then parse the text in memory
	BOOL success = parser.LoadFromFile(testFile.c_str());

	cout << "Parse result : " << (success > 0) << endl;
	if (success) {
		cout << "   Parts(Sections), including the hidden 'ROOT' node : " << parser.GetPartCount() << endl;
		CParseIni::POSITION pos = parser.GetFirstPartPos();
		CIniPart *part = NULL;
		while (part = parser.GetNextPart(pos)) {
			wcout << "        " << part->GetPartName() << endl;

			CIniPart::POSITION posValue = part->GetFirstKeyValuePos();
			LPCTSTR pszKey = NULL;
			LPCTSTR pszValue = NULL;
			while (part->GetNextKeyValue(posValue, pszKey, pszValue)) {
				wcout << "           " << pszKey << "=" << pszValue << endl;
			}
		}
	}
	cout << endl;
	cout << "You can also get the value directly:" << endl;
	wcout << "  LsfSharpen.Step=" << parser[_T("LsfSharpen")][_T("Step")].ToDouble() << endl;
	wcout << "  Domain.Domain0=" << (LPCTSTR)parser[_T("Domain")][_T("Domain0")] << endl;

    return 0;
}

