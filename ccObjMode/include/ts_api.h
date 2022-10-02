#ifndef __TS_API
#define __TS_API 1
#include <iostream>


#include <stdint.h>
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif // WIN32
using std::cout;
using std::endl;
#define d_cout(x) cout <<dec<< #x << " " << (x) << endl;
#define h_cout(x) cout <<hex<< #x << " " << (x) << endl;

inline int64_t GetTickCountEx()//
{
#ifndef WIN32
	struct timeval tv;
	struct timezone tz;

	gettimeofday(&tv, &tz);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
#else
	return GetTickCount64();
#endif // !WIN32

}
static int64_t begintime = 0;
//�����Զ��߳�ʹ��
void ptime()
{
	if (begintime == 0)
	{
		begintime = GetTickCountEx();
	}
	else {
		cout << "use time " << (GetTickCountEx() - begintime)<<" ms"<< endl;
		begintime = 0;
	}
}
template<class T>
void PrintType(T type)
{
	int64_t *p = reinterpret_cast<int64_t *>(&type);
	for (int i=0;i<sizeof(T)/sizeof(int64_t);i++)
	{
		d_cout(p[i]);
	}
}

void printAddrFunc(void *addr,int c=2)
{
	typedef void(*_func)();
	printf("addr = %p\n", addr);
	_func *vptr=reinterpret_cast<_func*>(*static_cast<int64_t*>(addr));
	if (vptr != nullptr)
	{
		for (int i = 0; i < c; i++)
		{

			vptr[i]();
		}

	}
}

#endif
