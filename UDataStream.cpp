#include "pch.h"
#include "UDataStream.h"

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
