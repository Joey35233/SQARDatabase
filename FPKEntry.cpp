#pragma once
#include "pch.h"
#include "FpkEntry.h"

namespace Fs::Fpk::impl
{
	FpkString::FpkString()
	{
	}

	FpkString::FpkString(UDataStream& stream)
	{
		auto offset = stream.ReadUInt64();
		Length = stream.ReadUInt64();
		String = (char*)stream.GetBuffer() + offset;
	}

	FpkFile::FpkFile(UDataStream& stream)
	{
		DataOffset = stream.ReadUInt64();
		DataSize = stream.ReadUInt64();
		Name = FpkString(stream);
		DataHash = Data::MD5(stream.ReadBytes(16));
	}

	ulong FpkFile::GetDataOffset()
	{
		return DataOffset;
	}

	ulong FpkFile::GetDataSize()
	{
		return DataSize;
	}

	FpkString FpkFile::GetName()
	{
		return Name;
	}

	FpkReference::FpkReference(UDataStream& stream)
	{
		ReferenceName = FpkString(stream);
	}
}