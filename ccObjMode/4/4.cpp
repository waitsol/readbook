#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "ts_api.h"
using namespace std;

class base1
{
public:
	virtual void vfb1()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	virtual void vfb2()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int64_t x = 1;
	int64_t a = 2;
};
class base2
{
public:
	virtual void vfb21()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	virtual void vfb22()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int64_t xx = 3;
	int64_t aaa = 4;
};
class Device : public base1,public base2
{
public:
	virtual void vfd1()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}

	virtual void vfb1()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	virtual void vfb22()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int64_t b = 5;

	int64_t y = 6;
};

int main()
{
	Device d;
	d_cout(sizeof(d));
	int64_t* pd = reinterpret_cast<int64_t*> (&d);
	PrintType(d);
#ifdef  WIN32
	printAddrFunc(pd, 3); //win下合linux存储不一样
	printAddrFunc(pd+3, 2);
#else
	printAddrFunc(pd, 4);
	printAddrFunc(pd + 3, 2);
	//test func
	base2 *pb2=&d;
	//true
	d_cout(reinterpret_cast<char *>(pb2) == reinterpret_cast<char *>(&d)+sizeof(base1))
	pb2->vfb22();
#endif //  WIN32

	printf("%p\n",(&base1::x));
	printf("%p\n", (&base1::a));

	return 0;
}

