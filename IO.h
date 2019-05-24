#pragma once
#include "pch.h"

struct FileBlob
{
	ulong size;
	ubyte* data;

	~FileBlob()
	{
		delete[] data;
		//ReadFile()
	}
};

class UDataStream
{
public:
	UDataStream(ubyte* buffer)
		: buffer(buffer)
	{}

	UDataStream(ubyte* buffer, ulong cursorOffset)
		: buffer(buffer), bufferCursor(cursorOffset)
	{}

	template<typename T>
	T Read()
	{
		auto value = *(T*)(buffer + bufferCursor);
		bufferCursor += sizeof(T);
		return value;
	}

	ubyte ReadUInt8();
	ushort ReadUInt16();
	uint ReadUInt32();
	ulong ReadUInt64();
	float ReadFloat();
	ubyte* ReadBytes(uint);
	void Seek(ulong position);
	void Skip(ulong amount);
	ulong GetPosition();
	ubyte* GetBuffer();

private:
	ulong bufferCursor;
	ubyte* buffer;
};

// This right here, this right here is laziness.
UDataStream ReadFile(const wchar_t* fileName);
void WriteFile(ulong hash, const FileBlob& blob);
void WriteFile(const wchar* name, const FileBlob& blob);