#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "ts_api.h"
using namespace std;

class NRV {
public:
	friend NRV foo(double val);
	NRV() {
		memset(arr, 0, sizeof(double) * 100);
	}
//	NRV(const NRV& r) {		memcpy(this, &r, sizeof(r));	}
	double arr[100];
};
NRV foo(double val)
{
	NRV l;
	l.arr[0] = val;
	l.arr[1] = val;
	return l;
}


void testNRV()
{
	ptime();
	for (int i = 0; i < 10000 * 100; i++)
	{
		NRV l = foo(3.3);
	}
	ptime();

}

int main(int argc,char * argv[])
{
	testNRV(); 

	return 0;
}
