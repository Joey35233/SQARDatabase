#include "pch.h"
#include "PInvoke.h"

using namespace Fs;

#define CreateFileForReading(x) CreateFile(x, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)

void GetFileNames(uint datPathCount, char** datPaths, uint dictionaryLineCount, char** dictionaryEntries, uint* fileNameCount, char** fileNames)
{
	auto dictionary = Data::bytell_hash_map<ulong, char*>();
	for (uint i = 0; i < dictionaryLineCount; i++)
	{
		auto string = dictionaryEntries[i];
		auto hash = Data::Hashing::HashFilePath(string);
		dictionary.emplace(hash, string);
	}

	auto SQARs = new SQAR::SQAR[datPathCount];
	auto handles = new HANDLE[datPathCount];
	for (uint i = 0; i < datPathCount; i++)
	{
		auto datPathStrLength = strlen(datPaths[i]);
		auto wStringBuffer = new wchar[datPathStrLength + 1];
		mbstowcs_s(nullptr, wStringBuffer, datPathStrLength + 1, datPaths[i], datPathStrLength + 2);
		handles[i] = CreateFileForReading(wStringBuffer);

		auto handle = handles[i];

		SQARs[i].InitHeader(ReadFile(handle, 32));
		SQARs[i].InitFileList(ReadFile(handle, SQARs[i].GetFileCount() * 8));

		auto first = SQARs[i].GetEntry(0x522997cd03f88edd);
		*fileNameCount = SQARs[i].GetFileCount();
	}

	return;
}