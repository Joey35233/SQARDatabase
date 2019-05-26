#pragma once
#include "pch.h"

namespace Data
{
	struct MD5
	{
		MD5();
		MD5(ubyte*);
		ubyte data[16];
	};
}