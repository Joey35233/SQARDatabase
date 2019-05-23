#include "pch.h"
#include "UDataStream.h"
#include "SQAR.h"

// This right here, this right here is laziness.
UDataStream ReadSQAR(const wchar_t* fileName)
{
	auto file = CreateFile
	(
		fileName,
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	uint64_t size;
	{
		LARGE_INTEGER stupid;
		GetFileSizeEx(file, &stupid);
		size = *(uint64_t*)&stupid;
	}

	auto buffer = new uint8_t[size];
	ReadFile(file, buffer, size, NULL, NULL);
	CloseHandle(file);

	return UDataStream(buffer);
}

void WriteFile(SQARFile* entry, ubyte* data)
{
	auto file = CreateFile
	(
		std::to_wstring(entry->GetHash()).c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	WriteFile(file, data, entry->GetUncompressedSize(), NULL, NULL);
	delete[] data;
	CloseHandle(file);
}

int main()
{
	auto stream = ReadSQAR(L"chunk0.dat");

	auto archive = new SQAR(stream);

	for (uint i = 0; i < archive->GetFileCount(); i++)
	{
		auto entry = archive->GetEntry(i);
		if (entry->IsEncrypted())
		{
			printf("Error: %llu#018x is encrypted!\n", entry->GetHash());
			break;
		}
			
		WriteFile(entry, archive->GetFile(i));
	}
	return 0;
}