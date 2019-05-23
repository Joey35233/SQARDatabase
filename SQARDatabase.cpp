#include "pch.h"
#include "UDataStream.h"
#include "SQAR.h"
#include "bytell_hash_map.h"

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

void WriteSQARFile(ulong hash, const SQARFileBlob& blob)
{
	auto file = CreateFile
	(
		std::to_wstring(hash).c_str(),
		GENERIC_WRITE,
		FILE_SHARE_WRITE,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	WriteFile(file, blob.data, blob.size, NULL, NULL);
	CloseHandle(file);
}

int main()
{
	auto stream = ReadSQAR(L"chunk0.dat");

	auto archive = new SQAR(stream);

	ulong hash = 0x522997cd03f88edd >> 32;
	WriteSQARFile(hash, archive->GetEntry(hash));

	return 0;
}