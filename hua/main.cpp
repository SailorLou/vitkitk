

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

bool checkNumber(char value)
{
	if(value >= '0' &&value <= '9')
		return true;

	return false;

}

bool checkSign(char value)
{
	return value == '+' || value == '-';
}

bool checkPoint(char value)
{
	return value == '.';
}


int  main()
{
	string inputStr;
	while(getline(cin, inputStr)) {

		if(inputStr.empty())
			continue;

		int numberBegin = 0;
		int subCount = 0;
		int  beginPoint = 0;
		bool newSubBegin = false;
		//bool hasSign = false;
		bool hasPoint = false;
		string maxString;

		auto replaceFun = [&]() {
			string temp = inputStr.substr(numberBegin, subCount);
			if(subCount >= maxString.length()) {
				maxString = temp;
				numberBegin = 0;
				subCount = 0;
				newSubBegin = false;
				beginPoint = 0;
			}
		};

		for(int i = 0; i < inputStr.length(); ++i) {
			if(checkSign(inputStr[i])) {
				if(newSubBegin) {
					if(checkSign(inputStr[i - 1])) {
						numberBegin = i;
						subCount = 1;
					} else {
						replaceFun();
					}

				} else {
					newSubBegin = true;
					numberBegin = i;
					subCount++;
				}
			} else if(checkNumber(inputStr[i])) {
				subCount++;
				if(!newSubBegin) {
					newSubBegin = true;
					numberBegin = i;
				}
			} else if(checkPoint(inputStr[i])) {
				if(!newSubBegin)
					continue;

				if(checkNumber(inputStr[i - 1]) && (i + 1 < inputStr.length()) && checkNumber(inputStr[i + 1])) {
					if(!hasPoint) {
						subCount++;
						hasPoint = true;
						beginPoint = i;
					} else {
						string temp = inputStr.substr(numberBegin, subCount);
						if(subCount >= maxString.length()) {
							maxString = temp;
						}

						numberBegin = beginPoint+1;
						subCount = i- beginPoint-1;
						newSubBegin = true;
					}

				} else {
					if(hasPoint) {
						replaceFun();
					} else {
						if(newSubBegin) {
							string temp = inputStr.substr(numberBegin, subCount);
							if(subCount >= maxString.length()) {
								maxString = temp;

							}

							numberBegin = 0;
							subCount = 0;
							newSubBegin = false;
						}
					}
				}
			} else {
				if(!newSubBegin)
					continue;

				replaceFun();
			}
		}

		if(newSubBegin) {
			string temp = inputStr.substr(numberBegin, subCount);
			if(!(checkPoint(temp.back()) || checkSign(temp.back()))) {
				if(subCount >= maxString.length()) {
					maxString = temp;
					numberBegin = 0;
					subCount = 0;
					newSubBegin = false;
				}
			}
		}

		std::cout << maxString << endl;
	}

	return 0;
}