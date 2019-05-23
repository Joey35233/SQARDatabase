#pragma once
#include "pch.h"

struct SQARFileBlob
{
	ulong size;
	ubyte* data;

	~SQARFileBlob()
	{
		delete[] data;
	}
};