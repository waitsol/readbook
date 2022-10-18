#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "ts_api.h"
using namespace std;
// g++ -fdump-lang-class 3.cpp  -I../include/
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

namespace Virtual
{
	class vbase
	{
	public:
		virtual void vf1()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vf2()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
#ifndef WIN32
		virtual void vfBase()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
#endif
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
#ifndef WIN32
		virtual void vfB()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
#endif
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
	class vvDevice : public vDeviceB, public vDeviceC, public vDeviceA
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
namespace NoV
{
	class vbase
	{
	public:
		virtual void vf1()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
		virtual void vf2()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
#ifndef WIN32
		virtual void vfBase()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
#endif
		int32_t a = 1;
		int64_t x = 2;
	};
	class vDeviceA : public  vbase
	{
	public:
		int32_t Ab = 3;
		int64_t Ay = 4;
		virtual void vfa()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
	};
	class vDeviceB : public  vbase
	{
	public:
		int32_t Bb = 5;
		int64_t By = 6;
#ifndef WIN32
		virtual void vfB()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
#endif
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
		virtual void vfC()
		{
			cout << typeid(this).name() << "  " << __func__ << " " << __LINE__ << endl;
		}
	};
	class vvDevice : public vDeviceB, public vDeviceC, public vDeviceA
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
class A
{
	int a;
	char b;
};
class AA : public A
{
	char c;
};
class AAA : public AA
{

	char d;
};
int main()
{
	d_cout(sizeof(A));
	d_cout(sizeof(AA));
	d_cout(sizeof(AAA));

	// testv();
	testv();

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
	vvDevice vd;
	int64_t *pvd = reinterpret_cast<int64_t *>(&vd);

#ifdef WIN32
	//距离头部的偏移地址 //x86 x64都是int32_t
	d_cout(*reinterpret_cast<int64_t *>(*(pvd + 1)));
	//+1是当前地址偏移量 这个偏移量指针无论是x64 还是x86都是Int32
	int dataAddr = *(reinterpret_cast<int32_t *>(*(pvd + 1)));
	d_cout(dataAddr);
	//偏移过去应该是这个类的虚函数表
	char *phead = reinterpret_cast<char *>(pvd + 1);
	//这2个地址一样
	printf("reinterpret_cast<int64_t*>(phead + dataAddr) = %p\n", reinterpret_cast<int64_t *>(phead + dataAddr));
	printAddrFunc(pvd, 3); //如果有继承的类有新虚函数 或者子类有新虚函数表
	// printAddrFunc(pvd+7);

	//偏移过去应该是虚基表
	dataAddr = *(reinterpret_cast<int32_t *>(*(pvd + 1)) + 1);
	d_cout(dataAddr);
	phead = reinterpret_cast<char *>(pvd + 1);
	//这2个地址一样
	printf("reinterpret_cast<int64_t*>(phead + dataAddr) = %p\n", reinterpret_cast<int64_t *>(phead + dataAddr));
	//虚函数表在这个位置 也就是虚基类数据的前面，本类数据的最后面
	printAddrFunc(pvd + 13, 2);

	//也可以打印一下vfa 4=2(vptr+vbptr)+2(数据)
	printAddrFunc(pvd + 4, 1);
#else
	// linux下第一个虚函数表是这个子类的表 和vb合并
	printAddrFunc(pvd, 4);
	// vc
	printAddrFunc(pvd + 3, 2);
	// vfa
	printAddrFunc(pvd + 6, 1);
	//段错误,虚函数没有重写不知道为什么4个表都找不到
	 //printAddrFunc(pvd +11, 1);
	//特殊打印 通过g++ -fdump-lang-class 3.cpp  -I../include/观看内存布局可以看到 vbase在下标2的地方
	_func *vptr = reinterpret_cast<_func *>(*static_cast<int64_t *>(pvd + 11));
	if (vptr != nullptr)
	{
		vptr[2]();
	}
	/*
	 *152   (int (*)(...))-88  -88是偏移 88/8=11
160   (int (*)(...))(& _ZTIN7Virtual8vvDeviceE)//重写了 这2个函数 但是不知道为什么运行这2个下标会code
168   (int (*)(...))Virtual::vvDevice::_ZTv0_n24_N7Virtual8vvDevice3vf1Ev //f1被vvDevice重写
176   (int (*)(...))Virtual::vDeviceC::_ZTv0_n32_N7Virtual8vDeviceC3vf2Ev//f2被重写 
184   (int (*)(...))Virtual::vbase::vfBase
	 */
#endif // WIN32
	//多重继承 base指针指向dev需要裁剪
	vDeviceA *pa = &vd;
	d_cout(reinterpret_cast<int64_t *>(pa) - pvd);
	vDeviceB *pb = &vd;
	d_cout(reinterpret_cast<int64_t *>(pb) - pvd);
	vDeviceC *pc = &vd;
	d_cout(reinterpret_cast<int64_t *>(pc) - pvd);
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
	vvDevice vd;
	int64_t *pvd = reinterpret_cast<int64_t *>(&vd);
#ifndef WIN32
	/*
	NoV::vvDevice::_ZTVN3NoV8vvDeviceE: 20 entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTIN3NoV8vvDeviceE)
16    (int (*)(...))NoV::vvDevice::vf1
24    (int (*)(...))NoV::vbase::vf2
32    (int (*)(...))NoV::vbase::vfBase
40    (int (*)(...))NoV::vDeviceB::vfB
48    (int (*)(...))NoV::vvDevice::vf3
56    (int (*)(...))NoV::vvDevice::vf4
64    (int (*)(...))-40
72    (int (*)(...))(& _ZTIN3NoV8vvDeviceE)
80    (int (*)(...))NoV::vvDevice::_ZThn40_N3NoV8vvDevice3vf1Ev//被重写了
88    (int (*)(...))NoV::vDeviceC::vf2
96    (int (*)(...))NoV::vbase::vfBase
104   (int (*)(...))NoV::vDeviceC::vfC
112   (int (*)(...))-80
120   (int (*)(...))(& _ZTIN3NoV8vvDeviceE)
128   (int (*)(...))NoV::vvDevice::_ZThn80_N3NoV8vvDevice3vf1Ev//被重写了
136   (int (*)(...))NoV::vbase::vf2
144   (int (*)(...))NoV::vbase::vfBase
152   (int (*)(...))NoV::vDeviceA::vfa
	*/
	printAddrFunc(pvd, 6); //打印看一下
	printAddrFunc(pvd + 5, 4);//不是虚继承打印被重写的 不core，，，
	printAddrFunc(pvd + 10, 4);

#endif
}