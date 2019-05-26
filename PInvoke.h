#pragma once
#include "pch.h"
#include "SQAR.h"
#include "Hashing.h"

extern "C"
{
	void GetFileNames(uint datPathCount, wchar** datPaths, uint dictionaryLineCount, wchar** dictionaryEntries, uint* fileNameCount, wchar** fileNames);
}