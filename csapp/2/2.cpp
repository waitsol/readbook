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
		//��ֵ���������֮��
		int16_t a = 1 << 15;//-32768
		cout << a << endl;
		int16_t fa = -1;
		//�²��Ǽ� Ǳ��ʶ��32768   ��Ϊ�з���32768Ҳ����-32768
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
	//2.1.3��С��
	{
		//��� �ߵ�ַ�Ը���Чλ 0x100 01   0x101 23 0x102 45 0x103 67
		//С�ε�ַ�洢�����෴ ����ȡ��ͷ��ַ�鿴���� ����ַתchar* �鿴0x100����
		int x = 0x1234567;
		char *px = (char*)&x;
		cout << hex << (*px & 0xff) << endl;
		cout << hex << (int)px[0] << endl;
		cout << hex << (int)px[3] << endl;
		if (*px == 0x01)
		{
			cout << "���" << endl;
		}
		else
		{
			cout << "С��" << endl;
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
float---��31λ(ռ1bit)---��30-23λ(ռ8bit)----��22-0λ(ռ23bit)
double--��63λ(ռ1bit)---��62-52λ(ռ11bit)---��51-0λ(ռ52bit)

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