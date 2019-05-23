#include "pch.h"
#include "MD5.h"

MD5::MD5()
{
}

MD5::MD5(ubyte* bytes)
{
	memcpy(data, &_mm_xor_si128(*(__m128i*)bytes, _mm_set_epi32(XM[1], XM[0], XM[0], XM[3])), 16);
}