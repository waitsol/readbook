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
inline INT64 GetTickCountEx()//
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
static INT64 begintime = 0;
//不可以多线程使用
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


#endif