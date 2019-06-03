#pragma once
#include "pch.h"
#include "Sqar.h"
#include "Hashing.h"

extern "C"
{
	__declspec(dllexport) void GetFileInfo(wchar* datPath, uint* fileInfoCount, Fs::Sqar::SqarFileInformation** fileInfo);
}