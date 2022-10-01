#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "ts_api.h"
using namespace std;
class base
{
	virtual void vf(){}
	int64_t x=3;
};
class Device : public  base
{
	int64_t y=4;
};
class vbase
{
	virtual void vf() {}
	int64_t x = 3;
};
class vDevice : public virtual vbase
{
	int64_t y = 4;
};
int main()
{
	d_cout(sizeof(Device));
	PrintType(Device());
	d_cout(sizeof(vDevice));
	PrintType(vDevice());
	return 0;
}