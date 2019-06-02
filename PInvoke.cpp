#include "pch.h"
#include "PInvoke.h"

using namespace Fs;

#define CreateFileForReading(x) CreateFile(x, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)

// I hate this code so much
void GetFileInfo(wchar* datPath, uint* fileInfoCount, Fs::SQAR::SQARFileInformation** fileInfo)
{
	auto fileHandle = CreateFileForReading(datPath);

	auto stream = ReadFile(fileHandle);
	auto archive = SQAR::SQAR(stream);

	*fileInfoCount = archive.GetFileCount();
	*fileInfo = (SQAR::SQARFileInformation*)CoTaskMemAlloc(*fileInfoCount * sizeof(SQAR::SQARFileInformation));
	archive.PopulateFileInfo(*fileInfo);

	CloseHandle(fileHandle);

	return;
}