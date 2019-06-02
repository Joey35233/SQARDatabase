#pragma once
#include "pch.h"
#include "SQAR.h"
#include "Hashing.h"

extern "C"
{
	__declspec(dllexport) void GetFileInfo(wchar* datPath, uint* fileInfoCount, Fs::SQAR::SQARFileInformation** fileInfo);
}