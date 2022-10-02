#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "ts_api.h"
using namespace std;

class base
{
public:
	virtual void vf1()
	{
		cout << typeid(*this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int64_t x = 3;
	int32_t a = 1;
};
class Device : public base
{
public:
	virtual void vf1()
	{
		cout << typeid(*this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int32_t b = 2;

	int64_t y = 4;
};

namespace Virtual {
	class vbase
	{
	public:
		virtual void vf1() {
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vf2()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		int32_t a = 1;
		int64_t x = 2;
	};
	class vDeviceA : public virtual vbase
	{
	public:
		int32_t Ab = 3;
		int64_t Ay = 4;
		virtual void vfa()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
	};
	class vDeviceB : public virtual vbase
	{
	public:

		int32_t Bb = 5;
		int64_t By = 6;
	
	};
	class vDeviceC : public virtual vbase
	{
	public:
		int32_t Bb = 7;
		int64_t By = 8;
		virtual void vf2()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vfC()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
	};
	class vvDevice : public  vDeviceB, public vDeviceC, public vDeviceA
	{
	public:

		int32_t zb = 9;
		int64_t zy = 10;
		//如果定义了新的虚函数，则编译器为其生成一个虚函数指针（vptr）以及一张虚函数表。该vptr位于对象内存最前面 win系统
		virtual void vf1()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vf3()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vf4()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
	};
}
namespace NoV {
	class vbase
	{
	public:
		virtual void vf1() {
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vf2()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		int32_t a = 1;
		int64_t x = 2;
	};
	class vDeviceA : public  vbase
	{
	public:
		int32_t Ab = 3;
		int64_t Ay = 4;
	};
	class vDeviceB : public  vbase
	{
		int32_t Bb = 5;
		int64_t By = 6;
	};
	class vDeviceC : public  vbase
	{
	public:
		int32_t Bb = 7;
		int64_t By = 8;
		virtual void vf2()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
	};
	class vvDevice : public vDeviceB, public vDeviceA, public vDeviceC
	{
	public:
		virtual void vf1()
		{

			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		int32_t zb = 9;
		int64_t zy = 10;
		//如果定义了新的虚函数，则编译器为其生成一个虚函数指针（vptr）以及一张虚函数表。该vptr位于对象内存最前面 win系统
		virtual void vf3()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vf4()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
	};
};
class testA
{
public:
	int64_t x = 3;
	int32_t a = 0;
};
class testB
{
public:
	testA c;
	int32_t b = 2;
	int64_t y = 4;
};

void testv();
void testnv();

int main()
{
	//testv();
	testnv();

	return 0;
}



void testv()
{

	using namespace Virtual;

	d_cout(sizeof(testA));
	d_cout(sizeof(testB));
	PrintType(testB());

	d_cout(sizeof(Device));
	PrintType(Device());
	testB b;
	Device d;
	// linux下类继承和直接类作为成员大小不太一样。。。
	d_cout(((char *)&b.b - (char *)&b.c.x));
	d_cout(((char *)&d.b - (char *)&d.x));

	d_cout(sizeof(vDeviceA));
	PrintType(vDeviceA());
	//多重继承，分别按照继承顺序设置变量，最后一个继承类数据和本类合并，如果是虚拟继承，最后是虚基类
	d_cout(sizeof(vvDevice));
	PrintType(vvDevice());
	vvDevice  vd;
	int64_t* pvd = reinterpret_cast<int64_t*>(&vd);


#ifdef WIN32
	//距离头部的偏移地址 //x86 x64都是int32_t
	d_cout(*reinterpret_cast<int64_t*>(*(pvd + 1)));
	//+1是当前地址偏移量 这个偏移量指针无论是x64 还是x86都是Int32
	int dataAddr = *(reinterpret_cast<int32_t*>(*(pvd + 1)));
	d_cout(dataAddr);
	//偏移过去应该是这个类的虚函数表
	char *phead = reinterpret_cast<char*>(pvd+1);
	//这2个地址一样 
	printf("reinterpret_cast<int64_t*>(phead + dataAddr) = %p\n", reinterpret_cast<int64_t*>(phead + dataAddr));
	printAddrFunc(pvd,3); //如果有继承的类有新虚函数 或者子类有新虚函数表  
	//printAddrFunc(pvd+7);

	//偏移过去应该是虚基表
	dataAddr = *(reinterpret_cast<int32_t*>(*(pvd + 1))+1);
	d_cout(dataAddr);
	phead = reinterpret_cast<char*>(pvd + 1);
	//这2个地址一样 
	printf("reinterpret_cast<int64_t*>(phead + dataAddr) = %p\n", reinterpret_cast<int64_t*>(phead + dataAddr));
	//虚函数表在这个位置 也就是虚基类数据的前面，本类数据的最后面
	printAddrFunc(pvd + 13, 2);

	//也可以打印一下vfa 4=2(vptr+vbptr)+2(数据)
	printAddrFunc(pvd + 4, 1);

#endif // WIN32

}

void testnv()
{

	using namespace NoV;

	d_cout(sizeof(testA));
	d_cout(sizeof(testB));
	PrintType(testB());

	d_cout(sizeof(Device));
	PrintType(Device());
	testB b;
	Device d;
	// linux下类继承和直接类作为成员大小不太一样。。。
	d_cout(((char *)&b.b - (char *)&b.c.x));
	d_cout(((char *)&d.b - (char *)&d.x));

	d_cout(sizeof(vDeviceA));
	PrintType(vDeviceA());
	//多重继承，分别按照继承顺序设置变量，最后一个继承类数据和本类合并，如果是虚拟继承，最后是虚基类
	d_cout(sizeof(vvDevice));
	PrintType(vvDevice());
	vvDevice  vd;
	int64_t* pvd = reinterpret_cast<int64_t*>(&vd);
	//虚函数表在这个位置 非虚继承时，派生类新的虚函数直接扩展在基类虚函数表的下面 
	printAddrFunc(pvd,4); 
	d_cout(reinterpret_cast<int64_t*>(&vd.Ab));

}