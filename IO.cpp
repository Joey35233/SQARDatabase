#include "pch.h"
#include "IO.h"

namespace Fs
{
	HANDLE GetReadHandle(const wchar_t* fileName)
	{
		return CreateFile
		(
			fileName,
			GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);
	}

	ubyte* ReadFile(HANDLE file)
	{
		LARGE_INTEGER stupid;
		GetFileSizeEx(file, &stupid);
		ulong size = *(ulong*)& stupid;

		return ReadFile(file, size);
	}

	ubyte* ReadFile(HANDLE file, ulong size)
	{
		auto buffer = new uint8_t[size];
		::ReadFile(file, buffer, size, NULL, NULL);

		return buffer;
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
		::WriteFile(file, blob.data, blob.size, NULL, NULL);
		CloseHandle(file);
	}

	void WriteFile(const wchar* name, const NamedFileBlob& blob)
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
		auto offset = 8 + *(ulong*)blob.data + 1;
		::WriteFile(file, blob.data + offset, blob.size - offset, NULL, NULL);
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

	char* UDataStream::ReadString(uint count)
	{
		auto ptr = buffer + bufferCursor;
		bufferCursor += count;
		return (char*)ptr;
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
}