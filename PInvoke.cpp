#include "pch.h"
#include "PInvoke.h"

using namespace Fs;

#define CreateFileForReading(x) CreateFile(x, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL)

// I hate this code so much
void GetFileNames(uint datPathCount, char** datPaths, uint dictionaryLineCount, char** dictionaryEntries, uint* fileCount, SQAR::SQARFileInformation** files)
{
	auto dictionary = Data::bytell_hash_map<ulong, char*>();
	for (uint i = 0; i < dictionaryLineCount; i++)
	{
		auto string = dictionaryEntries[i];
		auto hash = Data::Hashing::HashFilePath(string);
		dictionary.emplace(hash, string);
	}

	// Context all the switches!
	std::vector<SQAR::SQARFileInformation> fileInfo;
	for (uint i = 0; i < datPathCount; i++)
	{
		HANDLE handle;
		{
			auto datPathStrLength = strlen(datPaths[i]);
			auto wStringBuffer = new wchar[datPathStrLength + 1];
			mbstowcs_s(nullptr, wStringBuffer, datPathStrLength + 1, datPaths[i], datPathStrLength + 2);
			handle = CreateFileForReading(wStringBuffer);
			delete[] wStringBuffer;
		}

		auto stream = ReadFile(handle);
		auto archive = SQAR::SQAR(stream);
		archive.AddHashes(fileInfo);

		CloseHandle(handle);
	}

	*fileCount = fileInfo.size();
	*files = (SQAR::SQARFileInformation*)CoTaskMemAlloc(*fileCount * sizeof(SQAR::SQARFileInformation));
	for (uint i = 0; i < *fileCount; i++)
	{
		auto hash = fileInfo[i].hash & 0x3FFFFFFFFFFFF;
		auto cstr = dictionary[hash];
		std::string string;
		if (!cstr)
		{
			std::stringstream stream;
			stream << "0x" << std::hex << hash;
			string = stream.str();
		}
		else
		{
			string = cstr;
		}

		fileInfo[i].path = (char*)CoTaskMemAlloc(string.length() + 1);
		memcpy(fileInfo[i].path, string.c_str(), string.length() + 1);
	}

	return;
}