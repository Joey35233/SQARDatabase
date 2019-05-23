#pragma once
#include "pch.h"

struct MD5
{
	MD5();
	MD5(ubyte*);
	ubyte data[16];
};