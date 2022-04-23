#include <filesystem>
#include <string>
#include <iostream>
#include <windows.h>

void filePathTest() {
	using namespace std;
	using namespace std::filesystem;

	path currentPath = filesystem::current_path();
	cout << currentPath.generic_string() << endl;

	char pathCstr[80];
	while (cin >> pathCstr) {
		path inputPath(pathCstr);

		if (inputPath.is_absolute()) {
			cout << pathCstr << " is a absolute path." << endl;
		}

		if (inputPath.is_relative()) {
			cout << pathCstr << " is a relative path." << endl;
		}

		cout << "root_name is: " << inputPath.root_name().string() << endl;
		cout << "root_directory is: " << inputPath.root_directory().string() << endl;
		cout << "root_path is: " << inputPath.root_path().string() << endl;
		cout << "relative_path is: " << inputPath.relative_path().string() << endl;
		cout << "parent_path is: " << inputPath.parent_path().string() << endl;
		cout << "extension is: " << inputPath.extension().string() << endl;

		if (exists(inputPath)) {
			cout << "you get the right path." << endl;
		}
		else {
			cout << "The file you typed is not existing.";
		}
	}
	return;
}