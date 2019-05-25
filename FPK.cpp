#include "pch.h"
#include "FPK.h"

FPK::FPK(UDataStream& stream)
{
	Data = stream.GetBuffer();
	stream.Skip(36);
	FileCount = stream.ReadUInt32();
	ReferenceCount = stream.ReadUInt32();
	stream.Skip(4);

	Files = (FPKFile*)malloc(sizeof(FPKFile) * FileCount);
	for (uint i = 0; i < FileCount; i++)
	{
		Files[i] = FPKFile(stream);
	}

	References = (FPKReference*)malloc(sizeof(FPKReference) * ReferenceCount);
	for (uint i = 0; i < ReferenceCount; i++)
	{
		References[i] = FPKReference(stream);
	}
}

uint FPK::GetFileCount()
{
	return FileCount;
}

uint FPK::GetReferenceCount()
{
	return ReferenceCount;
}

NamedFileBlob* FPK::GetFiles()
{
	auto blobs = new NamedFileBlob[FileCount];

	for (uint i = 0; i < FileCount; i++)
	{
		auto entry = Files + i;

		// String
		auto name = entry->GetName();
		auto stringSize = name.Length;

		auto dataSize = entry->GetDataSize();

		blobs[i].size = 8 + stringSize + 1 + dataSize;
		blobs[i].data = new ubyte[blobs[i].size];

		*(ulong*)blobs[i].data = name.Length;
		memcpy(blobs[i].data + 8, name.String, name.Length);
		*(blobs[i].data + 8 + name.Length) = 0;

		auto dataPtr = Data + entry->GetDataOffset();
		memcpy(blobs[i].data + 8 + name.Length + 1, dataPtr, dataSize);
	}

	return blobs;
}