#pragma once
#include "pch.h"

struct SQARFileBlob
{
	ulong hash;
	ulong size;
	ubyte* data;

	~SQARFileBlob()
	{
		delete[] data;
	}
};