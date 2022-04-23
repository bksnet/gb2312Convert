
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <Windows.h>
//#include <debugapi.h>

inline void eatline() {
	while (getchar() != '\n') {
		continue;
	}
}

void fileOperation(int mode) {
	using namespace std;
	using namespace std::filesystem;

	
	
	string fileName;
	string targetFileName;

	// get file path and judge if file is existing.
	cout << "Enter name for new file" << endl;
	cin >> fileName;
	eatline();
	{
		size_t strSize = fileName.size();
		if (fileName.size() <= 0 || strSize >= 255) {
			cout << "Invaild input of file name.";
			exit(EXIT_FAILURE);
		}

		path filePath(fileName);
		if (!exists(fileName)) {
			//OutputDebugStringA("Failure file: ");
			//OutputDebugStringA(fileName.c_str());
			cout << "The file " << fileName << " is not existing.";
			exit(EXIT_FAILURE);
		}
	}

	// Set the target file.
	if (mode == 0) {
		cout << "Enter target file name: " << endl;
		cin >> targetFileName;
		eatline();
	}
	else if (mode == 1) {
		targetFileName = "temp";
	}

	size_t strSize = targetFileName.size();
	if (fileName.size() <= 0 || strSize >= 255) {
		cout << "Invaild input of file name.";
		exit(EXIT_FAILURE);
	}

	path targetFilePath(targetFileName);
	if (exists(targetFilePath)) {
		cout << "The target file is already exists." << endl;
		cout << "Do you want to continue? ";
		if (getchar() != 'y') {
			exit(EXIT_FAILURE);
		}
		else {
			while (getchar() != '\n') {
				continue;
			}
		}

	}

	ifstream sourceFile(fileName);
	if (!sourceFile.is_open()) {
		cout << "Can't open file " << fileName << endl;
		exit(EXIT_FAILURE);
	}
	//set input local;
	/*sourceFile.imbue(locale("zh_CN"));*/

	wofstream targetFile(targetFileName);
	if (!targetFile.is_open()) {
		cout << "Can't open file " << targetFileName << endl;
		exit(EXIT_FAILURE);
	}
	// It usefull to set the locale of ofstream which associate a file to output Chinese.
	targetFile.imbue(locale("en_US.utf8"));

	char sourceStr[255];
	wstring widechar;
	while (sourceFile.getline(sourceStr, 255)) {
		int charMount = strlen(sourceStr);
		sourceStr[charMount++] = '\n';
		sourceStr[charMount] = '\0';
		int requestSize = MultiByteToWideChar(936, MB_PRECOMPOSED, sourceStr, strlen(sourceStr), &widechar[0], 0);
		widechar.resize(requestSize); // Calculate request size and allocate space.

		MultiByteToWideChar(936, MB_PRECOMPOSED, sourceStr, strlen(sourceStr), &widechar[0], requestSize);
		cout << "The size of target string is: " << widechar.size() << endl;
		targetFile << widechar;
	}
	  

	//cout << targetFile.getloc().name().c_str() << endl;
	//cout << targetFile.rdstate() << endl;

	//wchar_t tempWideCharArr[] = L"好";

	// regardless the setting of locale, CMD always can't display Chinese correctly.
	//cout << "anything" << endl;
	//cout << "我可是中文" << endl;

	//cout.imbue(locale("en_US.utf8"));
	//cout << "anything" << endl;
	//cout << "我可是中文" << endl;

	// verify the fault reason.
	//targetFile << tempWideCharArr << endl;
	//cout << targetFile.rdstate() << endl;
	//cout << "Is EOF? " << targetFile.eof();
	//cout << "Is fail? " << targetFile.fail();
	//cout << "Is bad? " << targetFile.bad();

	//targetFile << L"That's strange." << endl;
	
	targetFile.close();
	targetFile.clear();

	sourceFile.close();
	sourceFile.clear();
	

	/*ofstream fout(fileName);
	fout << "It's written by fileIO application.";
	fout.close();

	ifstream fin(fileName);
	
	if (!(fin.is_open())) {
		cout << "Can't open file.";
		exit(EXIT_FAILURE);
	}

	char tempCharArr[80];

	while (fin.getline(tempCharArr, 80)) {
		cout << tempCharArr;
	}

	if (fin.eof()) {
		cout << "File end!";
	}

	fin.close();

	return;*/

	if (mode == 1) {
		try {
			remove(fileName);
		}
		catch (exception e) {
			cout << "Fail to delect file." << e.what() << endl;
			exit(EXIT_FAILURE);
		}
		try {
			rename(targetFileName, fileName);
		}
		catch (exception e) {
			cout << "Fail to rename file." << endl;
			exit(EXIT_FAILURE);
		}
	}

}
// ifstream.fail(): if iostate was setted.
// !ifstream: as well as ifstream.fail().
// ifstream.is_open(): check did the file openned correctly.