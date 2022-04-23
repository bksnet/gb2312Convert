#include <iostream>
#include <stdio.h>
#include <Windows.h>
using namespace std;

string UrlUTF8(char* str);
void GB2312ToUTF_8(string& pOut, char* pText, int pLen);
void Gb2312ToUnicode(WCHAR* pOut, char* pText);
void UnicodeToUTF_8(char* pOut, WCHAR* pText);


string UrlUTF8(char* str)
{
	string tt;
	string dd;
	GB2312ToUTF_8(tt, str, strlen(str));

	int len = tt.length();
	for (int i = 0; i < len; i++) {
		if (isalnum((BYTE)tt.at(i))) {
			char tempbuff[2] = { 0 };
			sprintf_s(tempbuff, "%c", (BYTE)tt.at(i));
			dd.append(tempbuff);
		}
		else if (isspace((BYTE)tt.at(i))) {
			dd.append("+");
		}
		else {
			char tempbuff[4];
			sprintf_s(tempbuff, "%%%x%x", ((BYTE)tt.at(i)) >> 4);
			dd.append(tempbuff);
		}
	}

	return dd;
	
}

void GB2312ToUTF_8(string& pOut, char* pText, int pLen)
{
	char buf[4];
	memset(buf, 0, 4); //get 4 bytes space and clean.

	pOut.clear();

	int i = 0;
	while (i < pLen) {
		//if the byte start by a 0(positive value),that meaning it's a ASCII value.
		if (pText[i] >= 0) {
			char asciistr[2] = { 0 };
			asciistr[0] = (pText[i++]); // place the ascii value in the low byte of a double byte space.
			pOut.append(asciistr); // Append result to the result string.
		}
		else {
			WCHAR pbuffer;
			//pass start address of a double byte. and covert to widechar(double).
			Gb2312ToUnicode(&pbuffer, pText + i); 
			UnicodeToUTF_8(buf, &pbuffer); //convert to utf8(three bytes).
			
			pOut.append(buf);

			//It's means that the Gb2312 character is two bytes
			//and wide char use two bytes too.
			//and UTF-8 of of a chinese charactor occupy three bytes.
			//but it append four bytes to utf-8 string, or no?

			i += 2;

		}
	}

	return;

}

void Gb2312ToUnicode(WCHAR* pOut, char* gbBuffer) {
	::MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, gbBuffer, 2, pOut, 1);
	return;
}

void UnicodeToUTF_8(char* pOut, WCHAR* pText) {
	char* pchar = (char*)pText;
}

int convertExem() {
	char str[] = "测试";
	string utf8Code = "";
	utf8Code = UrlUTF8(str);
	char code[1024];
	strcpy_s(code, utf8Code.c_str());
	for (int i = 0; i < utf8Code.length(); i++) {
		printf("%c", code[i]);
	}

	getchar();
	return 0;

}