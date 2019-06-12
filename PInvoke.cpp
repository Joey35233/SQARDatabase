#include "pch.h"
#include "PInvoke.h"
#include "Fpk.h"

#define CreateFileForReading(x) CreateFile(x, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING , NULL)

using namespace Fs;

// I hate this code so much
void GetFileInfo(HANDLE fileHandle, uint* fileInfoCount, Fs::Sqar::SqarFileInformation** fileInfo)
{
	auto stream = ReadFile(fileHandle);
	auto archive = Sqar::Sqar(stream);

	*fileInfoCount = archive.GetFileCount();
	*fileInfo = (Sqar::SqarFileInformation*)CoTaskMemAlloc(*fileInfoCount * sizeof(Sqar::SqarFileInformation));
	archive.PopulateFileInfo(*fileInfo);

	return;
}