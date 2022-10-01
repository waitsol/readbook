#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include "ts_api.h"
using namespace std;

int main(int argc,char * argv[])
{




	{
		//数值运算的巧妙之处
		int16_t a = 1 << 15;//-32768
		cout << a << endl;
		int16_t fa = -1;
		//猜猜是几 潜意识是32768   因为有符号32768也等于-32768
		int16_t b = 0 - a;// 0+ 1000 0000 
		cout << b << endl;

		int16_t c = a * fa;//a* (1<<16-1) =0- -a=    (-1==1<<16-1=0xffff )
		cout << c << endl;
		int16_t d = a / fa;
		cout << d << endl;

		{
			uint32_t fa = -1;
			uint32_t a = 1;
			a <<= 31;
			cout << fa << endl;
			uint32_t b = a / fa; 
			uint32_t d = a * -1;
			cout << a << endl;
			cout << b << endl;
			cout << d << endl;



		}

	}
	

	int x = 0x01234567;
	char *p = (char*)&x;
	
	for (int i = 0; i < 4; i++)
		cout << hex << (int)p[i];
	cout << endl;
	toBig(p, 4);
	for (int i = 0; i < 4; i++)
		cout << hex << (int)p[i];

#if 0
	//2.1.3大小端
	{
		//大端 高地址对高有效位 0x100 01   0x101 23 0x102 45 0x103 67
		//小段地址存储数据相反 我们取开头地址查看即可 即地址转char* 查看0x100数据
		int x = 0x1234567;
		char *px = (char*)&x;
		cout << hex << (*px & 0xff) << endl;
		cout << hex << (int)px[0] << endl;
		cout << hex << (int)px[3] << endl;
		if (*px == 0x01)
		{
			cout << "大端" << endl;
		}
		else
		{
			cout << "小端" << endl;
		}


	}
#endif
#if 0
	{
		int x = 12345;
		char *px = (char*)&x;
		cout << hex << (*px & 0xff) << endl;

		for (int i = 0; i < 4; i++)
			printf("%.2x", px[i]);
		cout << endl;
		float fx = x;

		char *pf = (char*)&fx;
		for (int i = 0; i < 4; i++)
			printf("%.2x", pf[i]);
		cout << endl;
		/*
float---第31位(占1bit)---第30-23位(占8bit)----第22-0位(占23bit)
double--第63位(占1bit)---第62-52位(占11bit)---第51-0位(占52bit)

*/


	}
#endif // 1
#if 0
	{
		const  char *pf = "12345";
		for (int i = 0; i < strlen(pf); i++)
			printf("%.2x", pf[i]);
		cout << endl;
	}
#endif // 1



	return 0;
}