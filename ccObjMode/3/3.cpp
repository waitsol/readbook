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
	int32_t b = 2;

	int64_t y = 4;
};
class vbase
{
public:
	virtual void vf1() {
		cout << typeid(*this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	virtual void vf2()
	{
		cout << typeid(*this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int32_t a = 1;
	int64_t x = 2;
};
class vDeviceA : public virtual vbase
{
	int32_t Ab = 3;
	int64_t Ay = 4;
};
class vDeviceB : public virtual vbase
{
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
		cout << typeid(*this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
};
class vvDevice : public vDeviceB, public vDeviceA, public vDeviceC
{
public:
	virtual void vf1()
	{
		cout << typeid(*this).name() << "  " << __func__ << " " << __LINE__ << endl;
	}
	int32_t zb = 9;
	int64_t zy = 10;
	virtual void vf3()
	{
		cout << typeid(*this).name()<<"  "<<__func__<<" "<<__LINE__<< endl;
	}
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
int main()
{
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
	int64_t* pvd=reinterpret_cast<int64_t*>(&vd);
	//虚函数表在这个位置 也就是虚基类数据的前面，本类数据的最后面
	printAddrFunc(pvd+11);


	return 0;
}