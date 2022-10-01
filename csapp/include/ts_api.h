#ifndef __TS_API
#define __TS_API 1
#include <iostream>
inline bool checkSmall()
{
	int x = 0x1234567;
	char *px = (char*)&x;
	if (*px == 0x01)
	{
		return false;
	}
	return true;
}
inline char *toSamll(char *p, int len)
{
	if (checkSmall())
		return p;
	int i = 0, j = len - 1;
	while (i < j)
		std::swap(p[i++], p[j--]);

	return p;
}
inline char *toBig(char *p, int len)
{
	if (!checkSmall())
		return p;
	int i = 0, j = len - 1;
	while (i < j)
		std::swap(p[i++], p[j--]);

	return p;
}
#endif