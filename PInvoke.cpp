#include "pch.h"
#include "PInvoke.h"

#define CreateFileForReading(x) CreateFile(x, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)

void GetFileNames(uint datPathCount, wchar** datPaths, uint dictionaryLineCount, wchar** dictionaryEntries, uint* fileNameCount, wchar** fileNames)
{
	//auto SQARs = new Fs::SQAR::SQAR[datPathCount];
}