#pragma once
#include "pch.h"
#include "SQAR.h"
#include "Hashing.h"

extern "C"
{
	__declspec(dllexport) void GetFileNames(uint datPathCount, char** datPaths, uint dictionaryEntryCount, char** dictionaryEntries, uint* fileNameCount, char*** fileNames);
}