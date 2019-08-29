#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
int main()
{
	int  a, b;
	while(cin >> a >> b) {
		if(a < 1 || a>9 || b < 1 || b>100)
			continue;

		std::vector<int> arr;
		arr.resize(b+1);
		arr[b] = -1;

		unsigned long long sum = 0;
		for(int i = 0; i < b; ++i) {
			long cur = a *(b - i);

			sum += cur;

			if(sum < 10)
				arr[i] = sum;
			else
				arr[i] = sum % 10;

			sum = (sum - arr[i]) / 10;
		}
		if(sum > 0)
			arr[b] = sum;

		for(int i =arr.size()-1; i>=0; --i) {
			if(arr[i] >=0)
				cout << arr[i];
		}
		cout << endl;
	}

	return 0;
}