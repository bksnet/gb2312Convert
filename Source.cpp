//#include <stringapiset.h>
//
//int main() {
//	char* gbBuffer;
//	WCHAR* pOut;
//	MultiByteToWideChar(936, MB_PRECOMPOSED, gbBuffer, 10, pOut, 0);
//}
//template<class charT, class trailT>

// write.cpp -- using cout.write()
//#include <iostream>
//#include <cstring>

//int main() {
//	using std::cout;
//	using std::endl;
//	const char* state1 = "Florida";
//	const char* state2 = "Kansas";
//	const char* state3 = "Euphoria";
//	int len = std::strlen(state2);
//	cout << "Increasing loop index: \n";
//	int i;
//	for (i = 1; i <= len; i++) {
//		cout.write(state2, i);
//		cout << endl;
//	}
//
//	//concatenate output
//	cout << "Decreasing loop index: \n";
//	for (i = len; i > 0; i--)
//		cout.write(state2, i) << endl;
//
//	//exceed string length
//	cout << "Exceeding string length: \n";
//	cout.write(state2, len + 5) << endl;
//
//	long val = 560031841;
//	cout.write((char*)&val, sizeof(long));
//
//	return 0;
//}

//int main() {
//	float i = 4.6;
//	std::cout.setf(std::ios_base::scientific);
//	std::cout << i << std::endl;
//	std::cout << i;
//	return 0;	
//

//cinexcp.cpp -- having cin throw an exception
//#include <iostream>
//#include <exception>

//int main() {
//	using namespace std;
//	// have failbit cause an exception to be thrown
//	cin.exceptions(ios_base::failbit);
//	cout << "Enter numbers: ";
//	int sum = 0;
//	int input;
//	try {
//		while (cin >> input) {
//			sum += input;
//		}
//	}
//	catch (ios_base::failure& bf) {
//		cout << bf.what() << endl;
//		cout << "O! the horror!\n";
//	}
//
//	cout << "Last value entered = " << input << endl;
//	cout << "Sum = " << sum << endl;
//	return 0;
//}
#include <string>
#include <iostream>


int main(int argc, char* argv[]) {
	void fileOperation(int mode);
	void filePathTest();
	int convertExem();

	//define the mode of calls of fileOperation;
	//0 present normal mode,you need specify both sorce and target file.
	//1 present writeover mode, source file will be writed over.
	int mode = 0;   

	if (argc == 2) {
		std::string parameter = argv[1];
		if (parameter == "/o") {
			mode = 1;
		}
		else {
			std::cout << "Error parameter!" << std::endl;
			exit(EXIT_FAILURE);
		}
	} else if (argc == 1) {
		mode = 0;
	}
	else {
		std::cout << "Error parameter!" << std::endl;
	}
	fileOperation(mode);
//	filePathTest();
	//convertExem();

	return 0;
}