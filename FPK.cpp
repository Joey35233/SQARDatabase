#include "pch.h"
#include "Fpk.h"

namespace Fs::Fpk
{
	Fpk::Fpk(UDataStream stream)
	{
		Data = stream.GetBuffer();
		stream.Skip(36);
		FileCount = stream.ReadUInt32();
		ReferenceCount = stream.ReadUInt32();
		stream.Skip(4);

		Files = (impl::FpkFile*)malloc(sizeof(impl::FpkFile) * FileCount);
		for (uint i = 0; i < FileCount; i++)
		{
			Files[i] = impl::FpkFile(stream);
		}

		References = (impl::FpkReference*)malloc(sizeof(impl::FpkReference) * ReferenceCount);
		for (uint i = 0; i < ReferenceCount; i++)
		{
			References[i] = impl::FpkReference(stream);
		}
	}

	uint Fpk::GetFileCount()
	{
		return FileCount;
	}

	uint Fpk::GetReferenceCount()
	{
		return ReferenceCount;
	}

	NamedFileBlob* Fpk::GetFiles()
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
}