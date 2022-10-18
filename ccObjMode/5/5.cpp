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
	base1()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;

		vfb1();
		printAddrFunc(reinterpret_cast<int64_t *>(this), 2);
	}
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
	~base1()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
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
	~base2()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
};
class Device : public base1, public base2
{
public:
	Device()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;

		vfb1();
#ifndef WIN32

		printAddrFunc(reinterpret_cast<int64_t *>(this), 4);
#endif // !WIN32

	}
	virtual void vfd1()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}

	virtual void vfb1()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		d_cout(x);
		d_cout(xx);
		d_cout(a);
		d_cout(aaa);
		d_cout(b);
		d_cout(y);
	}
	virtual void vfb22()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int64_t b = 5;

	int64_t y = 6;
};
class Testxg
{
public:
	~Testxg()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		//然后编译器析构b2 b1
	}

private:
	base1 b1;
	base2 b2;
};
class TestCD
{
public:
	TestCD() : x(1)
	{
		if (idx == 30)
		{
			throw;
		}
		idx++;
		cout << "TestCD construction " << idx << endl;
	}
	virtual ~TestCD()
	{
		cout << "~TestCD deconstruction " << endl;
	}
	static int idx;
	int x;
};
class DeviceCD : public TestCD
{
public:
	DeviceCD() : y(0) {}
	~DeviceCD()
	{
		cout << "~DeviceCD deconstruction " << endl;
	}
	int y;
};
int TestCD::idx = 0;

class LiveTime
{
public:
	~LiveTime()
	{
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << ":" << x << endl;
	}
	LiveTime(int _x) : x(_x) {}

	LiveTime operator+(const LiveTime &r)
	{
		LiveTime t = *this;
		cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		t.x += r.x;
		return t;
	}
	operator int()
	{
		return 1;
	}
	int x;
};
void testLiveTime(int x)
{
	cout << __func__ << " " << __LINE__ << endl;
}

void foo(double)
{
	cout << __func__ << " " << __LINE__ << endl;
}
void foo(int)
{
	cout << __func__ << " " << __LINE__ << endl;
}

template <class T>
class temClas
{
public:
	T val;
	void run()
	{
		foo(val);
	}
};

int main()
{
	
	{
		Device d;
		Testxg _;
		PrintType(d);
		//先析构_
	}
	try
	{
		TestCD *arr = new TestCD[3];
		delete[] arr;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	try
	{
		TestCD *arr = new DeviceCD[3];

		delete[] arr;
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
	}
	// cout<<endl;
	// {
	// 	char *p = new char[sizeof(base1)];
	// 	base1 *pb= new(p)Device;
	// 	pb->vfb1();
	// }

	LiveTime a = 1, b = 2;
	testLiveTime(a + b);
	{

		temClas<int> t;
		t.run();
	}
	{
		temClas<double> t;
		t.run();
	}

	return 0;
}
