#pragma once
#include "pch.h"
#include "FPKEntry.h"

FPKString::FPKString()
{
}

FPKString::FPKString(UDataStream& stream)
{
	auto offset = stream.ReadUInt64();
	Length = stream.ReadUInt64();
	String = (char*)stream.GetBuffer() + offset;
}

FPKFile::FPKFile(UDataStream& stream)
{
	DataOffset = stream.ReadUInt64();
	DataSize = stream.ReadUInt64();
	Name = FPKString(stream);
	DataHash = MD5(stream.ReadBytes(16));
}

ulong FPKFile::GetDataOffset()
{
	return DataOffset;
}

ulong FPKFile::GetDataSize()
{
	return DataSize;
}

FPKString FPKFile::GetName()
{
	return Name;
}

FPKReference::FPKReference(UDataStream& stream)
{
	ReferenceName = FPKString(stream);
}