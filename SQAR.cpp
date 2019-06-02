#include "pch.h"
#include "SQAR.h"
#include <zlib.h>
#include "Hashing.h"

namespace Fs::SQAR
{
	static constexpr ubyte XM_Header[]
	{
		0x00, 0x00, 0x00, 0x00,
		0x43, 0x10, 0x44, 0x41,
		0x50, 0x20, 0xC2, 0x11,
		0xC3, 0x08, 0x56, 0xD0,
		0x19, 0x73, 0x2C, 0x53,
		0x43, 0x10, 0x44, 0x41,
		0x43, 0x10, 0x44, 0x41,
		0x50, 0x20, 0xC2, 0x11
	};

	SQAR::SQAR(UDataStream stream)
	{
		Data = stream.GetBuffer();

		// Copy header
		InitHeader(stream.ReadBytes(32));
	}

	SQAR::~SQAR()
	{
		delete[] Data;
	}

	void SQAR::InitHeader(ubyte* bytes)
	{
		for (int i = 0; i < 32; ++i)
			((ubyte*)this)[i] = XM_Header[i] ^ bytes[i];
	}

	void SQAR::InitFileList()
	{
		auto data = Data + 32;
		auto sections = DecryptSectionList((ulong*)data);

		// Determines the alignment block size.
		uint blockShiftCount = (Flags & 0x800) > 0 ? 12 : 10;

		for (uint i = 0; i < FileCount; i++)
		{
			auto offset = sections[i] >> 40;
			offset <<= blockShiftCount;
			Entries.emplace(sections[i] & 0xFFFFFFFF, offset);
		}

		delete[] sections;
	}

	ulong* SQAR::DecryptSectionList(ulong* list)
	{
		auto sections = new ulong[FileCount];

		for (int i = 0; i < FileCount; i += 1)
		{
			uint i1 = (uint)list[i];
			uint i2 = list[i] >> 32;
			uint index1 = (i + ((i * sizeof(ulong)) / 5)) % 4;
			uint index2 = (i + ((i * sizeof(ulong) + sizeof(uint)) / 5)) % 4;
			i1 ^= XM[index1];
			i2 ^= XM[index2];

			sections[i] = (ulong)i2 << 32 | i1;
		}

		return sections;
	}

	ulong SQAR::GetSectionEntry(uint offset)
	{
		auto encryptedEntry = ((ulong*)(Data + 32))[offset];
		ulong entry = 0;

		uint i1 = (uint)encryptedEntry;
		uint i2 = encryptedEntry >> 32;
		uint index1 = (offset + ((offset * sizeof(ulong)) / 5)) % 4;
		uint index2 = (offset + ((offset * sizeof(ulong) + sizeof(uint)) / 5)) % 4;
		i1 ^= XM[index1];
		i2 ^= XM[index2];

		entry = (ulong)i2 << 32 | i1;

		return entry;
	}

	FileBlob SQAR::GetEntry(ulong hash)
	{
		// This needs a revamp
		auto offset = Entries[hash >> 32];
		auto stream = UDataStream(Data + offset);
		auto file = impl::SQARFile(stream);

		ubyte* buffer = nullptr;

		auto uncompressedSize = file.GetUncompressedSize();
		auto dataOffset = file.GetDataOffset();

		if (file.IsCompressed())
		{
			auto compressedSize = file.GetCompressedSize();

			auto decryptedData = DecryptData((uint)hash, dataOffset, compressedSize);
			buffer = new ubyte[uncompressedSize];
			uLong ucSize = uncompressedSize;
			uncompress(buffer, &ucSize, decryptedData, compressedSize);

			return { uncompressedSize, buffer };
		}

		memcpy(buffer, Data + dataOffset, uncompressedSize);
		return { uncompressedSize, buffer };
	}

	void SQAR::AddHashes(std::vector<SQARFileInformation>& vec)
	{
		auto stream = UDataStream(Data);

		for (auto fileOffset : Entries)
		{
			stream.Seek(fileOffset.second);
			auto file = impl::SQARFile(stream);

			SQARFileInformation info{};
			info.offset = fileOffset.second;
			info.size = file.GetCompressedSize();
			info.hash = file.GetHash();
			info.string = nullptr;
			vec.push_back(std::move(info));
		}
	}

	ubyte* SQAR::DecryptData(uint hashLow, ulong dataOffset, ulong size)
	{
		auto data = Data + dataOffset;

		auto blocks = size / sizeof(ulong);
		for (uint i = 0; i < blocks; i++)
		{
			uint offset = i * sizeof(ulong);

			uint index = (2 * ((hashLow + offset / 11) % 4));

			*(ulong*)(data + offset) ^= (ulong)impl::DecryptionTable[index + 1] << 32 | impl::DecryptionTable[index];
		}

		uint remaining = size % sizeof(ulong);
		uint startOffset = blocks * sizeof(long);
		for (uint i = 0; i < remaining; i++)
		{
			uint offset = startOffset + i;

			uint index = (2 * ((hashLow + (offset - (offset % sizeof(long))) / 11) % 4));
			uint decryptionIndex = offset % sizeof(long);
			uint xorMask = decryptionIndex < 4 ? impl::DecryptionTable[index] : impl::DecryptionTable[index + 1];
			ubyte xorMaskByte = ((xorMask >> (8 * decryptionIndex)) & 0xff);
			data[offset] ^= xorMaskByte;
		}

		return data;
	}

	uint SQAR::GetFileCount()
	{
		return FileCount;
	}
}