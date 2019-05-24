#include "pch.h"
#include "IO.h"

UDataStream ReadFile(const wchar_t* fileName)
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
		size = *(uint64_t*)& stupid;
	}

	auto buffer = new uint8_t[size];
	ReadFile(file, buffer, size, NULL, NULL);
	CloseHandle(file);

	return UDataStream(buffer);
}

void WriteFile(ulong hash, const FileBlob& blob)
{
	WriteFile(std::to_wstring(hash).c_str(), blob);
}

void WriteFile(const wchar* name, const FileBlob& blob)
{
	auto file = CreateFile
	(
		name,
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

ubyte UDataStream::ReadUInt8()
{
	return Read<ubyte>();
}

ushort UDataStream::ReadUInt16()
{
	return Read<ushort>();
}

uint UDataStream::ReadUInt32()
{
	return Read<uint>();
}

ulong UDataStream::ReadUInt64()
{
	return Read<ulong>();
}

float UDataStream::ReadFloat()
{
	return Read<float>();
}

ubyte* UDataStream::ReadBytes(uint count)
{
	auto ptr = buffer + bufferCursor;
	bufferCursor += count;
	return ptr;
}

void UDataStream::Seek(ulong position)
{
	bufferCursor = position;
}

void UDataStream::Skip(ulong amount)
{
	bufferCursor = bufferCursor + amount;
}

ulong UDataStream::GetPosition()
{
	return bufferCursor;
}

ubyte* UDataStream::GetBuffer()
{
	return buffer;
}