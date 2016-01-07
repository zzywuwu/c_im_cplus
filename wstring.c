#include <string>
#include <iostream>
#include <locale>
#include <codecvt>
#include <stdio.h>
#include <stdlib.h>
#include <cstdint>
using namespace std;
int main(int argc, char *argv[])
{
	
	std::wstring str = L"中国人";
	std::wstring_convert<codedvt<wchar_t, char, mbstate_t> >
	converter(new codedvt<wchar_t, char, mstate_t>("CHS"));
	string narrowStr = converter.to_bytes(str);
	wstring wstr = converter.from_bytes(narrowStr);
	cout << narrowStr << endl;
	wcout.imbue(locale("chs"));
	wcout << wstr << endl;
	
	#if 0
    const wchar_t* aa = L"姓名";
	setlocale(LC_ALL, "zh_CN.UTF-8");
	//wprintf(L"%ls\n",aa);
	//wcout << aa << endl;
	
	
	wstring ws = L"你好abc";
   	//wcout << ws << endl;
	//wprintf(L"%ls\n",ws.c_str());
	wcout << ws.length() << endl;
	
	wstring wstr(aa);
	
	wcout << wstr << endl;
	//wprintf(L"%ls\n",wstr.c_str());
	wcout << wstr.size() << endl;
	#endif
 
    return 0;
}
